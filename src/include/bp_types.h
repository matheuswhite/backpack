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

#include <errno.h>

typedef char s8_t;
typedef unsigned char u8_t;
typedef short s16_t;
typedef unsigned short u16_t;
typedef long s32_t;
typedef unsigned long u32_t;
typedef long long s64_t;
typedef unsigned long long u64_t;

typedef u32_t usize;

typedef char bool;

#define true 1
#define false 0

#ifndef NULL
#define NULL 0
#endif

#endif  // BACKPACK_TYPES_H
