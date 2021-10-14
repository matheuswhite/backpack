/*!
 * @file bp_stack.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Specifies the stack structure. This structure is a bp_array complement. To allow
 * the bp_array works as stack. So the following function follow the LIFO
 * (Last-In-First-Out) order.
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */
#ifndef BACKPACK_STACK_H
#define BACKPACK_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bp_array.h"

/*!
 * Remove the top element in the stack and put it in el argument variable.
 * @param stack Reference to the stack.
 * @param el [out] Reference to a variable, where the removed element will be put.
 * @return 0 on success, errno otherwise.
 */
int bp_stack_pop(bp_array_t *stack, void *el);

/*!
 * Get the top element in the stack.
 * @param stack Reference to the stack.
 * @return A reference to the desired element, or NULL if the stack argument is NULL.
 */
void *bp_stack_peek(bp_array_t *stack);

/*!
 * Push an element at the top of the stack.
 * @param stack Reference to the stack.
 * @param el Reference to the element to be pushed.
 * @return 0 on success, errno otherwise.
 */
int bp_stack_push(bp_array_t *stack, void *el);

/*!
 * Get a iterator to walk through the stack. The traversal order is from top to the bottom
 * of the stack.
 *
 * @warning This function doesn't check if the stack argument is null. So if this argument
 * is null, a crash will occur. That check must be done outside the function.
 *
 * @param stack Reference to the stack.
 * @return A new iterator instance for the stack.
 */
bp_iter_t bp_stack_iter(bp_array_t *stack);

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_STACK_H
