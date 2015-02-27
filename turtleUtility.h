/*
Author: Martin Eriksson

turtleUtility.h for turtle project
KTH, course IS1300 Inbyggda System

Utility functions like timers and such.
*/

#ifndef __TURTLE_UTILITY_H
#define __TURTLE_UTILITY_H

//defines

//includes
#include "stm32f30x_it.h"
#include "stm32f30x.h"
#include "stm32f3_discovery.h"

//FUNCTIONS
void initSystemTimer(void);
void delay(__IO uint32_t nTime);
void timingDelayDecrement(void);


#endif