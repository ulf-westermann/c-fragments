#include "stdio.h"


#define USE_BITS
#define USE_HELPERS
#define USE_CHECKS
#define USE_ENSURE
#define USE_STATIC_ASSERT
#define DEBUG

#include "utils.h"


/** test utils */
int main(void)
{
    unsigned int value = 0x55;

    ENSURE(GETBIT(value, 0) == 1);
    ENSURE(GETBIT(value, 1) == 0);
    ENSURE(GETBIT(value, 2) == 1);

    printf("test success\n");

    return 0;
}
