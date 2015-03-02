/*
stepMotorControl.c

author Martin Eriksson


Functions to control the step motors of the turtle.

connections:
pin 6   ---  Step1 (left motor)
pin 7   ---  dir1 (left motor)
pin 8   ---  MS1 (used to set step resolution)
pin 9   ---  MS2 (used to set step resolution)
pin 10  ---  step2 (right motor)
pin 11  ---  dir 2 (right motor)
pin 12  ---  Enable active low

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
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  
  
  // set to eigth step mode. (0x02)
  // step angle = 3.6 => 3.6/8 = 0.45 degrees per 1/8step
  GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET); 
  GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET);
  
  // turns of stepmotors as default.
  //stepMotorsEnable(false);
}


//***** turn right <arg> degrees ***** 
void turnRightDegrees(uint16_t degrees)
{
  stepMotorsEnable(true);
  setDirection(RIGHT);
  float mm = degrees * 1.047;

  //distance between the wheels 120 mm
  //circumference is 120*pi = 376.8 mm => 1.047 mm per degree
  for(int i = 0; i < mm2steps( (uint16_t) mm); i++)
  {
    goOneStep();
  }
  
  stepMotorsEnable(false);
}


//***** turn left <arg> degrees ***** 
void turnLeftDegrees(uint16_t degrees)
{
  stepMotorsEnable(true);
  setDirection(LEFT);
  float mm = degrees * 1.047;

  //distance between the wheels 120 mm
  //circumference is 120*pi = 376.8 mm => 1.047 mm per degree
  for(int i = 0; i < mm2steps( (uint16_t) mm); i++)
  {
    goOneStep();
  }
  
  stepMotorsEnable(false);
}


//***** Moves forward <arg> distance in mm *****
void moveForward(uint16_t mm)
{
  stepMotorsEnable(true);
  
  //setDirection(FORWARD);
  delay(100);
  GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET); 
  GPIO_WriteBit(GPIOC, GPIO_Pin_11, Bit_SET); 
  
  
  for(int i = 0; i < mm2steps(mm); i++)
  {
    goOneStep();
    
  }
  
  stepMotorsEnable(false);
}


//***** converts millimeter to steps *****
uint16_t mm2steps(uint16_t mm)
{
  //one step is 0.45 degrees
  //wheel diameter is 47 mm maths gives 0.18
  float step = 0.184475f;
    
  float stepsToMove = mm / step;
  
  //printf("steps to move: %f", stepsToMove);
  return(uint16_t)stepsToMove;
}


// ***** SETS DIRECTION OF THE MOTORS *****
//       move forward or turn left/right
void setDirection(direction dir)
{
  // recomended to wait 1/10 second before switching direction
  delay(100);
  
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
  //left motor
  GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
  //right motor
  GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_SET);
  delay(1);
  GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
  GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_RESET);
  delay(1);
}

//***** enable - reversed to be active high *****
void stepMotorsEnable(bool en)
{
  if(!en)
  {
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
  }
  if(en)
  {
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
  }
}