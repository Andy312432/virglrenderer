/*
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: MIT
 */

#include "vkr_transport.h"

#include "venus-protocol/vn_protocol_renderer_dispatches.h"
#include "venus-protocol/vn_protocol_renderer_transport.h"

#include "vkr_context.h"
#include "vkr_ring.h"

static void
vkr_dispatch_vkSetReplyCommandStreamMESA(
   struct vn_dispatch_context *dispatch,
   struct vn_command_vkSetReplyCommandStreamMESA *args)
{
   struct vkr_context *ctx = dispatch->data;
   struct vkr_resource *res = vkr_context_get_resource(ctx, args->pStream->resourceId);
   if (!res) {
      vkr_log("failed to set reply stream: invalid res_id %u", args->pStream->resourceId);
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return;
   }

   vkr_cs_encoder_set_stream(&ctx->encoder, res, args->pStream->offset,
                             args->pStream->size);
}

static void
vkr_dispatch_vkSeekReplyCommandStreamMESA(
   struct vn_dispatch_context *dispatch,
   struct vn_command_vkSeekReplyCommandStreamMESA *args)
{
   struct vkr_context *ctx = dispatch->data;
   vkr_cs_encoder_seek_stream(&ctx->encoder, args->position);
}

static void
vkr_dispatch_vkExecuteCommandStreamsMESA(
   struct vn_dispatch_context *dispatch,
   struct vn_command_vkExecuteCommandStreamsMESA *args)
{
   struct vkr_context *ctx = dispatch->data;

   if (unlikely(!args->streamCount)) {
      vkr_log("failed to execute command streams: no stream specified");
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return;
   }

   /* note that nested vkExecuteCommandStreamsMESA is not allowed */
   if (unlikely(!vkr_cs_decoder_push_state(&ctx->decoder))) {
      vkr_log("failed to execute command streams: nested execution");
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return;
   }

   for (uint32_t i = 0; i < args->streamCount; i++) {
      const VkCommandStreamDescriptionMESA *stream = &args->pStreams[i];

      if (args->pReplyPositions)
         vkr_cs_encoder_seek_stream(&ctx->encoder, args->pReplyPositions[i]);

      if (!stream->size)
         continue;

      struct vkr_resource *res = vkr_context_get_resource(ctx, stream->resourceId);
      if (!res) {
         vkr_log("failed to execute command streams: invalid stream %u res_id %u", i,
                 stream->resourceId);
         vkr_cs_decoder_set_fatal(&ctx->decoder);
         break;
      }

      if (stream->offset + stream->size > res->size) {
         vkr_log("failed to execute command streams: invalid stream %u res_id %u", i,
                 stream->resourceId);
         vkr_cs_decoder_set_fatal(&ctx->decoder);
         break;
      }

      vkr_cs_decoder_set_stream(&ctx->decoder, res->u.data + stream->offset,
                                stream->size);
      while (vkr_cs_decoder_has_command(&ctx->decoder)) {
         vn_dispatch_command(&ctx->dispatch);
         if (vkr_cs_decoder_get_fatal(&ctx->decoder))
            break;
      }

      if (vkr_cs_decoder_get_fatal(&ctx->decoder))
         break;
   }

   vkr_cs_decoder_pop_state(&ctx->decoder);
}

static struct vkr_ring *
lookup_ring(struct vkr_context *ctx, uint64_t ring_id)
{
   struct vkr_ring *ring;
   LIST_FOR_EACH_ENTRY (ring, &ctx->rings, head) {
      if (ring->id == ring_id)
         return ring;
   }
   return NULL;
}

static bool
vkr_ring_layout_init(struct vkr_ring_layout *layout,
                     const struct vkr_resource *res,
                     const VkRingCreateInfoMESA *info)
{
   *layout = (struct vkr_ring_layout){
      .resource = res,
      .head = VKR_REGION_INIT(info->offset + info->headOffset, sizeof(uint32_t)),
      .tail = VKR_REGION_INIT(info->offset + info->tailOffset, sizeof(uint32_t)),
      .status = VKR_REGION_INIT(info->offset + info->statusOffset, sizeof(uint32_t)),
      .buffer = VKR_REGION_INIT(info->offset + info->bufferOffset, info->bufferSize),
      .extra = VKR_REGION_INIT(info->offset + info->extraOffset, info->extraSize),
   };

   const struct vkr_region res_region = VKR_REGION_INIT(info->offset, info->size);
   const struct vkr_region *regions[] = {
      &layout->head, &layout->tail, &layout->status, &layout->buffer, &layout->extra,
   };

   const struct vkr_region res_size = VKR_REGION_INIT(0, res->size);
   if (!vkr_region_is_valid(&res_region) || !vkr_region_is_within(&res_region, &res_size))
      return false;

   for (size_t i = 0; i < ARRAY_SIZE(regions); i++) {
      const struct vkr_region *region = regions[i];

      if (!vkr_region_is_valid(region) || !vkr_region_is_within(region, &res_region)) {
         vkr_log("ring buffer control variable (begin=%lu, end=%lu) placed"
                 " out-of-bounds in shared memory layout",
                 region->begin, region->end);
         return false;
      }

      if (!vkr_region_is_aligned(region, 4)) {
         vkr_log("ring buffer control variable (begin=%lu, end=%lu) must be"
                 " 32-bit aligned in shared memory layout",
                 region->begin, region->end);
         return false;
      }
   }

   /* assumes region->size == 0 is valid */
   for (size_t i = 0; i < ARRAY_SIZE(regions); i++) {
      const struct vkr_region *region = regions[i];

      for (size_t j = i + 1; j < ARRAY_SIZE(regions); j++) {
         const struct vkr_region *other = regions[j];

         if (!vkr_region_is_disjoint(region, other)) {
            vkr_log("ring buffer control variable (begin=%lu, end=%lu)"
                    " overlaps with control variable (begin=%lu, end=%lu)",
                    other->begin, other->end, region->begin, region->end);
            return false;
         }
      }
   }

   const size_t buf_size = vkr_region_size(&layout->buffer);
   if (buf_size > VKR_RING_BUFFER_MAX_SIZE || !util_is_power_of_two_nonzero(buf_size)) {
      vkr_log("ring buffer size (%z) must be a power of two and not exceed %lu", buf_size,
              VKR_RING_BUFFER_MAX_SIZE);
      return false;
   }

   return true;
}

