/*!
 * @file bp_array.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Specifies the array structure. This structure works as a buffer, where the
 * develop could insert the elements at the end and remove elements at any position.
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */
#ifndef BACKPACK_ARRAY_H
#define BACKPACK_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "bp_iter.h"

/*!
 * Value representing an invalid index
 */
#define BP_ARRAY_INVALID_INDEX 0xffFFffFF

/*!
 * Macro to initialize a bp_array.
 * @param array_ buffer where the elements will be stored.
 */
#define BP_ARRAY_INIT(array_)                                          \
    {                                                                  \
        ._element_size = sizeof((array_)[0]),                          \
        ._capacity = sizeof(array_) / sizeof((array_)[0]), ._size = 0, \
        ._array = (uint8_t *) (array_),                                \
    }

/*!
 * Macro to initialize a bp_array, which have initials elements.
 * @param array_ buffer where the elements will be stored.
 * @param size_ Number of elements already presents in the buffer.
 */
#define BP_ARRAY_START(array_, size_)                                        \
    {                                                                        \
        ._element_size = sizeof((array_)[0]),                                \
        ._capacity = sizeof(array_) / sizeof((array_)[0]), ._size = (size_), \
        ._array = (uint8_t *) (array_),                                      \
    }

/*!
 * Struct with metadata about an external buffer.
 *
 * @note This struct need an external buffer to work properly.
 */
typedef struct {
    size_t _element_size; /*!< Size (in bytes) of a single element in the array. */
    size_t _capacity;     /*!< Maximum number of elements in the array. */
    size_t _size;         /*!< Current number of elements in the array. */
    uint8_t *_array; /*!< Reference to the buffer, where the elements will be stored. */
} bp_array_t;

/*!
 * Push an element at the end of array.
 * @param array Reference to bp_array.
 * @param el Reference to the element to be pushed.
 * @return 0 on success.
 * @return -ENODEV if the 'array' or the 'el' argument is NULL.
 * @return -ENOMEM if the array is full.
 */
int bp_array_push(bp_array_t *array, void *el);

/*!
 * Get an element from the array, based on its position.
 * @param array Reference to bp_array.
 * @param idx Element index.
 * @return A reference to the desired element.
 * @return NULL if the index is out of range or the 'array' argument is NULL.
 */
void *bp_array_get(bp_array_t *array, size_t idx);

/*!
 * Delete an array element, based on its position.
 * @param array Reference to bp_array.
 * @param idx Element idx.
 * @return 0 on success.
 * @return -ENODEV if the 'array' argument is NULL.
 * @return -EFAULT if the index 'idx' is out of range.
 */
int bp_array_del(bp_array_t *array, size_t idx);

/*!
 * Find the index of an element, based at some parameter related to the element. This
 * parameter could be the element itself, or some field of its type. The match will
 * be done based on cmp function pointer. If the cmp function pointer argument is null,
 * then the elements will be compared with the parameter byte by byte.
 * @param array Reference to bp_array.
 * @param param Reference to the parameter used to compare elements.
 * @param cmp Function to compare an element with the parameter passed at argument param.
 * @return The index of found element.
 * @return BP_ARRAY_INVALID_INDEX if the element wasn't found or if the 'array' or the
 * 'param' argument is NULL.
 */
size_t bp_array_find_idx(bp_array_t *array, void *param,
                         bool (*cmp)(void *el, void *param));

/*!
 * Find the element in the array, based at some parameter related to the element. This
 * parameter could be the element itself, or some field of its type. The match will be
 * done based on cmp function pointer. If the cmp function point argument is null, then
 * the elements will be compared with the parameter byte by byte.
 * @param array Reference to bp_array.
 * @param param Reference to the parameter used to compare elements.
 * @param cmp Function to compare an element with the parameter passed at argument param.
 * @return A reference to the found element.
 * @return NULL if the element wasn't found or if the 'array' or the 'param' argument is
 * NULL.
 */
void *bp_array_find(bp_array_t *array, void *param, bool (*cmp)(void *el, void *param));

/*!
 * Drop all elements in the array.
 *
 * @warning After this function the array size is zero, but the elements stay in the
 * buffer.
 *
 * @param array Reference to bp_array.
 * @return 0 on success.
 * @return -ENODEV if the 'array' argument is NULL.
 */
int bp_array_clear(bp_array_t *array);

/*!
 * Get the array size.
 * @param array Reference to bp_array.
 * @return The size of array.
 * @return 0 if the 'array' argument is NULL.
 */
size_t bp_array_size(bp_array_t *array);

/*!
 * Get a iterator to walk through the bp_array.
 *
 * @warning This function doesn't check if the array argument is null. So if this argument
 * is null, a crash will occur. That check must be done outside the function.
 *
 * @param array Reference to bp_array.
 * @return A new iterator instance for the bp_array.
 */
bp_iter_t bp_array_iter(bp_array_t *array);

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_ARRAY_H
