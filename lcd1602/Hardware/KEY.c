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
#include "Delay.h"
#include "sys.h"
#include "config.h"
#include "lcd1602.h"
#include "UI.h"
#include "KEY.h"

/* for test */


uint16_t keyMenuCnt,keyUpCnt,keyDownCnt,keySpeedCnt;
uint8_t even_key_menu,even_key_up,even_key_down,even_key_speed;
uint8_t keyMenuLock   = 0;
uint8_t keyShortPress = 0;

void InitKey(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

/**
 * @brief 获取“菜单”按键的值
 * @note   按下键值为0，非按下键值为1
 * @return 按键值 
 */
uint8_t  GetkeyMenuValue(void)
{
    uint8_t value;
    value = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
    return value;
}
/**
 * @brief 获取速度按键的值
 * @note   按下键值为0，非按下键值为1
 * @return 按键值 
 */
uint8_t  GetkeySpeedValue(void)
{
    uint8_t value;
    value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);
    return value;
}
/**
 * @brief 获取向上按键的值
 * @note   按下键值为0，非按下键值为1
 * @return 按键值 
 */
uint8_t  GetkeyUpValue(void)
{
    uint8_t value;
    value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    return value;
}
/**
 * @brief 获取向下按键的值
 * @note   按下键值为0，非按下键值为1
 * @return 按键值 
 */
uint8_t  GetkeyDownValue(void)
{
    uint8_t value;
    value = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14);
    return value;
}

/**
 * @brief 按键扫码产生按键事件
 * 
 */
void KeyScan(void)
{
	if(GetkeyMenuValue())
	{
	    keyMenuLock = 0; 
		keyMenuCnt  = 0;
		if(keyShortPress == 1)
		{
			even_key_menu = MENU_SHORT_PRESS;
			keyShortPress = 0;
		}
	}
	else if(!keyMenuLock)
	{
		keyMenuCnt++;
		if(keyMenuCnt > 50)
		{
			keyShortPress = 1;
		}
		if(keyMenuCnt > 2000)
		{
			keyMenuCnt    = 0;
			keyShortPress = 0;
			keyMenuLock   = 1;
			even_key_menu = MENU_LONG_PRESS;
		}
	}

	if(!GetkeyUpValue())
	{
		keyUpCnt++;
	}
	if(GetkeyUpValue())
	{
		if(keyUpCnt > 3000)//3s long press
		{
			even_key_up = UP_LONG_PRESS;
		}
		else
		{
			if(keyUpCnt > 50)//50ms short press
			{
				even_key_up = UP_SHORT_PRESS;
			}
		}
		keyUpCnt = 0;
	}
		
	if(!GetkeyDownValue())
	{
		keyDownCnt++;
	}
	if(GetkeyDownValue())
	{
		if(keyDownCnt > 3000)//3s long press
		{
			even_key_down = DOWN_LONG_PRESS;
		}
		else
		{
			if(keyDownCnt > 50)//50ms short press
			{
				even_key_down = DOWN_SHORT_PRESS;			
			}
		}
		keyDownCnt = 0;
	
	}

	if(!GetkeySpeedValue())
	{
		keySpeedCnt++;
	}
	if(GetkeySpeedValue())
	{
		if(keySpeedCnt > 3000)//3s long press
		{
			even_key_speed = SPEED_LONG_PRESS;
		}
		else
		{
			if(keySpeedCnt > 50)//50ms short press
			{
				even_key_speed = SPEED_SHORT_PRESS;
			}
		}
		keySpeedCnt = 0;
	}
}


void KeyTask(void)
{
	if(even_key_menu == MENU_SHORT_PRESS )//MENU短按
	{
		MenuShortKeyHandle();
		even_key_menu = KEY_RELEASE;
	}
	else
	{
		if(even_key_menu == MENU_LONG_PRESS )//MENU长按
		{
			even_key_menu = KEY_RELEASE;
			MenuLongKeyHandle();
		}
	}

	if(even_key_up == UP_SHORT_PRESS  )//UP 短按
	{
		even_key_up = KEY_RELEASE;
		SetSetingPageAdd();

	}
	
	if(even_key_down == DOWN_SHORT_PRESS  )//DOWN 短按
	{
		even_key_down = KEY_RELEASE;
		SetSetingPageSub();

	}

	if(even_key_speed == SPEED_SHORT_PRESS  )//SPEED 短按
	{
		SpeedShortKeyHandle();

		even_key_speed = KEY_RELEASE;
	}
}

void MenuShortKeyHandle(void)
{
	if(taskIndex == 0)
	{
		if(GetMainInfPage() == 0)
			SetMainInfPage(1);
		else if(GetMainInfPage() == 1)
			SetMainInfPage(0);
	}

	if( taskIndex == 2 )
	{
		taskIndex = table[taskIndex].back;
	}
}

void MenuLongKeyHandle(void)
{
	if(taskIndex == 0)
		taskIndex = table[taskIndex].enter;// 长按表示确认键
	else if(taskIndex == 1)
		taskIndex = table[taskIndex].back;// 长按表示确认键
}

void SetSetingPageAdd(void)
{
	if(taskIndex == 1)
	{
		ui.menu.item ++ ;
		if(ui.menu.item >= 14)
			ui.menu.item = 0;
	}
	if(taskIndex == 2)
	{
		if(ui.menu.item == 12)
		{
			ui.RunInfo.pageNum ++;
		}
		if(ui.menu.item == 13)
		{
			ui.Version.Flag ++;
			if(ui.Version.Flag > 1)
				ui.Version.Flag = 0;
		}
	}
}

void SetSetingPageSub(void)
{
	if(taskIndex == 1)
	{
		ui.menu.item -- ;
		if(ui.menu.item > 30 )
			ui.menu.item = 13;
	}
	if(taskIndex == 2)
	{
		if(ui.menu.item == 12)
		{
			ui.RunInfo.pageNum --;
		}
		if(ui.menu.item == 13)
		{
			ui.Version.Flag --;
			if(ui.Version.Flag > 15)
				ui.Version.Flag = 1;		
		}
	}
}

void SpeedShortKeyHandle(void)
{	
	static uint8_t keyLock = 0;
	if(taskIndex == 1)
	{
		taskIndex = table[taskIndex].enter;// 短按表示确认键
		keyLock = 0;
	}

	if(taskIndex == 2)
	{	
		if(keyLock == 1)
		{
			uint8_t index = ui.menu.item;
			switch (index)
			{
			case 0:
				ui.TestAnimation.item++;
				if(ui.TestAnimation.item > 4)
					ui.TestAnimation.item = 0;	
				break;
			case 1:
				ui.swSetting.item++;
				if(ui.swSetting.item >1)
					ui.swSetting.item= 0;

			case 2:
				ui.ArtNetSetting.item++;
				if(ui.ArtNetSetting.item > 2)
					ui.ArtNetSetting.item = 0;	
				break;
			case 3:
				ui.AutoID.item++;
				break;
			case 4:
				ui.DMXSetting.item++;
				if(ui.DMXSetting.item > 2)
					ui.DMXSetting.item = 0;
				break;
			case 6:
				ui.setBrightness.item++;
				if(ui.setBrightness.item > 6)
					ui.setBrightness.item = 0;	
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				ui.addrMenu.item++;
				break;
			case 11:
				break;
			case 12:
				break;
			default:
				break;
			}
		}	
		keyLock = 1;	
	}
}