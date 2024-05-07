/** \file
 * a queue (FIFO).
 */

#ifndef STACK_H
#define STACK_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/** internal control structure of stack. to create a stack, create an instance of this type and initialize it
 * with stack_init().
 */
typedef struct stack_s {
    uint8_t* buffer;
    uint8_t* buffer_end;
    uint8_t* stack_top;
    uint32_t count;
} stack_t;


/** initialize stack.
 * @param[in] self: the stack instance.
 * @param[in] buffer: a pointer to the externally allocated buffer for the stack.
 * @param[in] buffer_size the buffer size in bytes.
 * @return 0 on success, negative value on error. */
int stack_init(stack_t* self, uint8_t* buffer, size_t buffer_size);


int stack_push(stack_t* self, uint8_t* data, size_t data_size);
int stack_pop(stack_t* self);
int stack_pop_all(stack_t* self);
int stack_copy_from(stack_t* self, uint32_t index);
int stack_dup(stack_t* self);
int stack_swap(stack_t* self);


/** get number of items on the stack.
 * @param[in] self: the stack instance.
 * @return the number of items on the stack. */
size_t stack_get_count(stack_t* self);


#ifdef __cplusplus
}
#endif


#endif
