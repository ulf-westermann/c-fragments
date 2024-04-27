#ifndef UTILS_H
#define UTILS_H


// macros to handle indiviual bits in a variable. BITNUM starts at 0. examples: x = GETBIT(y, 1); SETBIT(x, 7);
#ifdef USE_BITS
    #define GETBIT(VALUE, BITNUM) ((VALUE & (1 << BITNUM)) >> BITNUM)

    #define SETBIT(VALUE, BITNUM)                                                                                                \
        do {                                                                                                                     \
            VALUE |= (1 << BITNUM)                                                                                               \
        } while (0)

    #define CLRBIT(VALUE, BITNUM)                                                                                                \
        do {                                                                                                                     \
            VALUE &= ~(1 << BITNUM)                                                                                              \
        } while (0)

    #define TGLBIT(VALUE, BITNUM)                                                                                                \
        do {                                                                                                                     \
            VALUE ^= (1 << BITNUM)                                                                                               \
        } while (0)
#endif


// various helper macros
#ifdef USE_HELPERS
    #define IS_POWER_OF_TWO(UNSIGNED_VALUE) ((UNSIGNED_VALUE) && (((UNSIGNED_VALUE) & ((UNSIGNED_VALUE)-1)) == 0))
    #define ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof((ARRAY)[0]))
    #define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
    #define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif


// macros to check results of operations
#ifdef USE_CHECKS
    #include <stdint.h>

    // check if addition results in unsigned integer wrap
    #define CHECK_OVERFLOW_ADD_UINT64(X, Y) (UINT64_MAX - X < Y)
    #define CHECK_OVERFLOW_ADD_UINT32(X, Y) (UINT32_MAX - X < Y)
    #define CHECK_OVERFLOW_ADD_UINT16(X, Y) (UINT16_MAX - X < Y)
    #define CHECK_OVERFLOW_ADD_UINT8(X, Y) (UINT8_MAX - X < Y)

    // check if subtraction results in unsigned integer overflow
    #define CHECK_OVERFLOW_SUB_UINT(X, Y) (X < Y)

    // check if cast to next smaller type would lose data
    #define CHECK_LOSS_UINT64_TO_UINT32(X) (X > UINT32_MAX)
    #define CHECK_LOSS_UINT32_TO_UINT16(X) (X > UINT16_MAX)
    #define CHECK_LOSS_UINT16_TO_UINT8(X) (X > UINT8_MAX)

    // check if cast from unsigned to signed would would lose data
    #define CHECK_LOSS_UINT64_TO_INT64(X) (X > INT64_MAX)
    #define CHECK_LOSS_UINT32_TO_INT32(X) (X > INT32_MAX)
    #define CHECK_LOSS_UINT16_TO_INT16(X) (X > INT16_MAX)
    #define CHECK_LOSS_UINT8_TO_INT8(X) (X > INT8_MAX)
#endif


// customizable assert like mechanism
#ifdef USE_ENSURE
    #ifdef DEBUG
        #include <stdbool.h>
        #include <stdio.h>

        #define ENSURE(EXPRESSION)                                                                                               \
            do {                                                                                                                 \
                if (!(EXPRESSION)) {                                                                                             \
                    fprintf(stderr, "%s:%d: ensure failed in %s (\"" #EXPRESSION "\")\n", __FILE__, __LINE__, __func__);                               \
                    while (1)                                                                                                    \
                        ;                                                                                                        \
                }                                                                                                                \
            } while (0)
    #else
        #define ENSURE ((void)0)
    #endif
#endif


// static assert for C standards before C11
#ifdef USE_STATIC_ASSERT
    #if __STDC_VERSION__ < 201112L
        #define static_assert(expression, message)                                                                               \
            do {                                                                                                                 \
                enum { __ASSERT_STATIC__ = 1 / (expression) }                                                                    \
            } while (0)
    #endif
#endif


// template for X macros
#if 0
    #define LIST_OF_SOMETHING                                                                                                    \
        X(foo, 1)                                                                                                                \
        X(bar, 2)                                                                                                                \
        X(baz, 42) \

    // first use of list
    #define X(NAME, NUMBER) int autogenerated_variable_##NAME = NUMBER;
    LIST_OF_SOMETHING
    #undef X

    // list can be used several times with different X macro definition
    #define X(NAME, NUMBER) printf("name: %s, number: %d\n", #NAME, NUMBER);
    LIST_OF_SOMETHING
    #undef X
#endif


#endif
