/**
 * @file timer.h
 * @author JackeyZ
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) JackeyZ
 * 
 */
#include "stm32f10x.h"

extern uint16_t workledcnt; 
extern uint8_t flickerFlag;
 

void InitTimer(void);
void TIMx_Init(TIM_TypeDef* TIMx,u16 Psc,u16 Arr);
