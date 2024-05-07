#include "stack.h"
#include <stddef.h>
#include <string.h>


static uint8_t* get_item_top(uint8_t* item_top, uint32_t index);
static size_t get_item_size(const uint8_t* const item_top);
static size_t get_item_size_from(uint8_t* item_top, uint32_t index);
static uint8_t* get_item_data_ptr(uint8_t* const item_top);
static uint8_t* get_item_data_ptr_from(uint8_t* item_top, uint32_t index);


int stack_init(stack_t* self, uint8_t* buffer, size_t buffer_size)
{
    if (self == NULL || buffer == NULL) {
        return -1;
    }

    self->buffer = self->stack_top = buffer;
    self->buffer_end = buffer + buffer_size;
    self->count = 0;

    return 0;
}


int stack_push(stack_t* self, uint8_t* data, size_t data_size)
{
    if (self == NULL || data == NULL) {
        return -1;
    }

    uint8_t* new_stack_top = self->stack_top + data_size + sizeof(size_t);

    if (new_stack_top > self->buffer_end) {
        return -1;
    }

    memcpy(self->stack_top, data, data_size);
    memcpy(self->stack_top + data_size, &data_size, sizeof(data_size));

    self->stack_top = new_stack_top;
    self->count += 1;

    return 0;
}


int stack_pop(stack_t* self)
{
    if (self == NULL || self->count == 0) {
        return -1;
    }

    self->stack_top -= get_item_size(self->stack_top);
    self->count -= 1;

    return 0;
}


int stack_pop_all(stack_t* self)
{
    return stack_init(self, self->buffer, self->buffer_end - self->buffer);
}


int stack_copy_from(stack_t* self, uint32_t index)
{
    if (self == NULL) {
        return -1;
    }

    return stack_push(self, get_item_data_ptr_from(self->stack_top, index), get_item_size_from(self->stack_top, index));
}


int stack_dup(stack_t* self)
{
    return stack_copy_from(self, 0);
}


int stack_swap(stack_t* self)
{
    if (self == NULL) {
        return 0;
    }

    uint8_t* first_item_data_ptr = get_item_data_ptr_from(self->stack_top, 1);
    size_t second_item_data_size = get_item_size_from(self->stack_top, 0);

    stack_copy_from(self, 1); // make temp copy of first
    stack_copy_from(self, 1); // make temp copy of second

    memcpy(first_item_data_ptr, get_item_data_ptr(self->stack_top), get_item_size(self->stack_top) + sizeof(size_t)); // move temp copy of second to former place of first

    stack_pop(self); // remove temp copy of second

    memcpy(first_item_data_ptr + second_item_data_size + sizeof(size_t), get_item_data_ptr(self->stack_top), get_item_size(self->stack_top) + sizeof(size_t)); // move temp copy of first to end of new second

    stack_pop(self); // remove temp copy of first

    return 0;
}


size_t stack_get_count(stack_t* self)
{
    if (self == NULL) {
        return 0;
    }

    return self->count;
}


static size_t get_item_size(const uint8_t* const item_top)
{
    size_t item_size;

    memcpy(&item_size, item_top - sizeof(size_t), sizeof(size_t));

    return item_size;
}


static size_t get_item_size_from(uint8_t* item_top, uint32_t index)
{
    for (uint32_t i = 0; i < index; i += 1) {
        item_top -= get_item_size(item_top) + sizeof(size_t);
    }

    return get_item_size(item_top);
}


static uint8_t* get_item_data_ptr(uint8_t* const item_top)
{
    return item_top - sizeof(size_t) - get_item_size(item_top);
}


static uint8_t* get_item_data_ptr_from(uint8_t* item_top, uint32_t index)
{
    for (uint32_t i = 0; i < index; i += 1) {
        item_top -= get_item_size(item_top) + sizeof(size_t);
    }

    return get_item_data_ptr(item_top);
}

