/* This file is generated by venus-protocol.  See vn_protocol_renderer.h. */

/*
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: MIT
 */

#ifndef VN_PROTOCOL_RENDERER_PIPELINE_CACHE_H
#define VN_PROTOCOL_RENDERER_PIPELINE_CACHE_H

#include "vn_protocol_renderer_structs.h"

#pragma GCC diagnostic push
#if !defined(__clang__) && defined(__GNUC__) && __GNUC__ >= 12
#pragma GCC diagnostic ignored "-Wdangling-pointer"
#endif
#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wunused-parameter"

/* struct VkPipelineCacheCreateInfo chain */

static inline void *
vn_decode_VkPipelineCacheCreateInfo_pnext_temp(struct vn_cs_decoder *dec)
{
    /* no known/supported struct */
    if (vn_decode_simple_pointer(dec))
        vn_cs_decoder_set_fatal(dec);
    return NULL;
}

static inline void
vn_decode_VkPipelineCacheCreateInfo_self_temp(struct vn_cs_decoder *dec, VkPipelineCacheCreateInfo *val)
{
    /* skip val->{sType,pNext} */
    vn_decode_VkFlags(dec, &val->flags);
    vn_decode_size_t(dec, &val->initialDataSize);
    if (vn_peek_array_size(dec)) {
        const size_t array_size = vn_decode_array_size(dec, val->initialDataSize);
        val->pInitialData = vn_cs_decoder_alloc_temp(dec, array_size);
        if (!val->pInitialData) return;
        vn_decode_blob_array(dec, (void *)val->pInitialData, array_size);
    } else {
        vn_decode_array_size(dec, val->initialDataSize);
        val->pInitialData = NULL;
    }
}

static inline void
vn_decode_VkPipelineCacheCreateInfo_temp(struct vn_cs_decoder *dec, VkPipelineCacheCreateInfo *val)
{
    VkStructureType stype;
    vn_decode_VkStructureType(dec, &stype);
    if (stype != VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO)
        vn_cs_decoder_set_fatal(dec);

    val->sType = stype;
    val->pNext = vn_decode_VkPipelineCacheCreateInfo_pnext_temp(dec);
    vn_decode_VkPipelineCacheCreateInfo_self_temp(dec, val);
}

static inline void
vn_replace_VkPipelineCacheCreateInfo_handle_self(VkPipelineCacheCreateInfo *val)
{
    /* skip val->sType */
    /* skip val->pNext */
    /* skip val->flags */
    /* skip val->initialDataSize */
    /* skip val->pInitialData */
}

static inline void
vn_replace_VkPipelineCacheCreateInfo_handle(VkPipelineCacheCreateInfo *val)
{
    struct VkBaseOutStructure *pnext = (struct VkBaseOutStructure *)val;

    do {
        switch ((int32_t)pnext->sType) {
        case VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO:
            vn_replace_VkPipelineCacheCreateInfo_handle_self((VkPipelineCacheCreateInfo *)pnext);
            break;
        default:
            /* ignore unknown/unsupported struct */
            break;
        }
        pnext = pnext->pNext;
    } while (pnext);
}

static inline void vn_decode_vkCreatePipelineCache_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkCreatePipelineCache *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    if (vn_decode_simple_pointer(dec)) {
        args->pCreateInfo = vn_cs_decoder_alloc_temp(dec, sizeof(*args->pCreateInfo));
        if (!args->pCreateInfo) return;
        vn_decode_VkPipelineCacheCreateInfo_temp(dec, (VkPipelineCacheCreateInfo *)args->pCreateInfo);
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
        args->pPipelineCache = vn_cs_decoder_alloc_temp(dec, sizeof(*args->pPipelineCache));
        if (!args->pPipelineCache) return;
        vn_decode_VkPipelineCache(dec, args->pPipelineCache);
    } else {
        args->pPipelineCache = NULL;
        vn_cs_decoder_set_fatal(dec);
    }
}

