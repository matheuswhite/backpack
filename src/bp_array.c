/*!
 * @file bp_array.c
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Implement the array structure.
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */
#include "bp_array.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Fallback function for compare elements. It's used when the user doesn't provide an
 * function for compare. This function will compare the two elements byte by byte.
 * @param left Reference to the first element to compare.
 * @param right Reference to the seconds element to compare.
 * @param el_size Size of each element.
 * @return true if the elements are equals
 * @return false if the elements are different
 */
static bool bp_array_default_cmp(void *left, void *right, usize el_size);

/*!
 * Initialize iterator for bp_array.
 * @param self Reference to the iterator itself.
 * @return Reference to the first element in the array.
 */
static void *bp_array_iter_init(struct bp_iter *self);

/*!
 * Move the iterator to the next position.
 * @param self Reference to the iterator itself.
 * @return false if the current element is the last element.
 * @return true if the current element isn't the last element.
 */
static bool bp_array_iter_next(struct bp_iter *self);

/*!
 * Get the current iterator element.
 * @param self Reference to the iterator itself.
 * @return Reference to the current iterator element.
 */
static void *bp_array_iter_get(struct bp_iter *self);

void *bp_array_get(bp_array_t *array, usize idx)
{
    if (array == NULL) {
        return NULL;
    }

    if (idx >= array->_size) {
        return NULL;
    }

    return &array->_array[idx * array->_element_size];
}

int bp_array_push(bp_array_t *array, void *el)
{
    if (array == NULL || el == NULL) {
        return -ENODEV;
    }

    if (array->_size >= array->_max_size) {
        return -ENOMEM;
    }

    void *ptr = &array->_array[array->_size * array->_element_size];
    memcpy(ptr, el, array->_element_size);
    array->_size += 1;

    return 0;
}

int bp_array_del(bp_array_t *array, usize idx)
{
    if (array == NULL) {
        return -ENODEV;
    }

    if (idx >= array->_size) {
        return -EFAULT;
    }

    if (idx == array->_size - 1) {
        memset(bp_array_get(array, idx), 0, array->_element_size);
    } else {
        for (usize i = idx; i < (array->_size - 1); i++) {
            memcpy(bp_array_get(array, i), bp_array_get(array, i + 1),
                   array->_element_size);
        }
    }

    array->_size -= 1;

    return 0;
}

usize bp_array_find_idx(bp_array_t *array, void *param,
                        bool (*cmp)(void *el, void *param))
{
    if (array == NULL || param == NULL) {
        return BP_ARRAY_INVALID_INDEX;
    }

    bool res;

    for (usize i = 0; i < array->_size; ++i) {
        if (cmp != NULL) {
            res = cmp(bp_array_get(array, i), param);
        } else {
            res =
                bp_array_default_cmp(bp_array_get(array, i), param, array->_element_size);
        }

        if (res) {
            return i;
        }
    }

    return BP_ARRAY_INVALID_INDEX;
}

void *bp_array_find(bp_array_t *array, void *param, bool (*cmp)(void *el, void *param))
{
    if (array == NULL || param == NULL) {
        return NULL;
    }

    bool res;

    for (usize i = 0; i < array->_size; ++i) {
        if (cmp != NULL) {
            res = cmp(bp_array_get(array, i), param);
        } else {
            res =
                bp_array_default_cmp(bp_array_get(array, i), param, array->_element_size);
        }

        if (res) {
            return bp_array_get(array, i);
        }
    }

    return NULL;
}

int bp_array_clear(bp_array_t *array)
{
    if (array == NULL) {
        return -ENODEV;
    }

    array->_size = 0;

    return 0;
}

usize bp_array_size(bp_array_t *array)
{
    if (array == NULL) {
        return 0;
    }

    return array->_size;
}

bp_iter_t bp_array_iter(bp_array_t *array)
{
    bp_iter_t iter = {
        .init        = bp_array_iter_init,
        .next        = bp_array_iter_next,
        .get         = bp_array_iter_get,
        .current.idx = 0,
        .coll        = array,
    };

    return iter;
}

static bool bp_array_default_cmp(void *left, void *right, usize el_size)
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

static void *bp_array_iter_init(struct bp_iter *self)
{
    self->current.idx = 0;

    return bp_array_get(self->coll, 0);
}

static bool bp_array_iter_next(struct bp_iter *self)
{
    bp_array_t *array = self->coll;
    if (self->current.idx >= array->_size) {
        return false;
    }

    self->current.idx += 1;
    return true;
}

static void *bp_array_iter_get(struct bp_iter *self)
{
    return bp_array_get(self->coll, self->current.idx);
}

#ifdef __cplusplus
}
#endif
