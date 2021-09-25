/**
 * @file bp_types.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#ifndef BACKPACK_TYPES_H
#define BACKPACK_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stdbool.h>

typedef char s8_t;
typedef unsigned char u8_t;
typedef short s16_t;
typedef unsigned short u16_t;
typedef long s32_t;
typedef unsigned long u32_t;
typedef long long s64_t;
typedef unsigned long long u64_t;

typedef u32_t usize;

#ifndef NULL
#define NULL ((void*) 0)
#endif

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_TYPES_H
