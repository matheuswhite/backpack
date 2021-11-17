/*!
 * @file bp_ring.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Specifies the ring structure. This structure works as a circular buffer. When
 * the buffer is in its maximum capacity, and a new element need be pushed into the
 * buffer, the oldest element is replaced by the new element.
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

/*!
 * Value representing an invalid index
 */
#define BP_RING_INVALID_INDEX 0xffFFffFF

/*!
 * Macro to initialize a bp_ring
 * @param array_ Buffer where the elements will be stored.
 */
#define BP_RING_INIT(array_)                                                       \
    {                                                                              \
        ._array = (u8_t *) (array_), ._element_size = sizeof((array_)[0]),         \
        ._capacity = sizeof(array_) / sizeof((array_)[0]), ._size = 0, ._head = 0, \
        ._tail = 0,                                                                \
    }

/*!
 * Struct with metadata about the ring buffer.
 */
typedef struct {
    u8_t *_array;        /*!< Reference to the buffer itself. */
    usize _element_size; /*!< Size (in bytes) of a single element in the array. */
    usize _capacity;     /*!< Maximum number of elements in the ring buffer. */
    usize _size;         /*!< Current number of elements in the ring buffer. */
    usize _head;         /*!< Index of the head of the ring buffer. */
    usize _tail;         /*!< Index of the tail of the ring buffer. */
} bp_ring_t;

/*!
 * Get an element from the ring buffer, based on its position.
 * @param ring Reference to bp_ring.
 * @param idx Element index.
 * @return A reference to the desired element
 * @return NULL if the index is out of range or the 'ring' argument is NULL.
 */
void *bp_ring_get(bp_ring_t *ring, usize idx);

/*!
 * Get the oldest element (at tail) in the ring buffer.
 * @param ring Reference to bp_ring.
 * @return A reference to the oldest element.
 * @return NULL if the 'ring' argument is NULL or if the ring is empty.
 */
void *bp_ring_peek(bp_ring_t *ring);

/*!
 * Remove the oldest element (at tail) of the ring buffer and put it in el argument
 * variable.
 * @param ring Reference to bp_ring.
 * @param el [out] Reference to a variable where the removed element will be put.
 * @return 0 on success.
 * @return -ENODEV if the 'ring' argument is NULL.
 * @return -ENOENT if the ring is empty.
 */
int bp_ring_pop(bp_ring_t *ring, void *el);

/*!
 * Push an element at the end (at head) of ring buffer.
 * @param ring Reference to bp_ring.
 * @param el Reference to the element to be pushed.
 * @return 0 on success.
 * @return -ENODEV if the 'ring' or the 'el' argument is NULL.
 */
int bp_ring_push(bp_ring_t *ring, void *el);

/*!
 * Find the index of an element, based at some parameter related to the element. This
 * parameter could be the element itself, or some field of its type. The match will be
 * done based on cmp function pointer. If the cmp function pointer argument is null, then
 * the elements will be compared with the parameter byte by byte.
 * @param ring Reference to bp_ring.
 * @param param Reference to the parameter used to compare elements.
 * @param cmp Function to compare an element with the parameter passed at argument param.
 * @return The index of found element.
 * @return BP_RING_INVALID_INDEX if the element wasn't found or if the 'ring' or the
 * 'param' argument is NULL.
 */
usize bp_ring_find_idx(bp_ring_t *ring, void *param, bool (*cmp)(void *el, void *param));

/*!
 * Find the element in the ring buffer, based at some parameter related to the element.
 * This parameter could be the element itself, or some field of its type. The match will
 * be done based on cmp function pointer. If the cmp function point argument is null, then
 * the elements will be compared with the parameter byte by byte.
 * @param ring Reference to bp_ring.
 * @param param Reference to the parameter used to compare elements.
 * @param cmp Function to compare an element with the parameter passed at argument param.
 * @return A reference to the found element.
 * @return NULL if the element wasn't found or if the 'ring' or the 'param' argument is
 * NULL.
 */
void *bp_ring_find(bp_ring_t *ring, void *param, bool (*cmp)(void *el, void *param));

/*!
 * Drop all elements in the ring buffer.
 *
 * @warning After this function the ring buffer size is zero, but the elements stay in the
 * buffer.
 *
 * @param ring Reference to bp_ring.
 * @return 0 on success.
 * @return -ENODEV if the 'ring' argument is NULL.
 */
int bp_ring_clear(bp_ring_t *ring);

/*!
 * Get the ring buffer size.
 * @param ring Reference to bp_ring.
 * @return The size of ring buffer.
 * @return 0 if the 'ring' argument is null.
 */
usize bp_ring_size(bp_ring_t *ring);

/*!
 * Get a iterator to walk through the bp_ring.
 *
 * @warning This function doesn't check if the ring argument is null. So if this argument
 * is null, a crash will occur. That check must be done outside the function.
 *
 * @param ring Reference to bp_ring.
 * @return A new iterator instance for the bp_ring.
 */
bp_iter_t bp_ring_iter(bp_ring_t *ring);

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_RING_H
