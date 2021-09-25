/**
 * @file bp_iter.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#ifndef BACKPACK_ITER_H
#define BACKPACK_ITER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bp_types.h"

typedef struct bp_iter {
    void *(*init)(struct bp_iter *self);
    bool (*next)(struct bp_iter *self);
    void *(*get)(struct bp_iter *self);
    union {
        usize *el;
        usize idx;
    } current;
    void *coll;
} bp_iter_t;

#define BP_FOREACH(type, var, iter_ptr)                                      \
    for (type *var = (iter_ptr)->init(iter_ptr); (iter_ptr)->next(iter_ptr); \
         var       = (iter_ptr)->get(iter_ptr))

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_ITER_H
