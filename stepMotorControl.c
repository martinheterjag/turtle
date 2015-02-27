/*
stepMotorControl.c

author Martin Eriksson


Functions to control the step motors of the turtle.
*/

#include "stepMotorControl.h"
#include "turtleUtility.h"


//***** INITIALIZE THE STEP MOTOR CONTROL *****
void initStepMotor(void)
{
  // declare init-structs
  GPIO_InitTypeDef GPIO_InitStructure;
  
  // start port C Clock
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
  // enable PC6..12 as normal IO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  // set to eigth step mode. (0x02)
  // step angle = 3.6 => 3.6/8 = 0.45 degrees per 1/8step
  GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET); 
  GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET);
  
}


//***** turn right <arg> degrees ***** 
void turnRightDegrees(uint16_t degrees)
{
  setDirection(RIGHT);
  
  //distance between the wheels 120 mm
  //circumference is 120*pi = 376.8 mm => 1.047 mm per degree
  for(int i = 0; i < mm2steps(degrees * (uint16_t)1.047f); i++)
  {
    goOneStep();
  }
}


//***** turn left <arg> degrees ***** 
void turnLeftDegrees(uint16_t degrees)
{
  setDirection(LEFT);
  
  //distance between the wheels 120 mm
  //circumference is 120*pi = 376.8 mm => 1.047 mm per degree
  for(int i = 0; i < mm2steps(degrees * (uint16_t)1.047f); i++)
  {
    goOneStep();
  }
}


//***** Moves forward <arg> distance in mm *****
void moveForward(uint16_t mm)
{
  setDirection(FORWARD);
  for(int i = 0; i < mm2steps(mm); i++)
  {
    goOneStep();
  }
  
}

uint16_t mm2steps(uint16_t mm)
{
  //one step is 0.45 degrees
  //wheel diameter is 47 mm
  float circumference = 47.0 * 3.14; // 147.58
  float degree = circumference / 360.0; //0,4099444444...
  float step = degree * 0.45; // 0,184475
  
  uint16_t stepsToMove = mm * (uint16_t)step;
  return stepsToMove;
}


// ***** SETS DIRECTION OF THE MOTORS *****
//       move forward or turn left/right
void setDirection(direction dir)
{
  //pin7 left step motor pin11 right step motor
  switch(dir)
  {
  case FORWARD:
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET); 
    GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_SET); 
    break;
  case RIGHT:
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET); 
    GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_RESET); 
    break;
  case LEFT:
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET); 
    GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_SET); 
    break;
  }

}


//***** rotates both step motors one step *****
void goOneStep()
{
  delay(1);
  //left motor
  GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
  //right motor
  GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_SET);
  delay(1);
  GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
  GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_RESET);
}