static void
vkr_dispatch_vkCreateRingMESA(struct vn_dispatch_context *dispatch,
                              struct vn_command_vkCreateRingMESA *args)
{
   struct vkr_context *ctx = dispatch->data;
   const VkRingCreateInfoMESA *info = args->pCreateInfo;

   const struct vkr_resource *res = vkr_context_get_resource(ctx, info->resourceId);
   if (!res) {
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return;
   }

   struct vkr_ring_layout layout;
   if (!vkr_ring_layout_init(&layout, res, info)) {
      vkr_log("vkCreateRingMESA supplied with invalid buffer layout parameters");
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return;
   }

   struct vkr_ring *ring = vkr_ring_create(&layout, ctx, info->idleTimeout);
   if (!ring) {
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return;
   }

   ring->id = args->ring;
   list_addtail(&ring->head, &ctx->rings);

   vkr_ring_start(ring);
}

static void
vkr_dispatch_vkDestroyRingMESA(struct vn_dispatch_context *dispatch,
                               struct vn_command_vkDestroyRingMESA *args)
{
   struct vkr_context *ctx = dispatch->data;
   struct vkr_ring *ring = lookup_ring(ctx, args->ring);
   if (!ring || !vkr_ring_stop(ring)) {
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return;
   }

   vkr_ring_destroy(ring);
}

static void
vkr_dispatch_vkNotifyRingMESA(struct vn_dispatch_context *dispatch,
                              struct vn_command_vkNotifyRingMESA *args)
{
   struct vkr_context *ctx = dispatch->data;
   struct vkr_ring *ring = lookup_ring(ctx, args->ring);
   if (!ring) {
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return;
   }

   vkr_ring_notify(ring);
}

static void
vkr_dispatch_vkWriteRingExtraMESA(struct vn_dispatch_context *dispatch,
                                  struct vn_command_vkWriteRingExtraMESA *args)
{
   struct vkr_context *ctx = dispatch->data;
   struct vkr_ring *ring = lookup_ring(ctx, args->ring);
   if (!ring) {
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return;
   }

   if (!vkr_ring_write_extra(ring, args->offset, args->value))
      vkr_cs_decoder_set_fatal(&ctx->decoder);
}

static void
vkr_dispatch_vkGetVenusExperimentalFeatureData100000MESA(
   UNUSED struct vn_dispatch_context *dispatch,
   struct vn_command_vkGetVenusExperimentalFeatureData100000MESA *args)
{
   const VkVenusExperimentalFeatures100000MESA features = {
      .memoryResourceAllocationSize = VK_TRUE,
      .globalFencing = VK_FALSE,
      .largeRing = VK_TRUE,
      .syncFdFencing = VK_TRUE,
   };

   vn_replace_vkGetVenusExperimentalFeatureData100000MESA_args_handle(args);

   if (!args->pData) {
      *args->pDataSize = sizeof(features);
      return;
   }

   *args->pDataSize = MIN2(*args->pDataSize, sizeof(features));
   memcpy(args->pData, &features, *args->pDataSize);
}

void
vkr_context_init_transport_dispatch(struct vkr_context *ctx)
{
   struct vn_dispatch_context *dispatch = &ctx->dispatch;

   dispatch->dispatch_vkSetReplyCommandStreamMESA =
      vkr_dispatch_vkSetReplyCommandStreamMESA;
   dispatch->dispatch_vkSeekReplyCommandStreamMESA =
      vkr_dispatch_vkSeekReplyCommandStreamMESA;
   dispatch->dispatch_vkExecuteCommandStreamsMESA =
      vkr_dispatch_vkExecuteCommandStreamsMESA;
   dispatch->dispatch_vkCreateRingMESA = vkr_dispatch_vkCreateRingMESA;
   dispatch->dispatch_vkDestroyRingMESA = vkr_dispatch_vkDestroyRingMESA;
   dispatch->dispatch_vkNotifyRingMESA = vkr_dispatch_vkNotifyRingMESA;
   dispatch->dispatch_vkWriteRingExtraMESA = vkr_dispatch_vkWriteRingExtraMESA;

   dispatch->dispatch_vkGetVenusExperimentalFeatureData100000MESA =
      vkr_dispatch_vkGetVenusExperimentalFeatureData100000MESA;
}
