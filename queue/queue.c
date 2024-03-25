#include "queue.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>


void queue_init(queue_t* queue, QUEUE_ENTRY_TYPE* buffer, uint32_t buffer_size) {
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


int queue_read(queue_t* queue, QUEUE_ENTRY_TYPE* value) {
    assert(queue != NULL);
    assert(value != NULL);

    if (queue->count == 0) {
        return -1;
    }

    memcpy(value, &queue->buffer[queue->read_index], QUEUE_ENTRY_SIZE);
    queue->read_index = (queue->read_index + 1) % queue->capacity;
    queue->count--;

    return 0;
}


int queue_write(queue_t* queue, QUEUE_ENTRY_TYPE* value) {
    assert(queue != NULL);
    assert(value != NULL);

    if (queue->count >= queue->capacity) {
        return -1;
    }

    memcpy(&queue->buffer[queue->write_index], value, QUEUE_ENTRY_SIZE);
    queue->write_index = (queue->write_index + 1) % queue->capacity;
    ++queue->count;

    return 0;
}


uint32_t queue_get_count(queue_t* queue) {
    assert(queue != NULL);

    return queue->count;
}
