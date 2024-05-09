#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>


static stack_t s;
static uint8_t buffer[40];


void print_stack(void) {
    uint32_t top = s.stack_top - s.buffer;

    printf("stack:   ");

    for (uint32_t i = 0; i < sizeof(buffer); i += 1)
    {
        printf("%02x ", buffer[i]);
    }
    
    printf("\n");


    printf("top pos: ");

    for (uint32_t i = 0; i < top; i += 1)
    {
        printf("   ");
    }

    printf("*\n");

    printf("stack top byte index (one beyond data): %u\n", top);
}


// test
int main(void)
{
    uint8_t read_buffer[9];
    size_t read_length;

    // init
    printf("stack_init(). should succeed...\n");
    assert(stack_init(&s, (uint8_t*)buffer, sizeof(buffer)) == 0);
    assert(stack_get_count(&s) == 0);
    print_stack();

    // tests with empty stack
    printf("stack_remove_all(). should succeed...\n");
    assert(stack_remove_all(&s) == 0);
    assert(stack_get_count(&s) == 0);

    printf("stack_pop(). should fail...\n");
    assert(stack_pop(&s, read_buffer, 2, &read_length) < 0);
    assert(stack_get_count(&s) == 0);

    printf("stack_dup(). should fail...\n");
    assert(stack_dup(&s) < 0);
    assert(stack_get_count(&s) == 0);

    printf("stack_swap(). should fail...\n");
    assert(stack_swap(&s) < 0);
    assert(stack_get_count(&s) == 0);

    printf("stack_remove_top(). should fail...\n");
    assert(stack_remove_top(&s) < 0);
    assert(stack_get_count(&s) == 0);

    print_stack();

    // filling stack
    printf("stack_push(). should succeed...\n");
    assert(stack_push(&s, (uint8_t[]){1, 2}, 2) == 0);
    print_stack();

    printf("stack_push(). should succeed...\n");
    assert(stack_push(&s, (uint8_t[]){3, 4}, 2) == 0);
    print_stack();

    printf("stack_push(). should succeed...\n");
    assert(stack_push(&s, (uint8_t[]){5, 6}, 2) == 0);
    print_stack();

    printf("stack_push(). should succeed...\n");
    assert(stack_push(&s, (uint8_t[]){7, 8}, 2) == 0);
    print_stack();

    // tests with full stack
    printf("stack_push(). should fail...\n");
    assert(stack_push(&s, (uint8_t[]){10}, 1) < 0);
    assert(stack_get_count(&s) == 4);

    printf("stack_dup(). should fail...\n");
    assert(stack_dup(&s) < 0);
    assert(stack_get_count(&s) == 4);

    printf("stack_copy_from(). should fail...\n");
    assert(stack_copy_from(&s, 1) < 0);
    assert(stack_get_count(&s) == 4);

    printf("stack_swap(). should fail...\n");
    assert(stack_swap(&s) < 0);
    assert(stack_get_count(&s) == 4);

    print_stack();

    // normal operations on half filled stack
    printf("stack_pop(). stack contains 1,2,3,4,5,6,7,8. should fail...\n");
    assert(stack_pop(&s, read_buffer, 1, &read_length) < 0);
    assert(read_length == 2);
    assert(stack_get_count(&s) == 4);
    print_stack();

    printf("stack_pop(). stack contains 1,2,3,4,5,6,7,8. should succeed...\n");
    assert(stack_pop(&s, read_buffer, 2, &read_length) == 0);
    assert(memcmp(read_buffer, (uint8_t[]){7, 8}, 2) == 0);
    assert(stack_get_count(&s) == 3);
    print_stack();

    printf("stack_dup(). stack contains 1,2,3,4,5,6. should succeed...\n");
    assert(stack_dup(&s) == 0);
    assert(stack_get_count(&s) == 4);
    print_stack();

    printf("stack_pop(). stack contains 1,2,3,4,5,6,5,6. should succeed...\n");
    assert(stack_pop(&s, read_buffer, 2, &read_length) == 0);
    assert(memcmp(read_buffer, (uint8_t[]){5, 6}, 2) == 0);
    assert(stack_get_count(&s) == 3);
    print_stack();

    printf("stack_copy_from(). stack contains 1,2,3,4,5,6. should succeed...\n");
    assert(stack_copy_from(&s, 1) == 0);
    assert(stack_get_count(&s) == 4);
    print_stack();

    printf("stack_pop(). stack contains 1,2,3,4,5,6,3,4. should succeed...\n");
    assert(stack_pop(&s, read_buffer, 2, &read_length) == 0);
    assert(memcmp(read_buffer, (uint8_t[]){3, 4}, 2) == 0);
    assert(stack_get_count(&s) == 3);
    print_stack();

    printf("stack_pop(). stack contains 1,2,3,4,5,6. should succeed...\n");
    assert(stack_pop(&s, read_buffer, 2, &read_length) == 0);
    assert(memcmp(read_buffer, (uint8_t[]){5, 6}, 2) == 0);
    assert(stack_get_count(&s) == 2);
    print_stack();

    printf("stack_swap(). stack contains 1,2,3,4. should succeed...\n");
    assert(stack_swap(&s) == 0);
    assert(stack_get_count(&s) == 2);

    printf("stack_pop(). stack contains 3,4,1,2. should succeed...\n");
    assert(stack_pop(&s, read_buffer, 2, &read_length) == 0);
    assert(memcmp(read_buffer, (uint8_t[]){1, 2}, 2) == 0);
    assert(stack_get_count(&s) == 1);
    print_stack();

    printf("stack_pop(). stack contains 3,4. should succeed...\n");
    assert(stack_pop(&s, read_buffer, 2, &read_length) == 0);
    assert(memcmp(read_buffer, (uint8_t[]){3, 4}, 2) == 0);
    assert(stack_get_count(&s) == 0);
    print_stack();

    printf("test success\n");

    return 0;
}
