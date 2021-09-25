/**
 * @file bp_stack.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#ifndef BACKPACK_STACK_H
#define BACKPACK_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bp_array.h"

int bp_stack_pop(bp_array_t *stack, void *el);

void *bp_stack_peek(bp_array_t *stack);

int bp_stack_push(bp_array_t *stack, void *el);

bp_iter_t bp_stack_iter(bp_array_t *stack);

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_STACK_H
