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

int bp_stack_pop(bp_stack_t *stack, void *el)
{
    if (stack == NULL || el == NULL) {
        return -ENODEV;
    }

    if (stack->_size == 0) {
        return -ENOENT;
    }

    void *last_el = &stack->_buffer[(stack->_size - 1) * stack->_element_size];

    memcpy(el, last_el, stack->_element_size);
    memset(last_el, 0, stack->_element_size);
    stack->_size -= 1;

    return 0;
}

void *bp_stack_peek(bp_stack_t *stack)
{
    if (stack == NULL) {
        return NULL;
    }

    if (stack->_size == 0) {
        return NULL;
    }

    return &stack->_buffer[(stack->_size - 1) * stack->_element_size];
}

int bp_stack_push(bp_stack_t *stack, void *el)
{
    if (stack == NULL || el == NULL) {
        return -ENODEV;
    }

    if (stack->_size >= stack->_max_size) {
        return -ENOMEM;
    }

    void *ptr = &stack->_buffer[stack->_size * stack->_element_size];
    memcpy(ptr, el, stack->_element_size);
    stack->_size += 1;

    return 0;
}

int bp_stack_clear(bp_stack_t *stack)
{
    if (stack == NULL) {
        return -ENODEV;
    }

    stack->_size = 0;

    return 0;
}

usize bp_stack_size(bp_stack_t *stack)
{
    if (stack == NULL) {
        return 0;
    }

    return stack->_size;
}

bp_iter_t bp_stack_iter(bp_stack_t *stack)
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
    bp_stack_t *stack = self->coll;

    if (stack->_size == 0) {
        return NULL;
    }

    self->current.idx = stack->_size - 1;

    return &stack->_buffer[self->current.idx * stack->_element_size];
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
    bp_stack_t *stack = self->coll;

    if (self->current.idx >= stack->_size) {
        return NULL;
    }

    return &stack->_buffer[self->current.idx * stack->_element_size];
}

#ifdef __cplusplus
}
#endif
