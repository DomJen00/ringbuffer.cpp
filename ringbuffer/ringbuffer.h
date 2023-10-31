#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint32_t nbOfElements;
	uint32_t size;
	uint32_t readOffset;
	uint32_t writeOffset;
	int32_t* value;        
} RingBuffer_t;

/*
 * creates a new ring buffer which is able to store
 * up to [maxSize] elements
 */
RingBuffer_t* ring_create(uint32_t);

/*
 * deletes the ring and the ring's data
 */
void ring_delete(RingBuffer_t*);

/*
 * adds the element to the ring buffer
 */
void ring_add(RingBuffer_t*, int);

/*
 * removes and returns the oldest element from ring
 */
bool ring_remove(RingBuffer_t*, int*);