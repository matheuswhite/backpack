/*!
 * @file bp_stack.c
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Implement the stack structure.
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */
#include "bp_stack.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Initialize iterator for stack.
 * @param self Reference to the iterator itself.
 * @return Reference to the top element in the stack.
 */
static void *bp_stack_iter_init(struct bp_iter *self);

/*!
 * Move the iterator to the next position.
 * @param self Reference to the iterator itself.
 * @return false if the current element is the bottom element in the stack.
 * @return true  if the current element isn't the bottom element in the stack.
 */
static bool bp_stack_iter_next(struct bp_iter *self);

/*!
 * Get the current iterator element.
 * @param self Reference to the iterator itself.
 * @return Reference to the current iterator element.
 */
static void *bp_stack_iter_get(struct bp_iter *self);

int bp_stack_pop(bp_array_t *stack, void *el)
{
    if (stack == NULL || el == NULL) {
        return -ENODEV;
    }

    if (stack->_size == 0) {
        return -ENOENT;
    }

    usize last_el;

    last_el = bp_array_size(stack) - 1;
    memcpy(el, bp_array_get(stack, last_el), stack->_element_size);

    return bp_array_del(stack, last_el);
}

void *bp_stack_peek(bp_array_t *stack)
{
    if (stack == NULL) {
        return NULL;
    }

    if (stack->_size == 0) {
        return NULL;
    }

    return bp_array_get(stack, bp_array_size(stack) - 1);
}

int bp_stack_push(bp_array_t *stack, void *el)
{
    return bp_array_push(stack, el);
}

bp_iter_t bp_stack_iter(bp_array_t *stack)
{
    bp_iter_t iter = {
        .init        = bp_stack_iter_init,
        .next        = bp_stack_iter_next,
        .get         = bp_stack_iter_get,
        .current.idx = 0,
        .coll        = stack,
    };

    return iter;
}

static void *bp_stack_iter_init(struct bp_iter *self)
{
    bp_array_t *stack = self->coll;

    if (stack->_size == 0) {
        self->current.idx = 0;
    } else {
        self->current.idx = bp_array_size(stack) - 1;
    }

    return bp_array_get(stack, self->current.idx);
}

static bool bp_stack_iter_next(struct bp_iter *self)
{
    if (self->current.idx == 0) {
        return false;
    }

    self->current.idx -= 1;
    return true;
}

static void *bp_stack_iter_get(struct bp_iter *self)
{
    return bp_array_get(self->coll, self->current.idx);
}

#ifdef __cplusplus
}
#endif
