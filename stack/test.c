#include "stack.h"
#include <assert.h>
#include <stdio.h>


// test
int main(void)
{
    stack_t q;
    uint32_t buffer[3];
    uint32_t read = 0;

    // init
    assert(stack_init(&q, sizeof(uint32_t), (uint8_t*)buffer, sizeof(buffer)) == 0);

    /*
    assert((void*)q.buffer == (void*)buffer);
    assert(q.buffer_size == 3 * sizeof(uint32_t));
    assert(q.item_size == 4);

    // empty read fails
    assert(queue_read(&q, &read) < 0);

    // fill
    assert(queue_write(&q, &(uint32_t){41}, false) == 0);
    assert(queue_write(&q, &(uint32_t){42}, false) == 0);
    assert(queue_write(&q, &(uint32_t){43}, false) == 0);

    // queue contains 41, 42, 43. full, put one more should fail
    assert(queue_write(&q, &(uint32_t){1}, false) < 0);

    // read 41
    assert(queue_read(&q, &read) == 0);
    assert(read == 41);

    // queue contains 42, 43. fill up again
    assert(queue_write(&q, &(uint32_t){44}, false) == 0);

    // queue contains 42, 43, 44, oldest gets overwritten
    assert(queue_write(&q, &(uint32_t){45}, true) == 0);

    // read 43, 44, 45
    assert(queue_read(&q, &read) == 0);
    assert(read == 43);

    assert(queue_read(&q, &read) == 0);
    assert(read == 44);

    assert(queue_read(&q, &read) == 0);
    assert(read == 45);

    // empty read fails
    assert(queue_read(&q, &read) < 0);

    // fill
    assert(queue_write(&q, &(uint32_t){100}, true) == 0);
    assert(queue_write(&q, &(uint32_t){101}, true) == 0);
    assert(queue_write(&q, &(uint32_t){102}, true) == 0);
    assert(queue_write(&q, &(uint32_t){103}, true) == 0);

    // read 101, 102, 103
    assert(queue_read(&q, &read) == 0);
    assert(read == 101);

    assert(queue_read(&q, &read) == 0);
    assert(read == 102);

    assert(queue_read(&q, &read) == 0);
    assert(read == 103);

    // empty read fails
    assert(queue_read(&q, &read) < 0);

    printf("test success\n");
*/
    return 0;
}
