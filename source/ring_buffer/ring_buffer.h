//
// Created by Dananjaya RAMANAYAKE on 21/09/2023.
//

#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#include <stdint-gcc.h>

typedef struct {
    uint32_t read_index;
    uint32_t write_index;
    uint32_t mask;
    uint8_t *buffer;
} ring_buffer_t;

void ring_buffer_setup(ring_buffer_t *rb, uint8_t *buffer, uint32_t size);
uint8_t ring_buffer_write(ring_buffer_t *rb, uint8_t *byte);
uint8_t ring_buffer_read(ring_buffer_t *rb, uint8_t *byte);
uint8_t ring_buffer_empty(ring_buffer_t *rb);

#endif //_RING_BUFFER_H
