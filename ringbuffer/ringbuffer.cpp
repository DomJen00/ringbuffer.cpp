#include <iostream>
#include "malloc.h"

#include "ringbuffer.h"

RingBuffer_t* ring_create(uint32_t size) {
	RingBuffer_t* pRingbuffer = (RingBuffer_t *)malloc(sizeof(RingBuffer_t));
	if (pRingbuffer == NULL) {
		std::cout << "Ringbuffer out of memory\n";
		return;
	}

	pRingbuffer->value = (int *)malloc(size * sizeof(int));
	if (pRingbuffer->value == NULL) {		
		free(pRingbuffer);
		std::cout << "Ringbuffer out of memory\n";
		return;
	}

	pRingbuffer->size = size;
	pRingbuffer->nbOfElements = 0;
	pRingbuffer->readOffset = 0;
	pRingbuffer->writeOffset = 0;
	
	return pRingbuffer;
}

void ring_delete(RingBuffer_t* pRingbuffer) {
	free(pRingbuffer->value);
	free(pRingbuffer);
}

void ring_add(RingBuffer_t* pRingbuffer, int element) {
	pRingbuffer->value[pRingbuffer->writeOffset] = element;
	pRingbuffer->writeOffset = (pRingbuffer->writeOffset + 1) % pRingbuffer->size;
	if (pRingbuffer->nbOfElements < pRingbuffer->size) {
		pRingbuffer->nbOfElements += 1;
	}
}

bool ring_remove(RingBuffer_t* pRingbuffer, int* result) {
	if (pRingbuffer->nbOfElements > 0 && (pRingbuffer->readOffset != pRingbuffer->writeOffset)) {
		*result = pRingbuffer->value[pRingbuffer->readOffset];
		pRingbuffer->readOffset = (pRingbuffer->readOffset + 1) % pRingbuffer->size;
		pRingbuffer->nbOfElements -= 1;
		return true;
	}
	return false;
}