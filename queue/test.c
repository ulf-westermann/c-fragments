#include "queue.h"
#include <assert.h>
#include <stdio.h>


int main(void)
{
    queue_t q;
    uint32_t buffer[3];
    uint32_t read = 0;

    // init
    queue_init(&q, buffer, sizeof(buffer));

    // emtpy read should fail
    assert(queue_read(&q, &read) < 0);

    // fill
    assert(queue_write(&q, &(uint32_t){41}, false) == 0);
    assert(queue_write(&q, &(uint32_t){42}, false) == 0);
    assert(queue_write(&q, &(uint32_t){43}, false) == 0);

    // queue contains 41, 42, 43. full, put one more should fail
    assert(queue_write(&q, &(uint32_t){1}, false) <= 0);

    // read first
    assert(queue_read(&q, &read) == 0);
    assert(read == 41);

    // queue contains 42, 43. fill up again
    assert(queue_write(&q, &(uint32_t){44}, false) == 0);

    // queue contains 42, 43, 44. overwrite oldest
    assert(queue_write(&q, &(uint32_t){2}, true) == 0);

    // queue contains 2, 43, 44. read oldest, which was overwritten
    assert(queue_read(&q, &read) == 0);
    assert(read == 2);

    // read next
    assert(queue_read(&q, &read) == 0);
    assert(read == 43);

    // read next
    assert(queue_read(&q, &read) == 0);
    assert(read == 44);

    // empty read should fail again
    assert(queue_read(&q, &read) < 0);

    printf("test success\n");

    return 0;
}
