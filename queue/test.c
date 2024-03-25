#include "queue.h"
#include <assert.h>
#include <stdio.h>


int main(void) {

    queue_t q;
    uint32_t buffer[3];
    uint32_t read = 0;

    queue_init(&q, buffer, sizeof(buffer));

    assert(queue_read(&q, &read) < 0);

    assert(queue_write(&q, &(uint32_t){41}) == 0);
    assert(queue_write(&q, &(uint32_t){42}) == 0);
    assert(queue_write(&q, &(uint32_t){43}) == 0);

    assert(queue_write(&q, &(uint32_t){44}) <= 0);

    assert(queue_read(&q, &read) == 0);
    assert(read == 41);

    assert(queue_write(&q, &(uint32_t){45}) == 0);

    assert(queue_read(&q, &read) == 0);
    assert(read == 42);

    assert(queue_read(&q, &read) == 0);
    assert(read == 43);

    assert(queue_read(&q, &read) == 0);
    assert(read == 45);

    assert(queue_read(&q, &read) < 0);

    printf("test success\n");

    return 0;
}
