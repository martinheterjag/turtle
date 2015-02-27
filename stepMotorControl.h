/*
Author: Martin Eriksson

stepMotorControl.h for turtle project
KTH, course IS1300 Inbyggda System
*/

#ifndef __STEP_MOTOR_CONTROL_H
#define __STEP_MOTOR_CONTROL_H

//defines and typedefs
typedef enum{
  FORWARD,
  RIGHT,
  LEFT
}direction;

//includes
#include "stm32f30x_it.h"
#include "stm32f30x.h"
#include "stm32f3_discovery.h"

//functions
void initStepMotor(void);
void turnRightDegrees(uint16_t degrees);
void turnLeftDegrees(uint16_t degrees);
void moveForward(uint16_t mm);
uint16_t mm2steps(uint16_t mm);
void setDirection(direction dir);
void goOneStep();








#endif