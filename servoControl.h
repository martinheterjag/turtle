/*
Author: Martin Eriksson

servoControl.h for turtle project
KTH, course IS1300 Inbyggda System
*/

#ifndef __SERVO_CONTROL_H
#define __SERVO_CONTROL_H

//defines

//includes
#include "stm32f30x_it.h"
#include "stm32f30x.h"
#include "stm32f3_discovery.h"

//functions
void initPWM(void);
void penUp(void);
void penDown(void);


#endif