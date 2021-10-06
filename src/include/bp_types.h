/*!
 * @file bp_types.h
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief Specifies the basic types used in this library.
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */
#ifndef BACKPACK_TYPES_H
#define BACKPACK_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stdbool.h>

typedef char s8_t;                /*!< Signed 8-bits integer. */
typedef unsigned char u8_t;       /*!< Unsigned 8-bits integer. */
typedef short s16_t;              /*!< Signed 16-bits integer. */
typedef unsigned short u16_t;     /*!< Unsigned 16-bits integer. */
typedef long s32_t;               /*!< Signed 32-bits integer. */
typedef unsigned long u32_t;      /*!< Unsigned 32-bits integer. */
typedef long long s64_t;          /*!< Signed 64-bits integer. */
typedef unsigned long long u64_t; /*!< Unsigned 64-bits integer. */

/*!
 * Type for size in general.
 */
typedef u32_t usize;

/*!
 * Define NULL value if isn't defined.
 */
#ifndef NULL
#define NULL ((void*) 0)
#endif

#ifdef __cplusplus
}
#endif

#endif  // BACKPACK_TYPES_H
