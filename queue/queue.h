/** \file
 * a queue.
 */

#ifndef QUEUE_H
#define QUEUE_H


#include <stdbool.h>
#include <stdint.h>


/** CONFIGURATION: to use a different data type, modify it here or define it before including the header file. */
#ifndef QUEUE_ENTRY_TYPE
#define QUEUE_ENTRY_TYPE uint32_t
#endif

#define QUEUE_ENTRY_SIZE sizeof(QUEUE_ENTRY_TYPE)


/** internal control structure of queue. to create a queue, create an instance of this type and initialize it
 * with queue_init().
 */
typedef struct queue_s {
    QUEUE_ENTRY_TYPE* buffer;
    uint32_t capacity;
    uint32_t count;
    uint32_t read_index;
    uint32_t write_index;
} queue_t;


/** initialize queue.
 * second parameter is a pointer to the externally allocated buffer for the queue.
 * third parameter is the buffer size in bytes. should be a multiple of QUEUE_ENTRY_SIZE.
 * returns 0 on success, negative value on error. */
void queue_init(queue_t* queue, QUEUE_ENTRY_TYPE* buffer, uint32_t buffer_size);


/** read from queue without removing entry.
 * second parameter received the read value.
 * returns 0 on success, negative value on error. */
int queue_peek(queue_t* queue, QUEUE_ENTRY_TYPE* value);


/** read from queue and remove entry.
 * second parameter received the read value.
 * returns 0 on success, negative value on error. */
int queue_read(queue_t* queue, QUEUE_ENTRY_TYPE* value);


/** write to queue, fails if queue is full when overwrite is false.
 * second parameter is the value to be stored in the queue.
 * third parameter overwrites oldest entry, if queue is full
 * returns 0 on success, negative value on error. */
int queue_write(queue_t* queue, QUEUE_ENTRY_TYPE* value, bool overwrite);


/** get number of items in the queue. */
uint32_t queue_get_count(queue_t* queue);


#endif
