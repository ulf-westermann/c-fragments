/** \file
 * a queue (FIFO).
 */

#ifndef QUEUE_H
#define QUEUE_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/** internal control structure of queue. to create a queue, create an instance of this type and initialize it
 * with queue_init().
 */
typedef struct queue_s {
    size_t item_size;
    uint8_t* buffer;
    size_t buffer_size;
    uint32_t count;
    uint32_t read_index;
    uint32_t write_index;
} queue_t;


/** initialize queue.
 * @param[in] self: the queue instance.
 * @param[in] item_size: the size of one buffer entry in bytes.
 * @param[in] buffer: a pointer to the externally allocated buffer for the queue.
 * @param[in] buffer_size the buffer size in bytes. should be a multiple of item_size.
 * @return 0 on success, negative value on error. */
int queue_init(queue_t* self, size_t item_size, uint8_t* buffer, size_t buffer_size);


/** read from queue without removing entry.
 * @param[in] self: the queue instance.
 * @param[out] value: the read value.
 * @return 0 on success, negative value on error. */
int queue_peek(queue_t* self, void* value);


/** read from queue and remove entry.
 * @param[in] self: the queue instance.
 * @param[out] value: the read value.
 * @return 0 on success, negative value on error. */
int queue_read(queue_t* self, void* value);


/** write to queue.
 * @param[in] self: the queue instance.
 * @param[in] value: the value to be stored in the queue.
 * @param[in] overwrite: if queue is full, overwrite oldest entry if true, otherwise fail.
 * @return 0 on success, negative value on error. */
int queue_write(queue_t* self, void* value, bool overwrite);


/** get number of items in the queue.
 * @param[in] self: the queue instance.
 * @return the number of items in the queue. */
uint32_t queue_get_count(queue_t* self);


#ifdef __cplusplus
}
#endif


#endif
