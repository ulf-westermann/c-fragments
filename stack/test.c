#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>


// test
int main(void)
{
    stack_t s;
    uint32_t buffer[9];
    uint8_t read_buffer[9];
    size_t read_length;

    assert(stack_init(&s, (uint8_t*)buffer, sizeof(buffer)) == 0);
    assert(stack_remove_all(&s) == 0);
    assert(stack_pop(&s, read_buffer, 9, &read_length) < 0);
    assert(stack_push(&s, (uint8_t[]){1, 2, 3}, 3) == 0);
    assert(stack_push(&s, (uint8_t[]){4, 5, 6}, 3) == 0);
    assert(stack_push(&s, (uint8_t[]){7, 8, 9}, 3) == 0);
    assert(stack_push(&s, (uint8_t[]){10}, 1) < 0);
    assert(stack_get_count(&s) == 3);
    assert(stack_pop(&s, read_buffer, 2, &read_length) < 0);
    assert(stack_get_count(&s) == 3);
    assert(stack_pop(&s, read_buffer, 3, &read_length) == 0);
    assert(stack_get_count(&s) == 2);
    assert(memcmp(read_buffer, (uint8_t[]){7, 8, 9}, 3) == 0);
    assert(stack_dup(&s) == 0);
    assert(stack_get_count(&s) == 3);
    assert(stack_remove_top(&s) == 0);
    assert(stack_get_count(&s) == 2);


    printf("test success\n");

    return 0;
}
