//
// Created by Dananjaya RAMANAYAKE on 01/09/2023.
//

#include "uart.h"

#define RX_COUNT 1

extern UART_HandleTypeDef huart2;

uint8_t rx_data[RX_COUNT];
uint8_t data_available;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    data_available = 1;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    data_available = 0;
}

void uart_setup(void) {
    HAL_UART_Receive_IT(&huart2,rx_data,RX_COUNT);
}

void uart_write(uint8_t* data, const uint32_t length) {
    for (uint32_t i = 0; i < length; i++) {
        uart_write_byte(data[i]);
    }
}

void uart_write_byte(uint8_t data) {
    HAL_UART_Transmit_IT(&huart2,&data,sizeof(uint8_t));
    while (HAL_UART_GetState(&huart2) ==HAL_UART_STATE_BUSY_TX ||
           HAL_UART_GetState(&huart2) == HAL_UART_STATE_BUSY_TX_RX);
}

uint32_t uart_read(uint8_t* data, const uint32_t length) {

    if(length == 0) {
        return 0;
    }

    HAL_UART_Receive_IT(&huart2,rx_data,RX_COUNT);

    for (uint32_t bytes_read = 0; bytes_read < length; bytes_read++) {
        data[bytes_read] = rx_data[bytes_read];
    }

    return length;
}

bool uart_data_available(void) {
    return data_available;
}
