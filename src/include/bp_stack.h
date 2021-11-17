/*!
 * @file bp_stack.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Specifies the stack structure. The following module follow the LIFO
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

#include <string.h>
#include "bp_iter.h"
#include "bp_types.h"

/*!
 * Macro to initialize a bp_stack.
 * @param buffer Buffer where the elements will be stored.
 */
#define BP_STACK_INIT(buffer)                                          \
    {                                                                  \
        ._element_size = sizeof((buffer)[0]),                          \
        ._capacity = sizeof(buffer) / sizeof((buffer)[0]), ._size = 0, \
        ._buffer = (u8_t *) (buffer),                                  \
    }

/*!
 * Macro to initialize a bp_stack, which have initials elements.
 * @param buffer Buffer where the elements will be stored.
 * @param size_ Number of elements already presentes in the buffer.
 */
#define BP_STACK_START(buffer, size_)                                        \
    {                                                                        \
        ._element_size = sizeof((buffer)[0]),                                \
        ._capacity = sizeof(buffer) / sizeof((buffer)[0]), ._size = (size_), \
        ._buffer = (u8_t *) (buffer),                                        \
    }

/*!
 * Struct with metadata about an external buffer.
 *
 * @note This struct need an external buffer to work properly.
 */
typedef struct {
    usize _element_size; /*!< Size (in bytes) of a single element in the stack. */
    usize _capacity;     /*!< Maximum number of elements in the stack */
    usize _size;         /*!< Current number of elements in the array. */
    u8_t *_buffer; /*!< Reference to the buffer, where the elements will be stored. */
} bp_stack_t;

/*!
 * Remove the top element in the stack and put it in el argument variable.
 * @param stack Reference to the stack.
 * @param el [out] Reference to a variable, where the removed element will be put.
 * @return 0 on success.
 * @return -ENODEV if the 'stack' argument is NULL.
 * @return -ENOENT if the stack is empty.
 */
int bp_stack_pop(bp_stack_t *stack, void *el);

/*!
 * Get the top element in the stack.
 * @param stack Reference to the stack.
 * @return A reference to the desired element.
 * @return NULL if the 'stack' argument is NULL or the stack is empty.
 */
void *bp_stack_peek(bp_stack_t *stack);

/*!
 * Push an element at the top of the stack.
 * @param stack Reference to the stack.
 * @param el Reference to the element to be pushed.
 * @return 0 on success, errno otherwise.
 * @return -ENODEV if the 'stack' or the 'el' argument is NULL.
 * @return -ENOMEM if the stack is full.
 */
int bp_stack_push(bp_stack_t *stack, void *el);

/*!
 * Drop all elements in the stack.
 *
 * @warning After this function the stack size is zero, but the elements stay in the
 * buffer.
 *
 * @param stack Reference to the stack.
 * @return 0 on success.
 * @return -ENODEV if the 'stack' argument is NULL.
 */
int bp_stack_clear(bp_stack_t *stack);

/*!
 * Get a iterator to walk through the stack.
 * @param stack Reference to the stack.
 * @return The size of the stack.
 * @return 0 if the 'stack' argument is NULL.
 */
usize bp_stack_size(bp_stack_t *stack);

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
bp_iter_t bp_stack_iter(bp_stack_t *stack);

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_STACK_H
