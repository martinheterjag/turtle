/**************************************************************
Author: Martin Eriksson
Date:   2015-03-10

Brief:  Main program for turtle robot project, made for a programming
        course with focus on embedded systems at KTH

        The program takes commands from USART port and draws figures from
        the commands entered. Usable commands:

        -forward <MILLIMETERS>          Moves given distance forward
        -left <DEGREES>                 Turns given angle to the left
        -right <DEGREES>                Turns given angle to the right
        -penup                          Raises pen from the paper
        -pendown                        Put pen to the paper

        
**************************************************************/

#include "commands.h"
#include "main.h"
#include "USART.h"
#include "servoControl.h"
#include "stepMotorControl.h"
#include "stateMachine.h"
#include "turtleUtility.h"


int main()
{
  initSystemTimer();
  initUSART();
  initPWM();
  initStepMotor();
  
  USART3PrintString("*** WELCOME TO TURTLE COMMANDS ***\r\n\n");
  command cmd;
 
  //setting commandstring to null
  for(uint8_t i = 0; i < MAX_CHARACTERS ; i++)
  {
    cmd.str[i] = '\0';
  }
  
  // variables for state machine
  state currentState, nextState;
  nextState = STATE_WAIT_FOR_COMMAND;
  while (1)
  {
    currentState = nextState;
    
    switch(currentState)
    {
    case STATE_WAIT_FOR_COMMAND:
      nextState = checkUSART3Input(&cmd);
      break;
      
    case STATE_FORWARD:
      USART3PrintString("going forward\n\r");
      moveForward(cmd.value);
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("done going forward\n\r");
      break;
      
    case STATE_RIGHT:
      USART3PrintString("Turning right\n\r");
      turnRightDegrees(cmd.value);
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("done turning right\n\r");
      break;
      
    case STATE_LEFT:
      USART3PrintString("Turning left\n\r");
      turnLeftDegrees(cmd.value);
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("done turning left\n\r");
      break;
      
    case STATE_PENUP:
      penUp();
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("pen is now up\n\r");
      break;
      
    case STATE_PENDOWN:
      penDown();
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("pen is now down\n\r");
      break;
    default:
      USART3PrintString("ERROR!!!\n\r");
      nextState = STATE_WAIT_FOR_COMMAND;
    }
    
  }
}
