#include "queue.h"
#include <stddef.h>
#include <string.h>


#ifdef NDEBUG
#define ensure(expr) ((void)0)
#else
#include <assert.h>
#define ensure(expr) assert(expr)
#endif


int queue_init(queue_t* queue, size_t item_size, uint8_t* buffer, size_t buffer_size)
{
    ensure(queue != NULL);
    ensure(item_size > 0);
    ensure(buffer != NULL);
    ensure(buffer_size >= item_size);
    ensure(buffer_size % item_size == 0);

    queue->item_size = item_size;
    queue->buffer = buffer;
    queue->buffer_size = buffer_size;
    queue->count = 0;
    queue->read_index = 0;
    queue->write_index = 0;

    return 0;
}


int queue_peek(queue_t* queue, void* value)
{
    ensure(queue != NULL);
    ensure(value != NULL);

    if (queue->count == 0) {
        return -1;
    }

    memcpy(value, &queue->buffer[queue->read_index], queue->item_size);

    return 0;
}


int queue_read(queue_t* queue, void* value)
{
    if (queue_peek(queue, value) != 0) {
        return -1;
    }

    queue->read_index = (queue->read_index + queue->item_size) % queue->buffer_size;

    queue->count -= 1;

    return 0;
}


int queue_write(queue_t* queue, void* value, bool overwrite)
{
    ensure(queue != NULL);
    ensure(value != NULL);

    if (queue->count * queue->item_size >= queue->buffer_size) {
        if (overwrite) {
            queue->read_index = (queue->read_index + queue->item_size) % queue->buffer_size;
        }
        else {
            return -1;
        }
    }
    else {
        queue->count += 1;
    }

    memcpy(&queue->buffer[queue->write_index], value, queue->item_size);
    queue->write_index = (queue->write_index + queue->item_size) % queue->buffer_size;

    return 0;
}


uint32_t queue_get_count(queue_t* queue)
{
    ensure(queue != NULL);

    return queue->count;
}
