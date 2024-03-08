#ifndef __LCD1602_H
#define __LCD1602_H

#include"sys.h"
#include"stm32f10x.h"

#define  LCD1602_Timer_GPIOA RCC_APB2Periph_GPIOA
#define  LCD1602_Timer_GPIOB RCC_APB2Periph_GPIOB
#define  LCD1602_GPIOA GPIOA
#define  LCD1602_GPIOB GPIOB
#define  LCD1602_RS   GPIO_Pin_1
#define  LCD1602_RW   GPIO_Pin_10
#define  LCD1602_E    GPIO_Pin_11
#define  LCD1602_IO   GPIO_Pin_0 |  GPIO_Pin_1 |  GPIO_Pin_2 |  GPIO_Pin_3 |  GPIO_Pin_4 |  GPIO_Pin_5 |  GPIO_Pin_6 |  GPIO_Pin_7

#define  LCD1602_I0_SET() GPIO_SetBits(GPIOA, LCD1602_IO)

#define  LCD1602_RS_SET()   GPIO_SetBits(GPIOB,LCD1602_RS)
#define  LCD1602_RS_RESET() GPIO_ResetBits(GPIOB,LCD1602_RS)

#define  LCD1602_RW_SET()   GPIO_SetBits(GPIOB,LCD1602_RW)
#define  LCD1602_RW_RESET() GPIO_ResetBits(GPIOB,LCD1602_RW)

#define  LCD1602_E_SET()   GPIO_SetBits(GPIOB,LCD1602_E)
#define  LCD1602_E_RESET() GPIO_ResetBits(GPIOB,LCD1602_E)

   

void LCD1602_Init(void);//液晶初始化函数
void LCD1602_ShowNum(unsigned char x,unsigned char y,unsigned char *str,unsigned char i);//LCD1602显示数字
void LCD1602_ShowStr(unsigned char x,unsigned char y,unsigned char *str);//LCD1602显示字符串


#endif