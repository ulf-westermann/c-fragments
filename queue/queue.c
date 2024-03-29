#include "queue.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>


/* enable for custom assert handling:
#ifndef NDEBUG
#include <stdio.h>
#undef assert
#define assert(expr) ((expr) ? (void)0 : (void)printf("%s:%d (%s): assertion failed\n", __FILE__, __LINE__, __func__))
#endif*/


void queue_init(queue_t* queue, QUEUE_ENTRY_TYPE* buffer, uint32_t buffer_size)
{
    assert(queue != NULL);
    assert(buffer != NULL);
    assert(buffer_size >= QUEUE_ENTRY_SIZE);
    assert(buffer_size % QUEUE_ENTRY_SIZE == 0); // could be removed, if desired

    queue->buffer = buffer;
    queue->capacity = buffer_size / QUEUE_ENTRY_SIZE;
    queue->count = 0;
    queue->read_index = 0;
    queue->write_index = 0;
}


int queue_peek(queue_t* queue, QUEUE_ENTRY_TYPE* value)
{
    assert(queue != NULL);
    assert(value != NULL);

    if (queue->count == 0) {
        return -1;
    }

    memcpy(value, &queue->buffer[queue->read_index], QUEUE_ENTRY_SIZE);

    return 0;
}


int queue_read(queue_t* queue, QUEUE_ENTRY_TYPE* value)
{
    if (queue_peek(queue, value) < 0) {
        return -1;
    }

    queue->read_index = (queue->read_index + 1) % queue->capacity;
    queue->count--;

    return 0;
}


int queue_write(queue_t* queue, QUEUE_ENTRY_TYPE* value, bool overwrite)
{
    assert(queue != NULL);
    assert(value != NULL);

    if (queue->count >= queue->capacity) {
        if (!overwrite) {
            return -1;
        }

        queue->read_index = queue->write_index;
    }
    else {
        ++queue->count;
    }

    memcpy(&queue->buffer[queue->write_index], value, QUEUE_ENTRY_SIZE);
    queue->write_index = (queue->write_index + 1) % queue->capacity;

    return 0;
}


uint32_t queue_get_count(queue_t* queue)
{
    assert(queue != NULL);

    return queue->count;
}
