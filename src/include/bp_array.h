/**
 * @file bp_array.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#ifndef BACKPACK_ARRAY_H
#define BACKPACK_ARRAY_H

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
} bp_array_t;

#define BP_ARRAY_INVALID_INDEX 0xffFFffFF

#define BP_ARRAY_INIT(array_)                                          \
    {                                                                  \
        ._element_size = sizeof((array_)[0]),                          \
        ._max_size = sizeof(array_) / sizeof((array_)[0]), ._size = 0, \
        ._array = (u8_t *) (array_),                                   \
    }

#define BP_ARRAY_START(array_, size_)                                        \
    {                                                                        \
        ._element_size = sizeof((array_)[0]),                                \
        ._max_size = sizeof(array_) / sizeof((array_)[0]), ._size = (size_), \
        ._array = (u8_t *) (array_),                                         \
    }

void *bp_array_get(bp_array_t *array, usize idx);

int bp_array_push(bp_array_t *array, void *el);

int bp_array_del(bp_array_t *array, usize idx);

usize bp_array_find_idx(bp_array_t *array, void *param,
                        bool (*cmp)(void *el, void *param));

void *bp_array_find(bp_array_t *array, void *param, bool (*cmp)(void *el, void *param));

int bp_array_clear(bp_array_t *array);

usize bp_array_size(bp_array_t *array);

bp_iter_t bp_array_iter(bp_array_t *array);

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_ARRAY_H
