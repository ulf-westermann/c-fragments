#include "queue.h"
#include <stddef.h>
#include <string.h>


#ifdef NDEBUG
    #define ensure(expr) ((void)0)
#else
    #include <assert.h>
    #define ensure(expr) assert(expr)
#endif


int queue_init(queue_t* self, size_t item_size, uint8_t* buffer, size_t buffer_size)
{
    ensure(self != NULL);
    ensure(item_size > 0);
    ensure(buffer != NULL);
    ensure(buffer_size >= item_size);
    ensure(buffer_size % item_size == 0);

    self->item_size = item_size;
    self->buffer = buffer;
    self->buffer_size = buffer_size;
    self->count = 0;
    self->read_index = 0;
    self->write_index = 0;

    return 0;
}


int queue_peek(queue_t* self, void* value)
{
    ensure(self != NULL);
    ensure(value != NULL);

    if (self->count == 0) {
        return -1;
    }

    memcpy(value, &self->buffer[self->read_index], self->item_size);

    return 0;
}


int queue_read(queue_t* self, void* value)
{
    if (queue_peek(self, value) != 0) {
        return -1;
    }

    self->read_index = (self->read_index + self->item_size) % self->buffer_size;

    self->count -= 1;

    return 0;
}


int queue_write(queue_t* self, void* value, bool overwrite)
{
    ensure(self != NULL);
    ensure(value != NULL);

    if (self->count * self->item_size >= self->buffer_size) {
        if (overwrite) {
            self->read_index = (self->read_index + self->item_size) % self->buffer_size;
        }
        else {
            return -1;
        }
    }
    else {
        self->count += 1;
    }

    memcpy(&self->buffer[self->write_index], value, self->item_size);
    self->write_index = (self->write_index + self->item_size) % self->buffer_size;

    return 0;
}


uint32_t queue_get_count(queue_t* self)
{
    ensure(self != NULL);

    return self->count;
}