static inline void vn_replace_vkCreatePipelineCache_args_handle(struct vn_command_vkCreatePipelineCache *args)
{
    vn_replace_VkDevice_handle(&args->device);
    if (args->pCreateInfo)
        vn_replace_VkPipelineCacheCreateInfo_handle((VkPipelineCacheCreateInfo *)args->pCreateInfo);
    /* skip args->pAllocator */
    /* skip args->pPipelineCache */
}

static inline void vn_encode_vkCreatePipelineCache_reply(struct vn_cs_encoder *enc, const struct vn_command_vkCreatePipelineCache *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkCreatePipelineCache_EXT});

    vn_encode_VkResult(enc, &args->ret);
    /* skip args->device */
    /* skip args->pCreateInfo */
    /* skip args->pAllocator */
    if (vn_encode_simple_pointer(enc, args->pPipelineCache))
        vn_encode_VkPipelineCache(enc, args->pPipelineCache);
}

static inline void vn_decode_vkDestroyPipelineCache_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkDestroyPipelineCache *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    vn_decode_VkPipelineCache_lookup(dec, &args->pipelineCache);
    if (vn_decode_simple_pointer(dec)) {
        vn_cs_decoder_set_fatal(dec);
    } else {
        args->pAllocator = NULL;
    }
}

static inline void vn_replace_vkDestroyPipelineCache_args_handle(struct vn_command_vkDestroyPipelineCache *args)
{
    vn_replace_VkDevice_handle(&args->device);
    vn_replace_VkPipelineCache_handle(&args->pipelineCache);
    /* skip args->pAllocator */
}

static inline void vn_encode_vkDestroyPipelineCache_reply(struct vn_cs_encoder *enc, const struct vn_command_vkDestroyPipelineCache *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkDestroyPipelineCache_EXT});

    /* skip args->device */
    /* skip args->pipelineCache */
    /* skip args->pAllocator */
}

static inline void vn_decode_vkGetPipelineCacheData_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkGetPipelineCacheData *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    vn_decode_VkPipelineCache_lookup(dec, &args->pipelineCache);
    if (vn_decode_simple_pointer(dec)) {
        args->pDataSize = vn_cs_decoder_alloc_temp(dec, sizeof(*args->pDataSize));
        if (!args->pDataSize) return;
        vn_decode_size_t(dec, args->pDataSize);
    } else {
        args->pDataSize = NULL;
        vn_cs_decoder_set_fatal(dec);
    }
    if (vn_peek_array_size(dec)) {
        const size_t array_size = vn_decode_array_size(dec, (args->pDataSize ? *args->pDataSize : 0));
        args->pData = vn_cs_decoder_alloc_temp(dec, array_size);
        if (!args->pData) return;
    } else {
        vn_decode_array_size_unchecked(dec);
        args->pData = NULL;
    }
}

static inline void vn_replace_vkGetPipelineCacheData_args_handle(struct vn_command_vkGetPipelineCacheData *args)
{
    vn_replace_VkDevice_handle(&args->device);
    vn_replace_VkPipelineCache_handle(&args->pipelineCache);
    /* skip args->pDataSize */
    /* skip args->pData */
}

static inline void vn_encode_vkGetPipelineCacheData_reply(struct vn_cs_encoder *enc, const struct vn_command_vkGetPipelineCacheData *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkGetPipelineCacheData_EXT});

    vn_encode_VkResult(enc, &args->ret);
    /* skip args->device */
    /* skip args->pipelineCache */
    if (vn_encode_simple_pointer(enc, args->pDataSize))
        vn_encode_size_t(enc, args->pDataSize);
    if (args->pData) {
        vn_encode_array_size(enc, (args->pDataSize ? *args->pDataSize : 0));
        vn_encode_blob_array(enc, args->pData, (args->pDataSize ? *args->pDataSize : 0));
    } else {
        vn_encode_array_size(enc, 0);
    }
}

