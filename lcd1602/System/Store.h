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
#ifndef __STORE_H
#define __STORE_H

extern uint16_t Store_Data[];

void InitStore(void);
void StoreSave(void);
void StoreClear(void);

#endif
