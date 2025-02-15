/* This file is generated by venus-protocol.  See vn_protocol_renderer.h. */

/*
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: MIT
 */

#ifndef VN_PROTOCOL_RENDERER_SHADER_MODULE_H
#define VN_PROTOCOL_RENDERER_SHADER_MODULE_H

#include "vn_protocol_renderer_structs.h"

#pragma GCC diagnostic push
#if !defined(__clang__) && defined(__GNUC__) && __GNUC__ >= 12
#pragma GCC diagnostic ignored "-Wdangling-pointer"
#endif
#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wunused-parameter"

static inline void vn_decode_vkCreateShaderModule_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkCreateShaderModule *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    if (vn_decode_simple_pointer(dec)) {
        args->pCreateInfo = vn_cs_decoder_alloc_temp(dec, sizeof(*args->pCreateInfo));
        if (!args->pCreateInfo) return;
        vn_decode_VkShaderModuleCreateInfo_temp(dec, (VkShaderModuleCreateInfo *)args->pCreateInfo);
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
        args->pShaderModule = vn_cs_decoder_alloc_temp(dec, sizeof(*args->pShaderModule));
        if (!args->pShaderModule) return;
        vn_decode_VkShaderModule(dec, args->pShaderModule);
    } else {
        args->pShaderModule = NULL;
        vn_cs_decoder_set_fatal(dec);
    }
}

static inline void vn_replace_vkCreateShaderModule_args_handle(struct vn_command_vkCreateShaderModule *args)
{
    vn_replace_VkDevice_handle(&args->device);
    if (args->pCreateInfo)
        vn_replace_VkShaderModuleCreateInfo_handle((VkShaderModuleCreateInfo *)args->pCreateInfo);
    /* skip args->pAllocator */
    /* skip args->pShaderModule */
}

static inline void vn_encode_vkCreateShaderModule_reply(struct vn_cs_encoder *enc, const struct vn_command_vkCreateShaderModule *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkCreateShaderModule_EXT});

    vn_encode_VkResult(enc, &args->ret);
    /* skip args->device */
    /* skip args->pCreateInfo */
    /* skip args->pAllocator */
    if (vn_encode_simple_pointer(enc, args->pShaderModule))
        vn_encode_VkShaderModule(enc, args->pShaderModule);
}

static inline void vn_decode_vkDestroyShaderModule_args_temp(struct vn_cs_decoder *dec, struct vn_command_vkDestroyShaderModule *args)
{
    vn_decode_VkDevice_lookup(dec, &args->device);
    vn_decode_VkShaderModule_lookup(dec, &args->shaderModule);
    if (vn_decode_simple_pointer(dec)) {
        vn_cs_decoder_set_fatal(dec);
    } else {
        args->pAllocator = NULL;
    }
}

static inline void vn_replace_vkDestroyShaderModule_args_handle(struct vn_command_vkDestroyShaderModule *args)
{
    vn_replace_VkDevice_handle(&args->device);
    vn_replace_VkShaderModule_handle(&args->shaderModule);
    /* skip args->pAllocator */
}

static inline void vn_encode_vkDestroyShaderModule_reply(struct vn_cs_encoder *enc, const struct vn_command_vkDestroyShaderModule *args)
{
    vn_encode_VkCommandTypeEXT(enc, &(VkCommandTypeEXT){VK_COMMAND_TYPE_vkDestroyShaderModule_EXT});

    /* skip args->device */
    /* skip args->shaderModule */
    /* skip args->pAllocator */
}

static inline void vn_dispatch_vkCreateShaderModule(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkCreateShaderModule args;

    if (!ctx->dispatch_vkCreateShaderModule) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkCreateShaderModule_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkCreateShaderModule(ctx, &args);

#ifdef DEBUG
    if (!vn_cs_decoder_get_fatal(ctx->decoder) && vn_dispatch_should_log_result(args.ret))
        vn_dispatch_debug_log(ctx, "vkCreateShaderModule returned %d", args.ret);
#endif

    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkCreateShaderModule_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

static inline void vn_dispatch_vkDestroyShaderModule(struct vn_dispatch_context *ctx, VkCommandFlagsEXT flags)
{
    struct vn_command_vkDestroyShaderModule args;

    if (!ctx->dispatch_vkDestroyShaderModule) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    vn_decode_vkDestroyShaderModule_args_temp(ctx->decoder, &args);
    if (!args.device) {
        vn_cs_decoder_set_fatal(ctx->decoder);
        return;
    }

    if (!vn_cs_decoder_get_fatal(ctx->decoder))
        ctx->dispatch_vkDestroyShaderModule(ctx, &args);


    if (!vn_cs_decoder_get_fatal(ctx->decoder) && (flags & VK_COMMAND_GENERATE_REPLY_BIT_EXT))
       vn_encode_vkDestroyShaderModule_reply(ctx->encoder, &args);

    vn_cs_decoder_reset_temp_pool(ctx->decoder);
}

#pragma GCC diagnostic pop

#endif /* VN_PROTOCOL_RENDERER_SHADER_MODULE_H */
