/*******************************************************************************
****文件路径         : .\main\GPIOformat.cpp
****作者名称         : Scaxlibur
****文件版本         : V1.0.0
****创建日期         : 2024-10-08 15:22:26
****简要说明         : 初始化专用GPIO组
********************************************************************************/
#include "GPIOformat.hpp"

// 配置并行输出GPIO
bool GPIOformat(){
    //14是时钟位
    const int Parallel_gpios[] = {0, 1, 2, 3, 4, 5, 6, 7};
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
    };
    for (int i = 0; i < sizeof(Parallel_gpios) / sizeof(Parallel_gpios[0]); i++)
    {
        io_conf.pin_bit_mask = 1ULL << Parallel_gpios[i];
        gpio_config(&io_conf);
    }
    // 创建 Parallel，仅输出
    dedic_gpio_bundle_handle_t Parallel = NULL;
    dedic_gpio_bundle_config_t Parallel_config = {
        .gpio_array = Parallel_gpios,
        .array_size = sizeof(Parallel_gpios) / sizeof(Parallel_gpios[0]),
        .flags = {
            .out_en = 1,
        },
    };
    ESP_ERROR_CHECK(dedic_gpio_new_bundle(&Parallel_config, &Parallel));
    return true;
}

//gpio输出