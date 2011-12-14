/* -*- coding: utf-8 -*-
 * ----------------------------------------------------------------------
 * Copyright © 2011, RedJack, LLC.
 * All rights reserved.
 *
 * Please see the LICENSE.txt file in this distribution for license
 * details.
 * ----------------------------------------------------------------------
 */

#ifndef LIBCORK_DS_MANAGED_BUFFER_H
#define LIBCORK_DS_MANAGED_BUFFER_H


#include <libcork/core/allocator.h>
#include <libcork/core/types.h>
#include <libcork/ds/slice.h>


/*-----------------------------------------------------------------------
 * Managed buffers
 */

struct cork_managed_buffer;

struct cork_managed_buffer_iface {
    /* Free the contents of a managed buffer, and the managed buffer
     * object itself. */
    void
    (*free)(struct cork_managed_buffer *buf);
};


struct cork_managed_buffer {
    /* The buffer that this instance manages */
    const void  *buf;
    /* The size of buf */
    size_t  size;
    /* A reference count for the buffer.  If this drops to 0, the buffer
     * will be finalized. */
    volatile int  ref_count;
    /* The managed buffer implementation for this instance. */
    struct cork_managed_buffer_iface  *iface;
};


struct cork_managed_buffer *
cork_managed_buffer_new_copy(struct cork_alloc *alloc,
                             const void *buf, size_t size);


typedef void
(*cork_managed_buffer_freer)(struct cork_alloc *alloc,
                             void *buf, size_t size);

struct cork_managed_buffer *
cork_managed_buffer_new(struct cork_alloc *alloc,
                        const void *buf, size_t size,
                        cork_managed_buffer_freer free);


struct cork_managed_buffer *
cork_managed_buffer_ref(struct cork_managed_buffer *buf);

void
cork_managed_buffer_unref(struct cork_managed_buffer *buf);


bool
cork_managed_buffer_slice(struct cork_slice *dest,
                          struct cork_managed_buffer *buffer,
                          size_t offset, size_t length);

bool
cork_managed_buffer_slice_offset(struct cork_slice *dest,
                                 struct cork_managed_buffer *buffer,
                                 size_t offset);


#endif /* LIBCORK_DS_MANAGED_BUFFER_H */
