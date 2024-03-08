#ifndef __LCD1602_H
#define __LCD1602_H 

#include "stm32f10x.h"

/***************************根据自己的硬件引脚做修改*****************************/
#define LCD_RS_Set()	GPIO_SetBits( GPIOB, GPIO_Pin_12 )//1602的数据/指令选择控制线
#define LCD_RS_Clr()	GPIO_ResetBits( GPIOB, GPIO_Pin_12 )

#define LCD_RW_Set()	GPIO_SetBits( GPIOB, GPIO_Pin_13 )//1602的读写控制线
#define LCD_RW_Clr()	GPIO_ResetBits( GPIOB, GPIO_Pin_13 )

#define LCD_EN_Set()	GPIO_SetBits( GPIOB, GPIO_Pin_14 )//1602的使能控制线
#define LCD_EN_Clr()	GPIO_ResetBits( GPIOB, GPIO_Pin_14 )

#define DATAOUT( x ) GPIO_Write( GPIOA, x )	//1602的8条数据控制线

void GPIO_Configuration();

void LCD1602_Init();

void LCD1602_Wait_Ready();

void LCD1602_Write_Cmd( uint8_t cmd );

void LCD1602_Write_Dat( uint8_t data );

void LCD1602_ClearScreen();

void LCD1602_Set_Cursor( uint8_t x, uint8_t y );

void LCD1602_Show_Str( uint8_t x, uint8_t y, char *str );

void LCD1602_Show_Num( uint8_t x, uint8_t y, uint8_t Num ,unsigned char i);

void LCD1602_Show_Code(uint8_t x, uint8_t y, char index );

#endif