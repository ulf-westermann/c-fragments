/** \file
 * HDLC like byte stuffing (decode).
 */


#ifndef BYTE_STUFFING_DECODE
#define BYTE_STUFFING_DECODE


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


#define DECODE_DELIMITER 0x7e
#define DECODE_ESCAPE 0x7d


/**
 * decode byte stuffing.
 * \param[in] current_byte
 * \param[in] next_byte
 * \param[out] decoded_byte
 * \return error (-1) or number of consumed bytes (1 or 2)
 */
static inline int byte_stuffing_decode(uint_least8_t current_byte, uint_least8_t next_byte, uint_least8_t* decoded_byte)
{
    if (!decoded_byte) {
        return -1;
    }

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
