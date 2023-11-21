#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Places a global variable in the .text.global section.
 *
 * @note Trailing `#` prevents assembler messages with mutable variables.
 *
 */
#define __global __attribute__((section(".text.global # ")))

/**
 * @brief Marks a function to be always inline.
 *
 */
#define __always_inline __attribute__((always_inline))

/**
 * @brief Defines a weak symbol.
 *
 */
#define __weak __attribute__((weak))

#define __static_inline static inline __always_inline

#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)

#endif /* DEFS_H_INCLUDED */
