/**
 * @file bp_ring.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#ifndef BACKPACK_RING_H
#define BACKPACK_RING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "bp_iter.h"
#include "bp_types.h"

typedef struct {
    usize _element_size;
    usize _max_size;
    usize _size;
    u8_t *_array;
    usize _head;
    usize _tail;
} bp_ring_t;

#define BP_RING_INVALID_INDEX 0xffFFffFF

#define BP_RING_INIT(array_)                                                       \
    {                                                                              \
        ._array = (u8_t *) (array_), ._element_size = sizeof((array_)[0]),         \
        ._max_size = sizeof(array_) / sizeof((array_)[0]), ._size = 0, ._head = 0, \
        ._tail = 0,                                                                \
    }

void *bp_ring_get(bp_ring_t *ring, usize idx);

void *bp_ring_peek(bp_ring_t *ring);

int bp_ring_pop(bp_ring_t *ring, void *el);

int bp_ring_push(bp_ring_t *ring, void *el);

usize bp_ring_find_idx(bp_ring_t *ring, void *param, bool (*cmp)(void *el, void *param));

void *bp_ring_find(bp_ring_t *ring, void *param, bool (*cmp)(void *el, void *param));

int bp_ring_clear(bp_ring_t *ring);

usize bp_ring_size(bp_ring_t *ring);

bp_iter_t bp_ring_iter(bp_ring_t *ring);

#ifdef __cplusplus
}
#endif

#endif  // TEST_BACKPACK_RING_H
