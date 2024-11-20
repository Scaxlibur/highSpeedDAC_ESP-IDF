#pragma once

#include "driver/parlio_tx.h"
#include "driver/parlio_types.h"

class PARLIO{
    private:
        parlio_tx_unit_config_t parlio_conf{
            .clk_src = PARLIO_CLK_SRC_DEFAULT, //默认时钟96MHz
            .output_clk_freq_hz = 96000000,
            .data_width = 16,
            .data_gpio_nums = {
                [0] = GPIO_NUM_1,
                [1] = GPIO_NUM_2,
                [2] = GPIO_NUM_3,
                [3] = GPIO_NUM_4,
                [4] = GPIO_NUM_5,
                [5] = GPIO_NUM_6,
                [6] = GPIO_NUM_7,
                [7] = GPIO_NUM_8,
                [8] = GPIO_NUM_9,
                [9] = GPIO_NUM_10,
                [10] = GPIO_NUM_11,
                [11] = GPIO_NUM_12,
                [12] = GPIO_NUM_13,
                [13] = GPIO_NUM_14,
                [14] = GPIO_NUM_15,
                [15] = GPIO_NUM_16,
                },
            .clk_out_gpio_num = GPIO_NUM_17,
            .valid_gpio_num = GPIO_NUM_18, //检测信号是否有效
            .trans_queue_depth = 32,
            .max_transfer_size = 2,
            .sample_edge = PARLIO_SAMPLE_EDGE_POS,  //时钟的上升沿发送还是下降沿发送
            .bit_pack_order = PARLIO_BIT_PACK_ORDER_LSB,    //字节的高低位顺序
        };
        parlio_tx_unit_handle_t parlioHandle = NULL;

        void parlio_init();
        

    public:
        PARLIO();
        ~PARLIO();
};
