/** \file
 * HDLC like byte stuffing (encode).
 */


#ifndef BYTE_STUFFING_ENCODE
#define BYTE_STUFFING_ENCODE


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


#ifdef NDEBUG
    #define BYTE_STUFFING_ENCODE_ENSURE(expr) ((void)0)
#else
    #include <assert.h>
    #define BYTE_STUFFING_ENCODE_ENSURE(expr) assert(expr)
#endif


#define DECODE_DELIMITER 0x7e
#define DECODE_ESCAPE 0x7d


/**
 * encode byte stuffing.
 * \param[in] byte_to_encode
 * \param[out] encoded_bytes
 * \return number of encoded bytes (1 or 2)
 */
static inline int byte_stuffing_encode(uint_least8_t byte_to_encode, uint8_t encoded_bytes[2])
{
    BYTE_STUFFING_ENCODE_ENSURE(encoded_bytes);

    if (byte_to_encode == DECODE_DELIMITER || byte_to_encode == DECODE_ESCAPE) {
        encoded_bytes[0] = DECODE_ESCAPE;
        encoded_bytes[1] = byte_to_encode ^ 0x20;
        return 2;
    }
    else {
        encoded_bytes[0] = byte_to_encode;
        return 1;
    }
}


#ifdef __cplusplus
}
#endif


#endif
