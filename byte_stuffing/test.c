#include "byte_stuffing_decode.h"
#include "byte_stuffing_encode.h"
#include <assert.h>
#include <stdio.h>


// test
int main(void)
{
    uint8_t data[] = {0x7e, 0x42, 0x00, 0x7d, 0x7e, 0x7e, 0xff, 0x7f, 0x7f};
    const int data_length = sizeof(data) / sizeof(uint8_t);
    uint8_t encoded[2 * data_length];
    uint8_t decoded[data_length];

    // encode
    int encoded_length = 0;

    for (int i = 0; i < data_length; ++i) {
        int ret = byte_stuffing_encode(data[i], &encoded[encoded_length]);
        encoded_length += ret;
    }

    // decode
    int decoded_length = 0;

    for (int i = 0; i < encoded_length; ++decoded_length) {
        int ret = byte_stuffing_decode(encoded[i], encoded[i + 1], &decoded[decoded_length]);
        assert(ret > 0);
        i += ret;
    }

    // check that original data and decoded data have same length
    assert(data_length == decoded_length);

    // check that original data is equal to decoded data
    for (int i = 0; i < data_length; ++i) {
        assert(data[i] == decoded[i]);
    }

    // check that encoded data does not contain DELIMITER
    for (int i = 0; i < encoded_length; ++i) {
        assert(encoded[i] != DECODE_DELIMITER);
    }

    printf("test success\n");

    return 0;
}
