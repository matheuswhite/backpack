/**
 * @file bp_ring.c
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#include "bp_ring.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BP_RING_ADVANCE_PTR(ring, ptr) \
    (((ring)->ptr == ((ring)->_max_size - 1)) ? 0 : ((ring)->ptr + 1))

#define BP_RING_ADVANCE_HEAD(ring) BP_RING_ADVANCE_PTR(ring, _head)

#define BP_RING_ADVANCE_TAIL(ring) BP_RING_ADVANCE_PTR(ring, _tail)

static bool bp_ring_default_cmp(void *left, void *right, usize el_size);

static void *bp_ring_iter_init(struct bp_iter *self);

static bool bp_ring_iter_next(struct bp_iter *self);

static void *bp_ring_iter_get(struct bp_iter *self);

void *bp_ring_get(bp_ring_t *ring, usize idx)
{
    if (ring == NULL) {
        return NULL;
    }

    if (idx >= ring->_size) {
        return NULL;
    }

    idx += ring->_tail;
    if (idx >= ring->_max_size) {
        idx -= ring->_max_size;
    }

    return &ring->_array[idx * ring->_element_size];
}

void *bp_ring_peek(bp_ring_t *ring)
{
    if (ring == NULL) {
        return NULL;
    }

    if (ring->_size == 0) {
        return NULL;
    }

    return &ring->_array[ring->_tail * ring->_element_size];
}

int bp_ring_pop(bp_ring_t *ring, void *el)
{
    if (ring == NULL || el == NULL) {
        return -ENODEV;
    }

    if (ring->_size == 0) {
        return -ENOENT;
    }

    memcpy(el, &ring->_array[ring->_tail * ring->_element_size], ring->_element_size);
    ring->_size -= 1;
    ring->_tail = BP_RING_ADVANCE_TAIL(ring);

    return 0;
}

int bp_ring_push(bp_ring_t *ring, void *el)
{
    if (ring == NULL || el == NULL) {
        return -ENODEV;
    }

    void *ptr = &ring->_array[ring->_head * ring->_element_size];
    memcpy(ptr, el, ring->_element_size);

    ring->_head = BP_RING_ADVANCE_HEAD(ring);
    if (ring->_size < ring->_max_size) {
        ring->_size += 1;
    } else {
        ring->_tail = BP_RING_ADVANCE_TAIL(ring);
    }

    return 0;
}

usize bp_ring_find_idx(bp_ring_t *ring, void *param, bool (*cmp)(void *el, void *param))
{
    if (ring == NULL || param == NULL) {
        return BP_RING_INVALID_INDEX;
    }

    bool res;

    for (usize i = 0; i < ring->_size; ++i) {
        if (cmp != NULL) {
            res = cmp(bp_ring_get(ring, i), param);
        } else {
            res = bp_ring_default_cmp(bp_ring_get(ring, i), param, ring->_element_size);
        }

        if (res) {
            return i;
        }
    }

    return BP_RING_INVALID_INDEX;
}

void *bp_ring_find(bp_ring_t *ring, void *param, bool (*cmp)(void *el, void *param))
{
    if (ring == NULL || param == NULL) {
        return NULL;
    }

    bool res;
    void *el;

    for (usize i = 0; i < ring->_size; ++i) {
        el = bp_ring_get(ring, i);
        if (cmp != NULL) {
            res = cmp(el, param);
        } else {
            res = bp_ring_default_cmp(el, param, ring->_element_size);
        }

        if (res) {
            return el;
        }
    }

    return NULL;
}

int bp_ring_clear(bp_ring_t *ring)
{
    if (ring == NULL) {
        return -ENODEV;
    }

    ring->_size = 0;
    ring->_head = 0;
    ring->_tail = 0;

    return 0;
}

usize bp_ring_size(bp_ring_t *ring)
{
    if (ring == NULL) {
        return 0;
    }

    return ring->_size;
}

bp_iter_t bp_ring_iter(bp_ring_t *ring)
{
    bp_iter_t iter = {
        .init        = bp_ring_iter_init,
        .next        = bp_ring_iter_next,
        .get         = bp_ring_iter_get,
        .current.idx = 0,
        .coll        = ring,
    };

    return iter;
}

static bool bp_ring_default_cmp(void *left, void *right, usize el_size)
{
    bool res;
    u8_t *left_ptr  = NULL;
    u8_t *right_ptr = NULL;

    for (size_t i = 0; i < el_size; i++) {
        left_ptr  = (u8_t *) left + i;
        right_ptr = (u8_t *) right + i;
        res       = (bool) (*left_ptr - *right_ptr);
        if (res != 0) {
            return false;
        }
    }

    return true;
}

static void *bp_ring_iter_init(struct bp_iter *self)
{
    bp_ring_t *ring = self->coll;

    self->current.idx = ring->_tail;

    return bp_ring_peek(ring);
}

static bool bp_ring_iter_next(struct bp_iter *self)
{
    bp_ring_t *ring = self->coll;

    if (ring->_head == self->current.idx) {
        return false;
    }

    self->current.idx =
        ((self->current.idx == (ring->_max_size - 1)) ? 0 : (self->current.idx + 1));

    return true;
}

static void *bp_ring_iter_get(struct bp_iter *self)
{
    return bp_ring_get(self->coll, self->current.idx);
}

#ifdef __cplusplus
}
#endif
