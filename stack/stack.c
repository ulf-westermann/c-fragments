#include "stack.h"
#include <stddef.h>
#include <string.h>


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


#include <stdio.h>
int stack_push(stack_t* self, uint8_t* data, size_t data_length)
{
    if (self == NULL || data == NULL) {
        printf("1\n");
        return -1;
    }

    uint8_t* new_stack_top = self->stack_top + data_length + sizeof(size_t);
    printf("buffer_end: %lu, new_stack_top: %lu\n", (uintptr_t)self->buffer_end, (uintptr_t)new_stack_top);

    if (new_stack_top > self->buffer_end) {
        printf("new_stack_top > self->buffer_end\n");
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

    *data_length = get_item_size(self->stack_top);

    if (max_data_size < *data_length) {
        return -1;
    }

    memcpy(data, get_item_data_ptr(self->stack_top), *data_length);

    self->stack_top -= *data_length + sizeof(size_t);
    self->count -= 1;

    return 0;
}


int stack_remove_top(stack_t* self)
{
    if (self == NULL || self->count == 0) {
        return -1;
    }

    self->stack_top -= get_item_size(self->stack_top);
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

    return stack_push(self, get_item_data_ptr_from(self->stack_top, index), get_item_size_from(self->stack_top, index));
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

    uint8_t* first_item_data_ptr = get_item_data_ptr_from(self->stack_top, 1);
    size_t second_item_data_size = get_item_size_from(self->stack_top, 0);

    stack_copy_from(self, 1); // make temp copy of first
    stack_copy_from(self, 1); // make temp copy of second

    memcpy(first_item_data_ptr, get_item_data_ptr(self->stack_top), get_item_size(self->stack_top) + sizeof(size_t)); // move temp copy of second to former place of first

    stack_remove_top(self); // remove temp copy of second

    memcpy(first_item_data_ptr + second_item_data_size + sizeof(size_t), get_item_data_ptr(self->stack_top), get_item_size(self->stack_top) + sizeof(size_t)); // move temp copy of first to end of new second

    stack_remove_top(self); // remove temp copy of first

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

    printf("item_size: %lu\n", item_size);

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

