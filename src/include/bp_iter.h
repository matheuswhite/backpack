/*!
 * @file bp_iter.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Specifies the generic iterator structure. The iterator is a interface with 3
 * method. Thus, each data structure implements the way the iterator will walk
 * through its elements. The user also que create custom iterators, for its structures,
 * implementing the methods: init, next and get.
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */
#ifndef BACKPACK_ITER_H
#define BACKPACK_ITER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bp_types.h"

/*!
 * Macro to easy iterator usage in loops.
 * @param type The type of variable hold by the data structure represented by the
 * iterator. The macro use this type as pointer.
 * @param var Variable name that reference the element got by the iterator through the
 * loops. This variable is a pointer.
 * @param inter_ptr Reference to iterator variable.
 */
#define BP_FOREACH(type, var, iter_ptr)                                               \
    for (type *var = (type *) (iter_ptr)->init(iter_ptr); (iter_ptr)->next(iter_ptr); \
         var       = (type *) (iter_ptr)->get(iter_ptr))

/*!
 * Struct with iterator metadata.
 *
 * @note The functions inside the structures need be filled up by concrete implementation.
 *
 * @note The data structure represented by it's iterator is declared outside it. Only a
 * reference is stored inside it.
 */
typedef struct bp_iter {
    void *(*init)(struct bp_iter
                      *self); /*!< Function to get the first element of data structure. */
    bool (*next)(struct bp_iter *self); /*!< Function to move the iterator for the next
                                           element in the sequence. Must return false if
                                           the current element is the last. */
    void *(*get)(
        struct bp_iter *self); /*!< Function to get the current iterator element. */
    union {
        usize *el; /*!< Reference to current iterator element. */
        usize idx; /*!< Index of current iterator element in the data structure itself. */
    } current;     /*!< Union with the current iterator element address */
    void *coll;    /*!< Reference to the data structure itself. */
} bp_iter_t;

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_ITER_H
