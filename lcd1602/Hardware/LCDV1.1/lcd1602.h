#ifndef _LCD1602_H
#define _LCD1602_H

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

#define LCD_RS PBout(1)
#define LCD_RW PBout(10)
#define LCD_EN PBout(11)
#define LCD_VO PBout(0)

#define LCD_BUSY PAin(7)

void Lcd1602_Pin_Init(void);
void Lcd1602_Init(void);
void Lcd1602_Write_Cmd(int cmd);
void Lcd1602_Write_Data(int	data);
void Lcd1602_DisplayChar(u8 row,u8 col,int ch);
void Lcd1602_DisplayString(u8 row,u8 col,u8 *str);

void Lcd1602_Check_Busy(void);

#endif
