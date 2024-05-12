/** \file
 * HDLC like byte stuffing (decode).
 */


#ifndef BYTE_STUFFING_DECODE
#define BYTE_STUFFING_DECODE


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


#ifndef ENSURE
    #ifdef NDEBUG
        #undef ENSURE
        #define ENSURE(expr) ((void)0)
    #else
        #include <assert.h>
        #undef ENSURE
        #define ENSURE(expr) assert(expr)
    #endif
#endif


#define DECODE_DELIMITER 0x7e
#define DECODE_ESCAPE 0x7d


/**
 * decode byte stuffing.
 * \param[in] current_byte
 * \param[in] next_byte
 * \param[out] decoded_byte
 * \return number of consumed bytes (1 or 2) or 0 in case of delimiter byte
 */
static inline int byte_stuffing_decode(uint_least8_t current_byte, uint_least8_t next_byte, uint_least8_t* decoded_byte)
{
    ENSURE(decoded_byte);

    if (current_byte == DECODE_DELIMITER) {
        return 0;
    }
    else if (current_byte == DECODE_ESCAPE) {
        *decoded_byte = next_byte ^ 0x20;

        return 2;
    }

    *decoded_byte = current_byte;

    return 1;
}


#ifdef __cplusplus
}
#endif


#endif
