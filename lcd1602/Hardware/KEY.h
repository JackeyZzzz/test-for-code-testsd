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
#ifndef __KEY_H
#define __KEY_H

extern uint8_t even_key_menu,even_key_up,even_key_down,even_key_speed;

void InitKey(void);
void KeyScan(void);
void KeyTask(void);
uint8_t GetKeyNum(void);

void MenuLongKeyHandle(void);
void SetSetingPageAdd(void);
void SetSetingPageSub(void);
void SpeedShortKeyHandle(void);
void MenuShortKeyHandle(void);

#endif
