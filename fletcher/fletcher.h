/** \file
 * calculation of fletcher checksum. fletcher checksums are faster to calculate than CRCs, but are found to detect less errors.
 *
 * https://en.wikipedia.org/wiki/fletcher's_checksum
 */


#ifndef FLETCHER_H
#define FLETCHER_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


#ifdef USE_FLETCHER16
/**
 * calculate fletcher16 checksum. init values are normally set to 0. result arguments contain the result after calculation. the
 * function can be used to calculate the checksum over data of a fixed length. it is also possible to calculate the checksum of a
 * stream of arbitrary length on the fly, using the result from the last calculation as init values for the calculation of the
 * next results.
 * @param[in] c0_init_value: initial c0 value.
 * @param[in] c1_init_value: initial c1 value.
 * @param[in] data: data.
 * @param[in] length: length of data in bytes.
 * @param[out] c0_result: c0 result.
 * @param[out] c1_result: c1 result.
 * @return 0 on success, negative value on error. */
static inline int fletcher16(uint8_t c0_init, uint8_t c1_init, const uint8_t* const data, uint32_t length,
                             uint8_t* const c0_result, uint8_t* const c1_result)
{
    if (!data) {
        return -1;
    }

    uint_fast16_t c0 = c0_init;
    uint_fast16_t c1 = c1_init;

    for (uint_fast32_t i = 0; i < length; ++i) {
        c0 = (c0 + data[i]) % 0xFF;
        c1 = (c1 + c0) % 0xFF;
    }

    *c0_result = c0;
    *c1_result = c1;

    return 0;
}
#endif


#ifdef USE_FLETCHER32
/**
 * calculate fletcher32 checksum. init values are normally set to 0. result arguments contain the result after calculation. the
 * function can be used to calculate the checksum over data of a fixed length. it is also possible to calculate the checksum of a
 * stream of arbitrary length on the fly, using the result from the last calculation as init values for the calculation of the
 * next results.
 * @param[in] c0_init_value: initial c0 value.
 * @param[in] c1_init_value: initial c1 value.
 * @param[in] data: data.
 * @param[in] length: length of data in bytes.
 * @param[out] c0_result: c0 result.
 * @param[out] c1_result: c1 result.
 * @return 0 on success, negative value on error. */
static inline int fletcher32(uint16_t c0_init_value, uint16_t c1_init_value, const uint16_t* const data, uint32_t length,
                             uint16_t* const c0_result, uint16_t* const c1_result)
{
    if (!data) {
        return -1;
    }

    uint_fast32_t c0 = c0_init_value;
    uint_fast32_t c1 = c1_init_value;

    for (uint_fast32_t i = 0; i < length; ++i) {
        c0 = (c0 + data[i]) % 0xFFFF;
        c1 = (c1 + c0) % 0xFFFF;
    }

    *c0_result = c0;
    *c1_result = c1;

    return 0;
}
#endif


#ifdef __cplusplus
}
#endif


#endif
