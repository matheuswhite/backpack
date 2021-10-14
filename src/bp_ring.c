/*!
 * @file bp_ring.c
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Implement the ring structure.
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

/*!
 * Macro to advance a ring buffer pointer. If the pointer is in the end of buffer, then
 * its value will be zero, otherwise it is increased by 1.
 * @param ring Reference to bp_ring.
 * @param ptr Pointer name to be advanced.
 * @return The next value of the pointer
 */
#define BP_RING_ADVANCE_PTR(ring, ptr) \
    (((ring)->ptr == ((ring)->_max_size - 1)) ? 0 : ((ring)->ptr + 1))

/*!
 * Macro to advance the head pointer. If the head pointer is in the end of buffer, then
 * its value will be zero, otherwise it is increased by 1.
 * @param ring Reference to bp_ring.
 * @return The next value of the head pointer
 */
#define BP_RING_ADVANCE_HEAD(ring) BP_RING_ADVANCE_PTR(ring, _head)

/*!
 * Macro to advance the tail pointer. If the tail pointer is in the end of buffer, then
 * its value will be zero, otherwise it is increased by 1.
 * @param ring Reference to bp_ring.
 * @return The next value of the tail pointer
 */
#define BP_RING_ADVANCE_TAIL(ring) BP_RING_ADVANCE_PTR(ring, _tail)

/*!
 * Fallback function for compare elements. It's used when the user doesn't provide an
 * function for compare. This function will compare the two elements byte by bytes.
 * @param left Reference to the first element to compare.
 * @param right Reference to the second element to compare.
 * @param el_size Size of each element.
 * @return true if the elements are equals
 * @return false if the elements are different
 */
static bool bp_ring_default_cmp(void *left, void *right, usize el_size);

/*!
 * Initialize iterator for bp_ring.
 * @param self Reference to the iterator itself.
 * @return Reference to the first element (at tail) in the ring buffer.
 */
static void *bp_ring_iter_init(struct bp_iter *self);

/*!
 * Move the iterator to the next position.
 * @param self Reference to the iterator itself.
 * @return false if the current element is the last element (at head).
 * @return true if the current element isn't the last element (at head).
 */
static bool bp_ring_iter_next(struct bp_iter *self);

/*!
 * Get the current iterator element.
 * @param self Reference to the iterator itself.
 * @return Reference to the current iterator element.
 */
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
