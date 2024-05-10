#include "stack.h"
#include <stddef.h>
#include <string.h>


static uint8_t* get_data_ptr(uint8_t* const item_top);
static size_t get_data_length(const uint8_t* const item_top);


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


int stack_push(stack_t* self, uint8_t* data, size_t data_length)
{
    if (self == NULL || data == NULL) {
        return -1;
    }

    uint8_t* new_stack_top = self->stack_top + data_length + sizeof(size_t);

    if (new_stack_top > self->buffer_end) {
        return -1;
    }

    memcpy(self->stack_top, data, data_length);
    memcpy(self->stack_top + data_length, &data_length, sizeof(data_length));

    self->stack_top = new_stack_top;
    self->count += 1;

    return 0;
}


int stack_pop(stack_t* self, uint8_t* data, size_t max_data_size, size_t* data_length)
{
    if (self == NULL || data == NULL || data_length == 0 || self->count == 0) {
        return -1;
    }

    *data_length = get_data_length(self->stack_top);

    if (max_data_size < *data_length) {
        return -1;
    }

    memcpy(data, get_data_ptr(self->stack_top), *data_length);

    self->stack_top -= *data_length + sizeof(size_t);
    self->count -= 1;

    return 0;
}


int stack_remove_top(stack_t* self)
{
    if (self == NULL || self->count == 0) {
        return -1;
    }

    self->stack_top -= get_data_length(self->stack_top) + sizeof(size_t);
    self->count -= 1;

    return 0;
}


int stack_remove_all(stack_t* self)
{
    return stack_init(self, self->buffer, self->buffer_end - self->buffer);
}


int stack_copy_from(stack_t* self, uint32_t index)
{
    if (index >= self->count)
    {
        return -1;
    }

    return stack_push(self, stack_get_data_ptr_at(self, index), stack_get_data_length_at(self, index));
}


int stack_dup(stack_t* self)
{
    return stack_copy_from(self, 0);
}


int stack_swap(stack_t* self)
{
    if (self == NULL || self->count < 2) {
        return -1;
    }

    size_t a_length = get_data_length(self->stack_top) + sizeof(size_t);
    size_t b_length = stack_get_data_length_at(self, 1) + sizeof(size_t);
    size_t stack_free = self->stack_top > self->buffer_end ? 0 : self->buffer_end - self->stack_top;

    if (stack_free < a_length + b_length) {
        return -1;
    }

    uint8_t* mem_start_ptr = stack_get_data_ptr_at(self, 1);

    stack_copy_from(self, 1); // make temp copy of B
    stack_copy_from(self, 1); // make temp copy of A, is now at top of stack

    memcpy(mem_start_ptr, get_data_ptr(self->stack_top), a_length); // move temp copy of A to old place of B
    stack_remove_top(self); // remove temp copy of A, temp copy of B is now at top of stack

    uint8_t* temp_b_data_ptr = get_data_ptr(self->stack_top);
    memcpy(mem_start_ptr + a_length, temp_b_data_ptr, b_length); // move temp copy B to end of new A position

    stack_remove_top(self); // remove temp copy of B

    return 0;
}


size_t stack_get_count(stack_t* self)
{
    if (self == NULL) {
        return 0;
    }

    return self->count;
}


uint8_t* stack_get_data_ptr_at(stack_t* self, uint32_t index)
{
    uint8_t* item_top = self->stack_top;

    for (uint32_t i = 0; i < index; i += 1) {
        item_top -= get_data_length(item_top) + sizeof(size_t);
    }

    return get_data_ptr(item_top);
}


size_t stack_get_data_length_at(stack_t* self, uint32_t index)
{
    uint8_t* item_top = self->stack_top;

    for (uint32_t i = 0; i < index; i += 1) {
        item_top -= get_data_length(item_top) + sizeof(size_t);
    }

    return get_data_length(item_top);
}


static uint8_t* get_data_ptr(uint8_t* const item_top)
{
    return item_top - sizeof(size_t) - get_data_length(item_top);
}


static size_t get_data_length(const uint8_t* const item_top)
{
    size_t item_size;

    memcpy(&item_size, item_top - sizeof(size_t), sizeof(size_t));

    return item_size;
}
