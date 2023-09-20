//
// Created by Dananjaya RAMANAYAKE on 26/08/2023.
//

#include <string.h>
#include "application.h"
#include "stm32f4xx_ll_gpio.h"
#include "main.h"

#define RX_CHAR_COUNT 4

extern UART_HandleTypeDef huart2;

uint8_t buffer[RX_CHAR_COUNT];


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

    if(uart_data_available())
        uart_write(buffer,RX_CHAR_COUNT);

    HAL_Delay(100);
}
