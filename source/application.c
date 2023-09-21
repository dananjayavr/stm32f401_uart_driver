//
// Created by Dananjaya RAMANAYAKE on 26/08/2023.
//

#include <string.h>
#include "application.h"
#include "stm32f4xx_ll_gpio.h"
#include "main.h"

#define RX_CHAR_COUNT 1

uint8_t buffer[RX_CHAR_COUNT];

uint8_t circular_buffer[12];
uint8_t data_ptr = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // Not Implemented
}

void setup(void) {
    uart_setup();
    uart_write("UART & Ring Buffer Demo\r\n",25);
}

void loop(void) {
    HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
    HAL_GPIO_TogglePin(TEST_PIN_GPIO_Port,TEST_PIN_Pin);

    uart_read(buffer,RX_CHAR_COUNT);

    if(uart_data_available()) {
        uart_write(buffer,RX_CHAR_COUNT);
        memcpy(circular_buffer+data_ptr,buffer,1);
        data_ptr++;
    }

    if(data_ptr == 11) {
        uart_write("\r\n",2);
        uart_write("circular_buffer:\r\n",18);
        uart_write(circular_buffer,12);
        uart_write("\r\n",2);

        data_ptr = 0;
    }

    HAL_Delay(100);
}
