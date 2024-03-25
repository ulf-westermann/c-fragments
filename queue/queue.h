/** \file
 * Ring buffer.
 */

#ifndef QUEUE_H
#define QUEUE_H


#include <stdint.h>


/** CONFIGURATION: To use a different data type, modify it here or define it before including the header file. */
#ifndef QUEUE_ENTRY_TYPE
#define QUEUE_ENTRY_TYPE uint32_t
#endif

#define QUEUE_ENTRY_SIZE sizeof(QUEUE_ENTRY_TYPE)


typedef struct queue_s {
    QUEUE_ENTRY_TYPE* buffer;
    uint32_t capacity;
    uint32_t count;
    uint32_t read_index;
    uint32_t write_index;
} queue_t;


void queue_init(queue_t* queue, QUEUE_ENTRY_TYPE* buffer, uint32_t length);
int queue_read(queue_t* queue, QUEUE_ENTRY_TYPE* value);
int queue_write(queue_t* queue, QUEUE_ENTRY_TYPE* value);
uint32_t queue_get_count(queue_t* queue);


#endif
