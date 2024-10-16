#ifndef _UARTtrans_H
#define _UARTtrans_H
#pragma once

#include "driver/uart.h" 
#define UART_NUM_PC UART_NUM_1
#define UART_NUM_SCREEN UART_NUM_2
#define UART_NUM_SCREEN_TX 
#define UART_NUM_SCREEN_RX UART_NUM_2


void init_uart2pc(void);
void init_uart2screen(void);

#endif