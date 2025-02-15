/*
 * Copyright 2020 Google LLC
 * SPDX-License-Identifier: MIT
 */

#ifndef VKR_CONTEXT_H
#define VKR_CONTEXT_H

#include "vkr_common.h"

#include "venus-protocol/vn_protocol_renderer_defines.h"
#include "virgl_resource.h"

#include "vkr_cs.h"

/*
 * When vkr_context_create_resource or vkr_context_import_resource is called, a
 * vkr_resource is created, and is valid until vkr_context_destroy_resource.
 */
struct vkr_resource {
   uint32_t res_id;

   enum virgl_resource_fd_type fd_type;

   union {
      /* valid when fd_type is dma_buf or opaque */
      int fd;
      /* valid when fd_type is shm */
      uint8_t *data;
   } u;

   size_t size;
};

enum vkr_context_validate_level {
   /* no validation */
   VKR_CONTEXT_VALIDATE_NONE,
   /* force enabling a subset of the validation layer */
   VKR_CONTEXT_VALIDATE_ON,
   /* force enabling the validation layer */
   VKR_CONTEXT_VALIDATE_FULL,
};

struct vkr_context {
   uint32_t ctx_id;
   vkr_renderer_retire_fence_callback_type retire_fence;

   char *debug_name;
   enum vkr_context_validate_level validate_level;
   bool validate_fatal;

   mtx_t mutex;

   struct list_head rings;
   struct hash_table *object_table;
   struct hash_table *resource_table;

   struct vkr_cs_encoder encoder;
   struct vkr_cs_decoder decoder;
   struct vn_dispatch_context dispatch;

   struct vkr_queue *sync_queues[64];

   struct vkr_instance *instance;
   char *instance_name;

   struct list_head head;
};

struct vkr_context *
vkr_context_create(uint32_t ctx_id,
                   vkr_renderer_retire_fence_callback_type cb,
                   size_t debug_len,
                   const char *debug_name);

void
vkr_context_destroy(struct vkr_context *ctx);

bool
vkr_context_submit_fence(struct vkr_context *ctx,
                         uint32_t flags,
                         uint32_t ring_idx,
                         uint64_t fence_id);

bool
vkr_context_submit_cmd(struct vkr_context *ctx, const void *buffer, size_t size);

bool
vkr_context_create_resource(struct vkr_context *ctx,
                            uint32_t res_id,
                            uint64_t blob_id,
                            uint64_t blob_size,
                            uint32_t blob_flags,
                            struct virgl_context_blob *out_blob);

bool
vkr_context_import_resource(struct vkr_context *ctx,
                            uint32_t res_id,
                            enum virgl_resource_fd_type fd_type,
                            int fd,
                            uint64_t size);

void
vkr_context_destroy_resource(struct vkr_context *ctx, uint32_t res_id);

static inline struct vkr_resource *
vkr_context_get_resource(struct vkr_context *ctx, uint32_t res_id)
{
   const struct hash_entry *entry = _mesa_hash_table_search(ctx->resource_table, &res_id);
   return likely(entry) ? entry->data : NULL;
}

static inline bool
vkr_context_validate_object_id(struct vkr_context *ctx, vkr_object_id id)
{
   if (unlikely(!id || _mesa_hash_table_search(ctx->object_table, &id))) {
      vkr_log("invalid object id %" PRIu64, id);
      vkr_cs_decoder_set_fatal(&ctx->decoder);
      return false;
   }

   return true;
}

static inline void *
vkr_context_alloc_object(UNUSED struct vkr_context *ctx,
                         size_t size,
                         VkObjectType type,
                         const void *id_handle)
{
   const vkr_object_id id = vkr_cs_handle_load_id((const void **)id_handle, type);
   if (!vkr_context_validate_object_id(ctx, id))
      return NULL;

   return vkr_object_alloc(size, type, id);
}

void
vkr_context_free_object(struct hash_entry *entry);

static inline void
vkr_context_add_object(struct vkr_context *ctx, struct vkr_object *obj)
{
   assert(vkr_is_recognized_object_type(obj->type));
   assert(obj->id);
   assert(!_mesa_hash_table_search(ctx->object_table, &obj->id));

   _mesa_hash_table_insert(ctx->object_table, &obj->id, obj);
}

static inline void
vkr_context_remove_object(struct vkr_context *ctx, struct vkr_object *obj)
{
   assert(_mesa_hash_table_search(ctx->object_table, &obj->id));

   struct hash_entry *entry = _mesa_hash_table_search(ctx->object_table, &obj->id);
   if (likely(entry)) {
      vkr_context_free_object(entry);
      _mesa_hash_table_remove(ctx->object_table, entry);
   }
}

static inline void
vkr_context_remove_objects(struct vkr_context *ctx, struct list_head *objects)
{
   struct vkr_object *obj, *tmp;
   LIST_FOR_EACH_ENTRY_SAFE (obj, tmp, objects, track_head)
      vkr_context_remove_object(ctx, obj);
   /* objects should be reinitialized if to be reused */
}

static inline void *
vkr_context_get_object(struct vkr_context *ctx, vkr_object_id obj_id)
{
   const struct hash_entry *entry = _mesa_hash_table_search(ctx->object_table, &obj_id);
   return likely(entry) ? entry->data : NULL;
}

void
vkr_context_add_instance(struct vkr_context *ctx,
                         struct vkr_instance *instance,
                         const char *name);

void
vkr_context_remove_instance(struct vkr_context *ctx, struct vkr_instance *instance);

#endif /* VKR_CONTEXT_H */
