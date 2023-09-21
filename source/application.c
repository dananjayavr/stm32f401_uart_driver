//
// Created by Dananjaya RAMANAYAKE on 26/08/2023.
//

#include <string.h>
#include "application.h"
#include "stm32f4xx_ll_gpio.h"
#include "main.h"

#define RX_CHAR_COUNT 1
uint8_t buffer[RX_CHAR_COUNT];

#define RING_BUFFER_LENGTH 128 // make it 128 later

ring_buffer_t rb = {0};
uint8_t ring_buf[RING_BUFFER_LENGTH] = {0};
uint8_t ring_buf_rx[RING_BUFFER_LENGTH] = {0};

uint8_t local_counter = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // Not Implemented
}

void setup(void) {

    ring_buffer_setup(&rb,ring_buf,RING_BUFFER_LENGTH);
    uart_setup();
    uart_write("UART & Ring Buffer Demo\r\n",25);
}

void loop(void) {
    HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
    HAL_GPIO_TogglePin(TEST_PIN_GPIO_Port,TEST_PIN_Pin);

    uart_read(buffer,RX_CHAR_COUNT);

    if(uart_data_available()) {
        ring_buffer_write(&rb, buffer);
        uart_write(buffer,RX_CHAR_COUNT);
        local_counter++;
    }

    if(local_counter == RING_BUFFER_LENGTH ) {
        for (int i = 0; i < RING_BUFFER_LENGTH; i++) {
            uint8_t byte;
            ring_buffer_read(&rb,&byte);
            ring_buf_rx[i] = byte;
        }
        uart_write("\r\n",2);
        uart_write("ring buffer contents:\r\n",23);
        uart_write(ring_buf_rx,RING_BUFFER_LENGTH);
        uart_write("\r\n",2);

        local_counter = 0;
    }

    HAL_Delay(100);
}
