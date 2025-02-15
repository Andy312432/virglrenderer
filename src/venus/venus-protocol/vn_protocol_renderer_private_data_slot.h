/* This file is generated by venus-protocol.  See vn_protocol_renderer.h. */

/*
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: MIT
 */

#ifndef VN_PROTOCOL_RENDERER_PRIVATE_DATA_SLOT_H
#define VN_PROTOCOL_RENDERER_PRIVATE_DATA_SLOT_H

#include "vn_protocol_renderer_structs.h"

#pragma GCC diagnostic push
#if !defined(__clang__) && defined(__GNUC__) && __GNUC__ >= 12
#pragma GCC diagnostic ignored "-Wdangling-pointer"
#endif
#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* struct VkPrivateDataSlotCreateInfo chain */

static inline void *
vn_decode_VkPrivateDataSlotCreateInfo_pnext_temp(struct vn_cs_decoder *dec)
{
    /* no known/supported struct */
    if (vn_decode_simple_pointer(dec))
        vn_cs_decoder_set_fatal(dec);
    return NULL;
}

static inline void
vn_decode_VkPrivateDataSlotCreateInfo_self_temp(struct vn_cs_decoder *dec, VkPrivateDataSlotCreateInfo *val)
{
    /* skip val->{sType,pNext} */
    vn_decode_VkFlags(dec, &val->flags);
}

static inline void
vn_decode_VkPrivateDataSlotCreateInfo_temp(struct vn_cs_decoder *dec, VkPrivateDataSlotCreateInfo *val)
{
    VkStructureType stype;
    vn_decode_VkStructureType(dec, &stype);
    if (stype != VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO)
        vn_cs_decoder_set_fatal(dec);

    val->sType = stype;
    val->pNext = vn_decode_VkPrivateDataSlotCreateInfo_pnext_temp(dec);
    vn_decode_VkPrivateDataSlotCreateInfo_self_temp(dec, val);
}

static inline void
vn_replace_VkPrivateDataSlotCreateInfo_handle_self(VkPrivateDataSlotCreateInfo *val)
{
    /* skip val->sType */
    /* skip val->pNext */
    /* skip val->flags */
}

static inline void
vn_replace_VkPrivateDataSlotCreateInfo_handle(VkPrivateDataSlotCreateInfo *val)
{
    struct VkBaseOutStructure *pnext = (struct VkBaseOutStructure *)val;

    do {
        switch ((int32_t)pnext->sType) {
        case VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO:
            vn_replace_VkPrivateDataSlotCreateInfo_handle_self((VkPrivateDataSlotCreateInfo *)pnext);
            break;
        default:
            /* ignore unknown/unsupported struct */
            break;
        }
        pnext = pnext->pNext;
    } while (pnext);
}

static inline void vn_decode_vkCreatePrivateDataSlot_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkCreatePrivateDataSlot *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    if (vn_decode_simple_pointer(dec)) {
        args->pCreateInfo = vn_cs_decoder_alloc_temp(dec, sizeof(*args->pCreateInfo));
        if (!args->pCreateInfo) return;
        vn_decode_VkPrivateDataSlotCreateInfo_temp(dec, (VkPrivateDataSlotCreateInfo *)args->pCreateInfo);
    } else {
        args->pCreateInfo = NULL;
        vn_cs_decoder_set_fatal(dec);
    }
    if (vn_decode_simple_pointer(dec)) {
        vn_cs_decoder_set_fatal(dec);
    } else {
        args->pAllocator = NULL;
    }
    if (vn_decode_simple_pointer(dec)) {
        args->pPrivateDataSlot = vn_cs_decoder_alloc_temp(dec, sizeof(*args->pPrivateDataSlot));
        if (!args->pPrivateDataSlot) return;
        vn_decode_VkPrivateDataSlot(dec, args->pPrivateDataSlot);
    } else {
        args->pPrivateDataSlot = NULL;
        vn_cs_decoder_set_fatal(dec);
    }
}

static inline void vn_replace_vkCreatePrivateDataSlot_args_handle(struct vn_command_vkCreatePrivateDataSlot *args)
{
    vn_replace_VkDevice_handle(&args->device);
    if (args->pCreateInfo)
        vn_replace_VkPrivateDataSlotCreateInfo_handle((VkPrivateDataSlotCreateInfo *)args->pCreateInfo);
    /* skip args->pAllocator */
    /* skip args->pPrivateDataSlot */
}

static inline void vn_encode_vkCreatePrivateDataSlot_reply(struct vn_cs_encoder *enc, const struct vn_command_vkCreatePrivateDataSlot *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkCreatePrivateDataSlot_EXT});

    vn_encode_VkResult(enc, &args->ret);
    /* skip args->device */
    /* skip args->pCreateInfo */
    /* skip args->pAllocator */
    if (vn_encode_simple_pointer(enc, args->pPrivateDataSlot))
        vn_encode_VkPrivateDataSlot(enc, args->pPrivateDataSlot);
}

static inline void vn_decode_vkDestroyPrivateDataSlot_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkDestroyPrivateDataSlot *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    vn_decode_VkPrivateDataSlot_lookup(dec, &args->privateDataSlot);
    if (vn_decode_simple_pointer(dec)) {
        vn_cs_decoder_set_fatal(dec);
    } else {
        args->pAllocator = NULL;
    }
}

