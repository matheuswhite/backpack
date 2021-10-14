/*!
 * @file bp_heap.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Specifies the heap structure. the heap could be a Min-Heap or a Max-Heap.
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#ifndef BACKPACK_HEAP_H
#define BACKPACK_HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bp_array.h"

/*!
 * Type for heap compare function. The return must be 0 for equals values, less than 0 if
 * (<= 0) the left is less than the right, and greater than 0 (>= 0) if the left is
 * greater than the right.
 */
typedef int (*bp_heap_cmp_t)(void *left, void *right);

/*!
 * Enumerate the kinds of heap. The available options are Min-Heap or Max-Heap.
 */
typedef enum {
    BP_MIN_HEAP, /*!< Option for Min-Heap. */
    BP_MAX_HEAP, /*!< Option for Max-Heap. */
} bp_heap_kind_t;

/*!
 * Structure with metadata about the heap.
 *
 * @note This struct need an external buffer to work properly.
 */
typedef struct {
    bp_array_t _coll;     /*!< Array that holds the heap elements. */
    bp_heap_kind_t _kind; /*!< Kind of the heap. */
    bp_heap_cmp_t _cmp;   /*!< Function to compare two elements of the heap. */
} bp_heap_t;

/*!
 * Macro to initialize a Min-Heap.
 * @param array_ Buffer where the elements will be stored.
 * @param cmp_ Function to compare the heap elements.
 */
#define BP_MIN_HEAP_INIT(array_, cmp_)                                     \
    {                                                                      \
        ._coll = BP_ARRAY_INIT(array_), ._kind = BP_MIN_HEAP, ._cmp = cmp_ \
    }

/*!
 * Macro to initialize a Max-Heap.
 * @param array_ Buffer where the elements will be stored.
 * @param cmp_ Function to compare the heap elements.
 */
#define BP_MAX_HEAP_INIT(array_, cmp_)                                     \
    {                                                                      \
        ._coll = BP_ARRAY_INIT(array_), ._kind = BP_MAX_HEAP, ._cmp = cmp_ \
    }

/*!
 * Get the root element of the Heap tree.
 * @param heap Reference to bp_heap.
 * @return A reference to the root element, or NULL if the heap is empty or the heap
 * argument is NULL.
 */
void *bp_heap_top(bp_heap_t *heap);

/*!
 * Drop all elements in the heap. After this function the heap size is zero, but the
 * elements stay in the buffer.
 * @param heap Reference to bp_heap.
 * @return 0 on success, errno otherwise.
 */
int bp_heap_clear(bp_heap_t *heap);

/*!
 * Remove the root element of the Heap tree and put it in el argument variable.
 * @param heap Reference to bp_heap.
 * @param el [out] Reference to a variable, where the removed element will be put.
 * @return 0 on success, errno, otherwise.
 */
int bp_heap_pop(bp_heap_t *heap, void *el);

/*!
 * Push an element on the Heap tree.
 * @param heap Reference to bp_heap.
 * @param el Reference to the element to be pushed.
 * @return 0 on success, errno otherwise.
 */
int bp_heap_push(bp_heap_t *heap, void *el);

/*!
 * Delete an array element, based at some parameter related to the element. This parameter
 * could be the element itself, or some field of its type. The match will be done based on
 * cmp function pointer. If the cmp function point argument is null, then the elements
 * will be compared with the parameter byte by byte.
 * @param heap Reference to bp_heap.
 * @param param Reference to the parameter used to compare elements.
 * @param cmp Function to compare an element with the parameter passed at argument param.
 * @return 0 on success, errno otherwise.
 */
int bp_heap_del(bp_heap_t *heap, void *param, bool (*cmp)(void *el, void *param));

/*!
 * Find the element in the heap, based at some parameter related to the element. This
 * parameter could be the element itself, or some field of its type. The match will be
 * done based on cmp function pointer. If the cmp function point argument is null, then
 * the elements will be compared with the parameter byte by byte.
 * @param heap Reference to bp_heap.
 * @param param Reference to the parameter used to compare elements.
 * @param cmp Function to compare an element with the parameter passed at argument param.
 * @return A reference to the found element, or NULL if the element wasn't found or some
 * mandatory argument is null.
 */
void *bp_heap_find(bp_heap_t *heap, void *param, bool (*cmp)(void *el, void *param));

/*!
 * Get a iterator to walk through the bp_heap, in Breadth-First-Search (BFS) sequence.
 *
 * @warning This function doesn't check if the heap argument is null. So if this argument
 * is null, a crash will occur. That check must be done outside the function.
 *
 * @param heap Reference to bp_heap.
 * @return A new iterator instance for the bp_heap, using BFS sequence.
 */
bp_iter_t bp_heap_bfs_iter(bp_heap_t *heap);

/*!
 * Get a iterator to walk through the bp_heap, in Depth-First-Search (DFS) sequence.
 *
 * @warning This function doesn't check if the heap argument is null. So if this argument
 * is null, a crash will occur. That check must be done outside the function.
 *
 * @param heap Reference to bp_heap.
 * @return A new iterator instance for the bp_heap, using DFS sequence.
 */
bp_iter_t bp_heap_dfs_iter(bp_heap_t *heap);

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_HEAP_H
