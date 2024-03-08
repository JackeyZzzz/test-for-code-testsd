/**
 * @file main.c
 * @author JackeyZ
 * @brief STM32F103C8T6 Template projects
 * @version 0.1
 * @date 2023-1-21
 * 
 * @copyright Copyright (c) JackeyZ
 * 
 */
#include "led.h"
#include "stm32f10x.h"
#include "sys.h"


/**
 * @brief Initial LED GPIO
 * @note  PA1    --  WORK LED
 * @note  PA15   --  SIGNAL LED 
 */
void InitWorkLed(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

/**
 * @brief 工作指示灯亮
 * 
 */
void WorkLedOn(void)
{
   PBout(5) = 1;
}
/**
 * @brief 工作指示灯灭
 * 
 */
void WorkLedOff(void)
{
   PBout(5) = 0;  
}
/**
 * @brief 工作指示灯轮转
 * 
 */
void WorkLedTurn(void)
{
  if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0) == SET)
	{
			PAout(0) = 0; 
	 }
	else
	{
			PAout(0) = 1; 
	 }
}
/**
 * @brief 信号指示灯亮
 * 
 */
void SignalLedOn(void)
{
   PAout(1) = 1;
}
/**
 * @brief 信号指示灯亮
 * 
 */
void SignalLedOff(void)
{
   PAout(1) = 0; 
}


