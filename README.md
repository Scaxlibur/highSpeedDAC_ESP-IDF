# ESP32-S3用于并口DAC通信的测试
尚在测试中，还没整明白

用AD9744作为DAC，制作了一个波形发生器

编译环境是ESP-IDF v5.3.1

## 遇到的问题

### ESP32-S3采用何种方式与DAC通信？

#### 1.使用库函数操作GPIO

不可行，库函数操作太慢。

#### 2.通过写寄存器操作GPIO

有可行性，但通过写寄存器翻转GPIO只能实现约3.6MHz的速度，对于高频信号而言捉襟见肘，可作为保留方案。

实际上，ESP32-S3写寄存器后，会检查寄存器是否正确写入，笔者推测这一步消耗了大量指令周期，导致翻转速度降低。

#### 3.通过专用GPIO组进行通信

ESP32-S3支持使用汇编代码或调用 CPU 低层 API 来操作 GPIO，ESP32-S3有GPIO控制指令可以使用，库中也有对应的辅助内联函数。

以下内容摘自[`ESP32-IDF编程指南`]([https://docs.espressif.com/projects/esp-idf/zh_CN/v5.3.1/esp32s3/api-reference/peripherals/dedic_gpio.html#_CPPv421dedic_gpio_new_bundlePK26dedic_gpio_bundle_config_tP26dedic_gpio_bundle_handle_t](https://docs.espressif.com/projects/esp-idf/zh_CN/v5.3.1/esp32s3/api-reference/peripherals/dedic_gpio.html))

> 高阶用户可以通过编写汇编代码或调用 CPU 低层 API 来操作 GPIO。常见步骤为：
>
> 1. 分配一个 GPIO 捆绑包：[`dedic_gpio_new_bundle()`](https://docs.espressif.com/projects/esp-idf/zh_CN/v5.3.1/esp32s3/api-reference/peripherals/dedic_gpio.html#_CPPv421dedic_gpio_new_bundlePK26dedic_gpio_bundle_config_tP26dedic_gpio_bundle_handle_t)
> 2. 查询该包占用的掩码：[`dedic_gpio_get_out_mask()`](https://docs.espressif.com/projects/esp-idf/zh_CN/v5.3.1/esp32s3/api-reference/peripherals/dedic_gpio.html#_CPPv423dedic_gpio_get_out_mask26dedic_gpio_bundle_handle_tP8uint32_t) 和/或 [`dedic_gpio_get_in_mask()`](https://docs.espressif.com/projects/esp-idf/zh_CN/v5.3.1/esp32s3/api-reference/peripherals/dedic_gpio.html#_CPPv422dedic_gpio_get_in_mask26dedic_gpio_bundle_handle_tP8uint32_t)
> 3. 调用 CPU LL apis（如 cpu_ll_write_dedic_gpio_mask）或使用该掩码编写汇编代码
> 4. 切换 IO 的最快捷方式是使用专用的“设置/清除”指令：

然而遗憾的是，ESP32-S3的一个核只能控制1个专用GPIO组，即8个GPIO口。这样的精度太低，而利用两个核心控制两个GPIO组，又会出现时钟同步的问题，较为麻烦。但通过专用GPIO进行GPIO翻转，其翻转速度可以达到近20MHz，今后或许可以通过专用GPIO组模拟某些协议。

#### 4.通过LCD控制模块进行通信

ESP32-S3支持LCD外设，支持8或16位位宽和两个时钟位，时钟可达40MHz。笔者认为此种并口通信方式与DAC的通信有共同之处，是一个可行的方向。但LCD控制模块有颜色空间转换之类的配置，这些配置项是否对DAC通信造成干扰，尚待进一步测试。

## 项目结构

还没想好，搞明白了再写

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
