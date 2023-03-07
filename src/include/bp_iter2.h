/**
 * @file bp_iter2.h
 * @author Matheus T. dos Santos (tenoriomatheus0@edge.ufal.br)
 * @brief
 * @version 0.1.0
 * @date 07/03/2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BACKPACK_ITER_2_H
#define BACKPACK_ITER_2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
#define __NULL_SYMBOL nullptr
#else
#define __NULL_SYMBOL NULL
#endif

#define BP_FOREACH_FOWARD(type, var, iter_ptr)                                   \
    for (type *var = (type *) bp_iterator_first(iter_ptr); var != __NULL_SYMBOL; \
         var       = (type *) bp_iterator_next(iter_ptr))

#define BP_FOREACH_REV(type, var, iter_ptr)                            \
    for (type *var = bp_iterator_last(iter_ptr); var != __NULL_SYMBOL; \
         var       = bp_iterator_prev(iter_ptr))


typedef struct bp_iterator {
    struct bp_iterator_vtable *vtable;
    void *coll;
    size_t current_idx;
} bp_iterator_t;

struct bp_iterator_vtable {
    void *(*first)(struct bp_iterator *self);
    void *(*last)(struct bp_iterator *self);
    void *(*next)(struct bp_iterator *self);
    void *(*prev)(struct bp_iterator *self);
};

static inline void *bp_iterator_first(bp_iterator_t *it)
{
    return it->vtable->first(it);
}

static inline void *bp_iterator_last(bp_iterator_t *it)
{
    return it->vtable->last(it);
}

static inline void *bp_iterator_next(bp_iterator_t *it)
{
    return it->vtable->next(it);
}

static inline void *bp_iterator_prev(bp_iterator_t *it)
{
    return it->vtable->prev(it);
}

#ifdef __cplusplus
}
#endif

#endif /* BACKPACK_ITER_2_H */
