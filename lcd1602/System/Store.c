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
#include "MyFLASH.h"

#define STORE_START_ADDRESS		0x0800FC00
#define STORE_COUNT				    512

uint16_t Store_Data[STORE_COUNT];

void InitStore(void)
{
	if (MyFLASH_ReadHalfWord(STORE_START_ADDRESS) != 0xA5A5)
	{
		MyFLASH_ErasePage(STORE_START_ADDRESS);
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS, 0xA5A5);
		for (uint16_t i = 1; i < STORE_COUNT; i ++)
		{
			MyFLASH_ProgramHalfWord(STORE_START_ADDRESS + i * 2, 0x0000);
		}
	}
	
	for (uint16_t i = 0; i < STORE_COUNT; i ++)
	{
		Store_Data[i] = MyFLASH_ReadHalfWord(STORE_START_ADDRESS + i * 2);
	}
}

void StoreSave(void)
{
	MyFLASH_ErasePage(STORE_START_ADDRESS);
	for (uint16_t i = 0; i < STORE_COUNT; i ++)
	{
		MyFLASH_ProgramHalfWord(STORE_START_ADDRESS + i * 2, Store_Data[i]);
	}
}

void StoreClear(void)
{
	for (uint16_t i = 1; i < STORE_COUNT; i ++)
	{
		Store_Data[i] = 0x0000;
	}
	StoreSave();
}
