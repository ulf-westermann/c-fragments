#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>


static stack_t s;
static uint8_t buffer[33];


void print_stack(void) {
    printf("stack: ");

    for (uint32_t i = 0; i < sizeof(buffer); i += 1)
    {
        printf("%02x ", buffer[i]);
    }
    
    printf("\n");

    uint32_t top = s.stack_top - s.buffer;
    printf("       ");

    for (uint32_t i = 0; i < top; i += 1)
    {
        printf("   ");
    }

    printf("*\n");

    printf("top: %u\n", top);
}


// test
int main(void)
{
    uint8_t read_buffer[9];
    size_t read_length;

    assert(stack_init(&s, (uint8_t*)buffer, sizeof(buffer)) == 0);
    print_stack();
    assert(stack_remove_all(&s) == 0);
    assert(stack_pop(&s, read_buffer, 9, &read_length) < 0);
    assert(stack_push(&s, (uint8_t[]){1, 2, 3}, 3) == 0);
    print_stack();
    assert(stack_push(&s, (uint8_t[]){4, 5, 6}, 3) == 0);
    print_stack();
    assert(stack_push(&s, (uint8_t[]){7, 8, 9}, 3) == 0);
    print_stack();
    assert(stack_push(&s, (uint8_t[]){10}, 1) < 0);
    assert(stack_get_count(&s) == 3);
    assert(stack_pop(&s, read_buffer, 2, &read_length) < 0);
    print_stack();
    assert(stack_get_count(&s) == 3);
    assert(stack_pop(&s, read_buffer, 3, &read_length) == 0);
    print_stack();
    assert(memcmp(read_buffer, (uint8_t[]){7, 8, 9}, 3) == 0);
    assert(stack_get_count(&s) == 2);
    assert(stack_dup(&s) == 0);
    print_stack();
    assert(stack_get_count(&s) == 3);
    assert(stack_remove_top(&s) == 0);
    assert(stack_get_count(&s) == 2);

    printf("test success\n");

    return 0;
}
