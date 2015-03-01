#include "commands.h"
#include "main.h"
#include "USART.h"
#include "servoControl.h"
#include "stepMotorControl.h"
#include "stateMachine.h"
#include "turtleUtility.h"
#include <stdbool.h>
#include <stdio.h>

//#define TEST_COMMANDS
//#define TEST_SERVO_CONTROL
//#define TEST_STEP_MOTOR_CONTROL




int main()
{
  initSystemTimer();
  initUSART();
  initPWM();
  initStepMotor();
  
  USART3PrintString("*** WELCOME TO TURTLE COMMANDS ***\r\n\n");
  command cmd;

//##############################################################################
#ifdef TEST_COMMANDS
  
  //setting commandstring to null
  for(uint8_t i = 0; i < MAX_CHARACTERS ; i++)
  {
    cmd.str[i] = '\0';
  }
  
  printf("Testing commands:\n");
  
  printf("forward: %d\n", checkCommandString("forward"));
  printf("right: %d\n", checkCommandString("right"));
  printf("left: %d\n", checkCommandString("left"));
  printf("penup: %d\n", checkCommandString("penup"));
  printf("pendown: %d\n", checkCommandString("pendown"));
  printf("repeat: %d\n", checkCommandString("repeat"));
  printf("to: %d\n", checkCommandString("to"));
  
  strcpy(cmd.str,"forward 200");
  cmd.value = 100;
  
  parseString(&cmd);
  printf("command: %s %d\n", cmd.str, cmd.value);
  printf("%s\n", checkCommandString(cmd.str)? "valid command" : "invalid command");

#endif //TEST_COMMANDS
//##############################################################################

//##############################################################################
#ifdef TEST_SERVO_CONTROL
   printf("Testing servo control:\n");
   penUp();
   printf("Pen up: 5 percent duty cycle\n");
   penDown();
   printf("Pen down: 3 percent duty cycle\n");
#endif //TEST_SERVO_CONTROL
//##############################################################################   
   
//##############################################################################
#ifdef TEST_STEP_MOTOR_CONTROL
   
#endif //TEST_STEP_MOTOR_CONTROL
//##############################################################################

 
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
      printf("going forward %d mm\n", cmd.value);
      moveForward(cmd.value);
      nextState = STATE_WAIT_FOR_COMMAND;
      break;
      
    case STATE_RIGHT:
      printf("turning right %d degrees\n", cmd.value);
      turnRightDegrees(cmd.value);
      nextState = STATE_WAIT_FOR_COMMAND;
      break;
      
    case STATE_LEFT:
      printf("turning left %d degrees\n", cmd.value);
      turnLeftDegrees(cmd.value);
      nextState = STATE_WAIT_FOR_COMMAND;
      break;
      
    case STATE_PENUP:
      printf("pen is now up, drawing disabled!\n");
      penUp();
      nextState = STATE_WAIT_FOR_COMMAND;
      break;
      
    case STATE_PENDOWN:
      printf("pen is now down, ready to draw\n");
      penDown();
      nextState = STATE_WAIT_FOR_COMMAND;
      break;
    default:
      printf("ERROR: %d\n", currentState);
      nextState = STATE_WAIT_FOR_COMMAND;
    }
    
  }
}
