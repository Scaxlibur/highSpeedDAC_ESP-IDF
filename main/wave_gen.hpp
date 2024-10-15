#ifndef WAVE_GEN_H

#pragma once

#include <math.h>
#include "driver/gptimer.h"

#define WAVE_GEN_H
#define SAMPLE_PER_CYCLE 256
#define ADC_MAX_VALUE 16384
#define ADC_MAX_VOLTAGE 3.3f
#define PI 3.14159
#define TIME_CLOCK_HZ (80 * 1000 * 1000)

enum WAVE_TYPE
{
    SIN = 1,
    SQUARE,
    SAWTOOTH
};

class WAVE_GEN
{
public:
    /* 波形发生器参数配置 */
    double uMaxValue = 3.3;         // 峰峰值
    double offSetValue = 1.65;      // 偏置电压
    int duty = 50;                  // 占空比%(方波)
    WAVE_TYPE wave_type = SAWTOOTH; // 波形种类
    unsigned int freq = 100;        // 频率
    // String param = "";

    unsigned int freq_old = 100;        // 上一次的频率
    uint8_t waveTab1[SAMPLE_PER_CYCLE]; // 生成的波形数据

    uint32_t sample_rate = 8000; // i2s_adc的采样速度，仅用于发送
    uint8_t sampleStep = 1;      // i2s_adc的取样间隔，仅用于发送
    uint8_t trigger_mode = 3;    // i2s_adc的触发模式，仅用于发送

    /* 波形模式切换按键 */
    const int button = 12; // 波形切换引脚位置
    char received_data[5] = {0};
    unsigned int rec_cnt1 = 0;

    /*波形定时器设定*/
    gptimer_handle_t waveCounterTimer_handle = NULL;
    //gptimer_handle_t& _waveCounterTimer_handle = waveCounterTimer_handle;
    gptimer_config_t waveCounterTimer_config = {
        .clk_src = GPTIMER_CLK_SRC_APB,     // 时钟源,APB时钟最快不超过80MHz
        .direction = GPTIMER_COUNT_UP,      // 时钟计数方向
        .resolution_hz = TIME_CLOCK_HZ,     // 80MHz, 1 tick = 0.125us             //时钟频率配置
        .intr_priority = 0,                 // 中断优先级
    };
    gptimer_alarm_config_t waveCounterTimer_alarm_config = {
        .alarm_count = 10,                  // 到达这个数时警报
        .reload_count = 1,                  // 重载的数值
        .flags = {
            .auto_reload_on_alarm = true,   // 是否自动重载
        }
    };

    /* 各种函数，波形发生器相关以及定时器相关的 */
    WAVE_GEN(double uMaxValue, double offSetValue, int duty, unsigned int freq, WAVE_TYPE wave_type);
    ~WAVE_GEN();
    int set_uMaxValue(double value);
    int set_offSetValue(double value);
    int set_duty(int value);
    int set_freq(int value);
    int set_wave_type(WAVE_TYPE wave_type);
    // String get_param();
    bool waveAlramTimer_config();
    void initTimer();
    void updateTimer();
    void get_waveindex();
    void waveSelect(int wave);
    void waveGen(WAVE_TYPE wave_type);
    void adjust_step();
};

#endif