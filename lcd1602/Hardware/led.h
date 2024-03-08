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
#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"
#define Led_Port GPIOA
#define LED4_Pin GPIO_Pin_12 // 单片机旁边的呼吸灯
#define LED5_Pin GPIO_Pin_11 // 电源开关旁边的呼吸灯

//#define RCC_Led(flag) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)

//#define LED_Twinkle 1000 // Led闪烁间隔（单位ms）

#define WorkLedToggle() GPIOB->ODR ^= GPIO_Pin_5; //



void InitWorkLed(void);
void WorkLedOn(void);
void WorkLedOff(void);
void WorkLedTurn(void);
void SignalLedOn(void);
void SignalLedOff(void);

#endif
