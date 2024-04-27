#include "fletcher.h"
#include <assert.h>
#include <stdio.h>


static void test_fletcher16_checksum_block(void)
{
    uint8_t test_vector[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint32_t length = sizeof(test_vector) / sizeof(uint8_t);

    uint8_t c0;
    uint8_t c1;

    fletcher16(0, 0, test_vector, length, &c0, &c1);

    assert(0x27 == c0);
    assert(0x06 == c1);
}


static void test_fletcher16_checksum_stream(void)
{
    uint8_t test_vector[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint32_t length = sizeof(test_vector) / sizeof(uint8_t);

    uint8_t c0 = 0;
    uint8_t c1 = 0;

    for (uint32_t i = 0; i < length; ++i) {
        fletcher16(c0, c1, &test_vector[i], 1, &c0, &c1);
    }

    assert(0x27 == c0);
    assert(0x06 == c1);
}


static void test_fletcher32_checksum_block(void)
{
    uint16_t test_vector[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint32_t length = sizeof(test_vector) / sizeof(uint16_t);

    uint16_t c0;
    uint16_t c1;

    fletcher32(0, 0, test_vector, length, &c0, &c1);

    assert(0x0324 == c0);
    assert(0x0DF8 == c1);
}


static void test_fletcher32_checksum_stream(void)
{
    uint16_t test_vector[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint32_t length = sizeof(test_vector) / sizeof(uint16_t);

    uint16_t c0 = 0;
    uint16_t c1 = 0;

    for (uint32_t i = 0; i < length; ++i) {
        fletcher32(c0, c1, &test_vector[i], 1, &c0, &c1);
    }

    assert(0x0324 == c0);
    assert(0x0DF8 == c1);
}


// test
int main(void)
{
    test_fletcher16_checksum_block();
    test_fletcher16_checksum_stream();

    test_fletcher32_checksum_block();
    test_fletcher32_checksum_stream();

    printf("test success\n");

    return 0;
}