static inline void vn_replace_vkDestroyPrivateDataSlot_args_handle(struct vn_command_vkDestroyPrivateDataSlot *args)
{
    vn_replace_VkDevice_handle(&args->device);
    vn_replace_VkPrivateDataSlot_handle(&args->privateDataSlot);
    /* skip args->pAllocator */
}

static inline void vn_encode_vkDestroyPrivateDataSlot_reply(struct vn_cs_encoder *enc, const struct vn_command_vkDestroyPrivateDataSlot *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkDestroyPrivateDataSlot_EXT});

    /* skip args->device */
    /* skip args->privateDataSlot */
    /* skip args->pAllocator */
}

static inline void vn_decode_vkSetPrivateData_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkSetPrivateData *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    vn_decode_VkObjectType(dec, &args->objectType);
    vn_decode_uint64_t(dec, &args->objectHandle);
    vn_decode_VkPrivateDataSlot_lookup(dec, &args->privateDataSlot);
    vn_decode_uint64_t(dec, &args->data);
}

static inline void vn_replace_vkSetPrivateData_args_handle(struct vn_command_vkSetPrivateData *args)
{
    vn_replace_VkDevice_handle(&args->device);
    /* skip args->objectType */
    /* skip args->objectHandle */
    vn_replace_VkPrivateDataSlot_handle(&args->privateDataSlot);
    /* skip args->data */
}

static inline void vn_encode_vkSetPrivateData_reply(struct vn_cs_encoder *enc, const struct vn_command_vkSetPrivateData *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkSetPrivateData_EXT});

    vn_encode_VkResult(enc, &args->ret);
    /* skip args->device */
    /* skip args->objectType */
    /* skip args->objectHandle */
    /* skip args->privateDataSlot */
    /* skip args->data */
}

static inline void vn_decode_vkGetPrivateData_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkGetPrivateData *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    vn_decode_VkObjectType(dec, &args->objectType);
    vn_decode_uint64_t(dec, &args->objectHandle);
    vn_decode_VkPrivateDataSlot_lookup(dec, &args->privateDataSlot);
    if (vn_decode_simple_pointer(dec)) {
        args->pData = vn_cs_decoder_alloc_temp(dec, sizeof(*args->pData));
        if (!args->pData) return;
    } else {
        args->pData = NULL;
        vn_cs_decoder_set_fatal(dec);
    }
}

static inline void vn_replace_vkGetPrivateData_args_handle(struct vn_command_vkGetPrivateData *args)
{
    vn_replace_VkDevice_handle(&args->device);
    /* skip args->objectType */
    /* skip args->objectHandle */
    vn_replace_VkPrivateDataSlot_handle(&args->privateDataSlot);
    /* skip args->pData */
}

static inline void vn_encode_vkGetPrivateData_reply(struct vn_cs_encoder *enc, const struct vn_command_vkGetPrivateData *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkGetPrivateData_EXT});

    /* skip args->device */
    /* skip args->objectType */
    /* skip args->objectHandle */
    /* skip args->privateDataSlot */
    if (vn_encode_simple_pointer(enc, args->pData))
        vn_encode_uint64_t(enc, args->pData);
}

static inline void vn_dispatch_vkCreatePrivateDataSlot(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkCreatePrivateDataSlot args;

    if (!ctx->dispatch_vkCreatePrivateDataSlot) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkCreatePrivateDataSlot_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkCreatePrivateDataSlot(ctx, &args);

#ifdef DEBUG
    if (!vn_cs_decoder_get_fatal(ctx->decoder) && vn_dispatch_should_log_result(args.ret))
        vn_dispatch_debug_log(ctx, "vkCreatePrivateDataSlot returned %d", args.ret);
#endif

    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkCreatePrivateDataSlot_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

static inline void vn_dispatch_vkDestroyPrivateDataSlot(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkDestroyPrivateDataSlot args;

    if (!ctx->dispatch_vkDestroyPrivateDataSlot) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkDestroyPrivateDataSlot_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkDestroyPrivateDataSlot(ctx, &args);


    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkDestroyPrivateDataSlot_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

static inline void vn_dispatch_vkSetPrivateData(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkSetPrivateData args;

    if (!ctx->dispatch_vkSetPrivateData) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkSetPrivateData_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkSetPrivateData(ctx, &args);

#ifdef DEBUG
    if (!vn_cs_decoder_get_fatal(ctx->decoder) && vn_dispatch_should_log_result(args.ret))
        vn_dispatch_debug_log(ctx, "vkSetPrivateData returned %d", args.ret);
#endif

    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkSetPrivateData_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

static inline void vn_dispatch_vkGetPrivateData(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkGetPrivateData args;

    if (!ctx->dispatch_vkGetPrivateData) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkGetPrivateData_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkGetPrivateData(ctx, &args);


    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkGetPrivateData_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

#pragma GCC diagnostic pop

#endif /* VN_PROTOCOL_RENDERER_PRIVATE_DATA_SLOT_H */
