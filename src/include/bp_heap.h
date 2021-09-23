/**
 * @file bp_heap.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#ifndef BACKPACK_HEAP_H
#define BACKPACK_HEAP_H

#include "bp_array.h"

typedef int (*bp_heap_cmp_t)(void *left, void *right);

typedef enum {
    BP_MIN_HEAP,
    BP_MAX_HEAP,
} bp_heap_kind_t;

typedef struct {
    bp_array_t _coll;
    bp_heap_kind_t _kind;
    bp_heap_cmp_t _cmp;
} bp_heap_t;

#define BP_MIN_HEAP_INIT(array_, cmp_)                                    \
    {                                                                     \
        ._coll = BP_ARRAY_INIT(array_), .kind = BP_MIN_HEAP, ._cmp = cmp_ \
    }

#define BP_MAX_HEAP_INIT(array_, cmp_)                                    \
    {                                                                     \
        ._coll = BP_ARRAY_INIT(array_), .kind = BP_MAX_HEAP, ._cmp = cmp_ \
    }

void *bp_heap_top(bp_heap_t *heap);

int bp_heap_clear(bp_heap_t *heap);

int bp_heap_pop(bp_heap_t *heap, void *el);

int bp_heap_push(bp_heap_t *heap, void *el);

int bp_heap_del(bp_heap_t *heap, void *param, bool (*cmp)(void *el, void *param));

usize bp_heap_find_idx(bp_heap_t *heap, void *param, bool (*cmp)(void *el, void *param));

void *bp_heap_find(bp_heap_t *heap, void *param, bool (*cmp)(void *el, void *param));

bp_iter_t bp_heap_bfs_iter(bp_heap_t *heap);

bp_iter_t bp_heap_dfs_iter(bp_heap_t *heap);

#endif  // BACKPACK_HEAP_H
