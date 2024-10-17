#include <stdio.h>
#include <string.h>

#include "GPIOformat.hpp"
#include "wave_gen.hpp"
#include "UARTtrans.hpp"


/* 实例化一个波形发生器 */
WAVE_TYPE wave_type = SAWTOOTH;
WAVE_GEN wave_gen(3.3, 1.65, 50, 100, wave_type);

/*******************************************************************************
****函数功能: 核心0上运行的任务2，
****入口参数: *arg:
****出口参数: 无
****函数备注: 将主程序与通信程序分别放两个核心上运行，提高执行速度
********************************************************************************/
void Task2(void *arg)
{
  vTaskDelay(50 / portTICK_PERIOD_MS);
  while (true)
  {

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

/*******************************************************************************
****函数功能: 串口通信函数
****出口参数: 无
****函数备注: 解析串口接收到的上位机指令
********************************************************************************/
void command_loop(void)
{
  int length = 0;
  uart_get_buffered_data_len(UART_NUM_PC, (size_t*)&length);
  // 如果串口是空的直接返回
  if (length == 0) return;
  char received_chars[10];
  vTaskDelay(1 / portTICK_PERIOD_MS);
  // 从串口读取返回的数据，读取20个字符
  uart_read_bytes(UART_NUM_PC, received_chars, length, 100);

  // 根据指令做不同动作
  if (received_chars[0] == 'F') // F指令设置波形发生器频率
  {
    int F = atoi(received_chars + 1);
    wave_gen.set_freq(F);
    //uart_write_bytes(UART_NUM_PC, (const char*)received_chars, strlen(received_chars));
    uart_write_bytes(UART_NUM_PC, (const char*)received_chars, strlen(received_chars));
    //等效于Serial.printf("%s,%d\n", received_chars, F);

  } 
  if (received_chars[0] == 'D') // D指令设置波形发生器占空比
  {
    int D = atoi(received_chars + 1);
    wave_gen.set_duty(D);
    //Serial.printf("%s,%d\n", received_chars, D);
    uart_write_bytes(UART_NUM_PC, (const char*)received_chars, strlen(received_chars));
  }
  if (received_chars[0] == 'U') // U指令设置波形发生器峰峰值
  {
    double U = atof(received_chars + 1);
    wave_gen.set_uMaxValue(U);
    //Serial.printf("%s,%.3f\n", received_chars, U);
    uart_write_bytes(UART_NUM_PC, (const char*)received_chars, strlen(received_chars));
  }
  if (received_chars[0] == 'B') // B指令设置波形发生器偏置电压
  {
    double B = atof(received_chars + 1);
    wave_gen.set_offSetValue(B);
    //Serial.printf("%s,%.3f\n", received_chars, B);
    uart_write_bytes(UART_NUM_PC, (const char*)received_chars, strlen(received_chars));
  }
  if (received_chars[0] == 'W') // W指令设置波形种类
  {
    int W = atoi(received_chars + 1);
    wave_gen.waveSelect(W);
  }
  //  最后清空串口
  while (length >= 0)
    uart_flush(UART_NUM_PC);
}

/*******************************************************************************
****函数功能: 主程序入口
****出口参数: 无
****函数备注: 启动后首先执行setup函数，只执行一次
********************************************************************************/
void setup()
{
  init_uart2pc();//打开串口通信
  /* 初始化波形发生器 */
  wave_gen.initTimer();
  //Serial.println("波形发生器初始化成功");
  /* 创建任务2，建立并保持与上位机的通信 */
  xTaskCreatePinnedToCore(Task2, "Task2", 12 * 1024, NULL, 1, NULL, 0);
  vTaskDelay(50 / portTICK_PERIOD_MS);
}

/*******************************************************************************
****函数功能: loop函数
****出口参数: 无
****函数备注: 程序执行完setup函数后，循环执行loop函数
********************************************************************************/
extern "C" void app_main(void)
{
  setup ();
  while (true)
  {
    command_loop();
    vTaskDelay(45 / portTICK_PERIOD_MS);
  }
}