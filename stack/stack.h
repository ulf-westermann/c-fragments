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
 * @param[in] self: stack instance.
 * @param[in] buffer: pointer to the externally allocated buffer for the stack.
 * @param[in] buffer_size: size of buffer in bytes.
 * @return 0 on success, negative value on error. */
int stack_init(stack_t* self, uint8_t* buffer, size_t buffer_size);


/** put data onto the top of the stack.
 * @param[in] self: the stack instance.
 * @param[in] data: pointer to data.
 * @param[in] data_length: length of data in bytes.
 * @return 0 on success, negative value on error. */
int stack_push(stack_t* self, uint8_t* data, size_t data_length);


/** remove topmost item from stack.
 * @param[in] self: the stack instance.
 * @param[out] data: data from stack.
 * @param[in] max_data_size: maximum size of data to copy. fails if size is not large enough.
 * @param[out] data_length: length of data from stack in bytes.
 * @return 0 on success, negative value on error. */
int stack_pop(stack_t* self, uint8_t* data, size_t max_data_size, size_t* data_length);


/** remove topmost item.
 * @param[in] self: the stack instance.
 * @return 0 on success, negative value on error. */
int stack_remove_top(stack_t* self);


/** remove all items from stack.
 * @param[in] self: the stack instance.
 * @return 0 on success, negative value on error. */
int stack_remove_all(stack_t* self);


/** put a copy of another stack item on the top of the stack.
 * @param[in] self: the stack instance.
 * @param[in] index: index of the item to copy. 0 is the topmost item.
 * @return 0 on success, negative value on error. */
int stack_copy_from(stack_t* self, uint32_t index);


/** put a copy of the item currently in the top position on the top of the stack.
 * @param[in] self: the stack instance.
 * @return 0 on success, negative value on error. */
int stack_dup(stack_t* self);


/** swap the two topmost items on the stack.
 * @param[in] self: the stack instance.
 * @return 0 on success, negative value on error. */
int stack_swap(stack_t* self);


/** get number of items on the stack.
 * @param[in] self: the stack instance.
 * @return the number of items on the stack. */
size_t stack_get_count(stack_t* self);


#ifdef __cplusplus
}
#endif


#endif
