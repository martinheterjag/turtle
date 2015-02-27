#include "commands.h"
#include "main.h"
#include "USART.h"
#include "servoControl.h"
#include "turtleUtility.h"
#include <stdbool.h>
#include <stdio.h>

//#define TEST_COMMANDS
//#define TEST_SERVO_CONTROL



int main()
{
  initUSART();
  USART3PrintString("*** WELCOME TO TURTLE COMMANDS ***\r\n\n");
  command cmd;
  
  initPWM();

  initSystemTimer();
  
  
  
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


#ifdef TEST_SERVO_CONTROL
   printf("Testing servo control:\n");
   penUp();
   printf("Pen up: 5 percent duty cycle\n");
   penDown();
   printf("Pen down: 3 percent duty cycle\n");
#endif //TEST_SERVO_CONTROL
   
   
  //setting commandstring to null
  for(uint8_t i = 0; i < MAX_CHARACTERS ; i++)
  {
    cmd.str[i] = '\0';
  }
  
  
  while (1)
  {
    checkUSART3Input(&cmd);
  }
}
