/*
Author: Martin Eriksson

USART.h for turtle project
KTH, course IS1300 Inbyggda System
*/

#ifndef __USART_H
#define __USART_H

//defines

//includes
#include "stm32f30x_it.h"
#include <string.h>
#include "commands.h"


//functions
void checkUSART3Input(command* cmd);
void initUSART(void);
void USART3InterruptEvent(void);
void USART3Print(uint8_t ch);
void USART3PrintString(volatile char* str);



#endif