static inline void vn_decode_vkMergePipelineCaches_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkMergePipelineCaches *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    vn_decode_VkPipelineCache_lookup(dec, &args->dstCache);
    vn_decode_uint32_t(dec, &args->srcCacheCount);
    if (vn_peek_array_size(dec)) {
        const uint32_t iter_count = vn_decode_array_size(dec, args->srcCacheCount);
        args->pSrcCaches = vn_cs_decoder_alloc_temp(dec, sizeof(*args->pSrcCaches) * iter_count);
        if (!args->pSrcCaches) return;
        for (uint32_t i = 0; i < iter_count; i++)
            vn_decode_VkPipelineCache_lookup(dec, &((VkPipelineCache *)args->pSrcCaches)[i]);
    } else {
        vn_decode_array_size(dec, args->srcCacheCount);
        args->pSrcCaches = NULL;
    }
}

static inline void vn_replace_vkMergePipelineCaches_args_handle(struct vn_command_vkMergePipelineCaches *args)
{
    vn_replace_VkDevice_handle(&args->device);
    vn_replace_VkPipelineCache_handle(&args->dstCache);
    /* skip args->srcCacheCount */
    if (args->pSrcCaches) {
       for (uint32_t i = 0; i < args->srcCacheCount; i++)
            vn_replace_VkPipelineCache_handle(&((VkPipelineCache *)args->pSrcCaches)[i]);
    }
}

static inline void vn_encode_vkMergePipelineCaches_reply(struct vn_cs_encoder *enc, const struct vn_command_vkMergePipelineCaches *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkMergePipelineCaches_EXT});

    vn_encode_VkResult(enc, &args->ret);
    /* skip args->device */
    /* skip args->dstCache */
    /* skip args->srcCacheCount */
    /* skip args->pSrcCaches */
}

static inline void vn_dispatch_vkCreatePipelineCache(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkCreatePipelineCache args;

    if (!ctx->dispatch_vkCreatePipelineCache) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkCreatePipelineCache_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkCreatePipelineCache(ctx, &args);

#ifdef DEBUG
    if (!vn_cs_decoder_get_fatal(ctx->decoder) && vn_dispatch_should_log_result(args.ret))
        vn_dispatch_debug_log(ctx, "vkCreatePipelineCache returned %d", args.ret);
#endif

    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkCreatePipelineCache_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

static inline void vn_dispatch_vkDestroyPipelineCache(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkDestroyPipelineCache args;

    if (!ctx->dispatch_vkDestroyPipelineCache) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkDestroyPipelineCache_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkDestroyPipelineCache(ctx, &args);


    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkDestroyPipelineCache_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

static inline void vn_dispatch_vkGetPipelineCacheData(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkGetPipelineCacheData args;

    if (!ctx->dispatch_vkGetPipelineCacheData) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkGetPipelineCacheData_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkGetPipelineCacheData(ctx, &args);

#ifdef DEBUG
    if (!vn_cs_decoder_get_fatal(ctx->decoder) && vn_dispatch_should_log_result(args.ret))
        vn_dispatch_debug_log(ctx, "vkGetPipelineCacheData returned %d", args.ret);
#endif

    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkGetPipelineCacheData_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

static inline void vn_dispatch_vkMergePipelineCaches(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkMergePipelineCaches args;

    if (!ctx->dispatch_vkMergePipelineCaches) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkMergePipelineCaches_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkMergePipelineCaches(ctx, &args);

#ifdef DEBUG
    if (!vn_cs_decoder_get_fatal(ctx->decoder) && vn_dispatch_should_log_result(args.ret))
        vn_dispatch_debug_log(ctx, "vkMergePipelineCaches returned %d", args.ret);
#endif

    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkMergePipelineCaches_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

#pragma GCC diagnostic pop

#endif /* VN_PROTOCOL_RENDERER_PIPELINE_CACHE_H */
