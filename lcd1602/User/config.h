/**
 * @file config.h
 * @author JackeyZ
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) JackeyZ
 * 
 */
#ifndef __CONFIG_H_
#define	__CONFIG_H_
#include "stm32f10x.h"


#define TRUE 1
#define FALSE 0

#define KEY_RELEASE                    0      // 按键松开
#define MENU_LONG_PRESS             0x11      // 菜单按键长按
#define MENU_SHORT_PRESS               1      // 菜单按键短按
#define UP_LONG_PRESS               0x22      // 加键按键长按
#define UP_SHORT_PRESS                 2      // 加键按键短案
#define DOWN_LONG_PRESS             0x33      // 减键按键长按
#define DOWN_SHORT_PRESS               3      // 减键按键短按
#define SPEED_LONG_PRESS            0x44      // 速度按键长按
#define SPEED_SHORT_PRESS              4      // 速度按键短按

#define LOGO_FLAG_ONE                  1  
#define LOGO_FLAG_TWO                  2  

#define SHOW_DATA                      1      // 主界面
#define SHOW_SETTING                   2      // 设置界面

//#define NORMAL 0
//#define REVERSE_DISPLAY 1


typedef struct
{
  uint8_t type;
  uint16_t data;
}SensorTypeDef;


#endif
