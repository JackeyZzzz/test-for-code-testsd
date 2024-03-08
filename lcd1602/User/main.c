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
#include "stm32f10x.h"                  // Device header
#include "initial.h"
#include "config.h"
#include "store.h"
#include "lcd1602.h"
#include "led.h"
#include "UI.h"
#include "key.h"
#include "config.h"

int main(void)
{
	InitSystem();                 // 初始化外设
	
	InitStore();                  // flash读取
	
	while (1)
	{		
		GuiRefresh();
		KeyTask();
	}
}
