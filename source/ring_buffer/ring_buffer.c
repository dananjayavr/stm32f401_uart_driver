//
// Created by Dananjaya RAMANAYAKE on 21/09/2023.
//

#include "ring_buffer.h"

void ring_buffer_setup(ring_buffer_t *rb, uint8_t *buffer, uint32_t size) {
    // ring buffer setup
    rb->buffer = buffer;
    rb->mask = size - 1;
}

uint8_t ring_buffer_write(ring_buffer_t *rb, uint8_t *byte) {
    uint32_t local_write_index = rb->write_index;
    uint32_t local_read_index = rb->read_index;

    uint32_t next_write_index = (local_write_index + 1) & rb->mask;

    if(next_write_index == local_read_index) {
        return 0; // buffer empty
    }

    rb->buffer[local_write_index] = *byte;
    rb->write_index = next_write_index;

    return 1;
}

uint8_t ring_buffer_read(ring_buffer_t *rb, uint8_t *byte) {
    uint32_t local_read_index;
    uint32_t local_write_index;

    local_read_index = rb->read_index;
    local_write_index = rb->write_index;

    if(local_read_index == local_write_index) {
        return 0; // buffer empty
    }

    *byte = rb->buffer[local_read_index];
    local_read_index = (local_read_index + 1) & rb->mask;
    rb->read_index = local_read_index;

    return 1;

}

uint8_t ring_buffer_empty(ring_buffer_t *rb) {
    return rb->read_index == rb->write_index;
}
