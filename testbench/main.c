#include "commands.h"
#include "main.h"
#include "USART.h"
#include "servoControl.h"
#include "stepMotorControl.h"
#include "stateMachine.h"
#include "turtleUtility.h"
#include <stdbool.h>
#include <stdio.h>

#define TEST_COMMANDS
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
  state test = STATE_FORWARD;
  /*printf("Testing commands:\n");
  
  printf("forward: %d\n", checkCommandString("forward",&test));
  printf("right: %d\n", checkCommandString("right",&test));
  printf("left: %d\n", checkCommandString("left",&test));
  printf("penup: %d\n", checkCommandString("penup",&test));
  printf("pendown: %d\n", checkCommandString("pendown",&test));
  printf("repeat: %d\n", checkCommandString("repeat",&test));
  printf("to: %d\n", checkCommandString("to",&test));
  */
  strcpy(cmd.str,"forward 200 20 20 ");
  cmd.value = 100;
  
  parseString(&cmd);
  printf("command: %s %d\n", cmd.str, cmd.value);
  printf("%s\n", checkCommandString(cmd.str,&test)? "valid command" : "invalid command");

  strcpy(cmd.str,"right 200");
  cmd.value = 100;
  
  parseString(&cmd);
  printf("command: %s %d\n", cmd.str, cmd.value);
  printf("%s\n", checkCommandString(cmd.str,&test)? "valid command" : "invalid command");
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
      USART3PrintString("going forward\n");
      moveForward(cmd.value);
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("done going forward\n");
      break;
      
    case STATE_RIGHT:
      
      turnRightDegrees(cmd.value);
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("done turning right\n");
      break;
      
    case STATE_LEFT:
      //printf("turning left %d degrees\n", cmd.value);
      turnLeftDegrees(cmd.value);
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("done turning left\n");
      break;
      
    case STATE_PENUP:
      //printf("pen is now up, drawing disabled!\n");
      penUp();
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("pen is now up\n");
      break;
      
    case STATE_PENDOWN:
      //printf("pen is now down, ready to draw\n");
      penDown();
      nextState = STATE_WAIT_FOR_COMMAND;
      USART3PrintString("pen is now down\n");
      break;
    default:
      USART3PrintString("ERROR!!!\n");
      nextState = STATE_WAIT_FOR_COMMAND;
    }
    
  }
}
