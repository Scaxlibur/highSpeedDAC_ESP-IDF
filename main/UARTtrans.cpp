#include "UARTtrans.hpp"

static const int RX_BUF_SIZE = 1024;  //串口接收缓冲区大小

const uart_config_t uart2pc_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    //.source_clk = UART_SCLK_APB,
};

const uart_config_t uart2screen_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    //.source_clk = UART_SCLK_APB,
};

void init_uart2pc(void)        //配置连接到PC的UART
{
    uart_param_config(UART_NUM_PC, &uart2pc_config);
    uart_set_pin(UART_NUM_PC, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_PC, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
}

void init_uart2screen(void)        //配置连接到串口屏的UART
{
    uart_param_config(UART_NUM_SCREEN, &uart2screen_config);
    uart_set_pin(UART_NUM_SCREEN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_SCREEN, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
}