/*****************************************************
commands.c

Author  Martin Eriksson
Date    2015-03-10

Brief   Functions to handle the commands and setting next state for 
        the statemachine.

*****************************************************/

#include <string.h>
#include <stdlib.h>
#include "commands.h" 


//+++ returns true if string is a valid command +++
bool checkCommandString(char* str, state* nextState)
{
  
  //list of valid commands, (strcmp returns 0 if strings are equal).
  if      (strcmp(str, "forward") == 0)
  {
    *nextState = STATE_FORWARD;
    return true;
  }
  else if (strcmp(str, "right") == 0)
  {
    *nextState = STATE_RIGHT;
    return true;
  }
  else if (strcmp(str, "left") == 0)
  {
    *nextState = STATE_LEFT;
    return true;
  }
  else if (strcmp(str, "penup") == 0)
  {
    *nextState = STATE_PENUP;
    return true;
  }
  else if (strcmp(str, "pendown") == 0)
  {
    *nextState = STATE_PENDOWN;
    return true;
  }
 /* else if (strcmp(str, "repeat") == 0)
  {
    return true;
  }
  else if (strcmp(str, "to") == 0)
  {
    return true;
  }*/
  else
  {

    return false;
  }
}


//++++ separates the input into command and value ++++
void parseString(command* cmd)
{
  cmd->value = 0;
  char temp[MAX_CHARACTERS];
  char valueStr[MAX_CHARACTERS];

  bool str_done = false, val_done = false;
  uint16_t i, j, k;
  
  for(i = 0; i < MAX_CHARACTERS; i++)
  {
    temp[i] = '\0';
    valueStr[i] = '\0';
  }
  
  //go thru the string to find space
  for(i = 0; i < MAX_CHARACTERS; i++)
  {
    
    //if the string is saved as a command, get the value
    if(str_done)
    {
      //if any number, save it as the value of the command
      if (!val_done && (cmd->str[i] >= '0' && cmd->str[i] <= '9'))
      {
        valueStr[k] = cmd->str[i];
        k++;
      }else
      {
        val_done = true;
      }
    }
    
    
    if ((cmd->str[i] == ' ' || cmd->str[i] == '\r') && !str_done)
    {
      //copy first word to temp string
      for(j = 0; j < i ; j++)
      {
        temp[j] = cmd->str[j];
      }
      temp[i] = '\0';
      str_done = true;
    }
    

    
    
  }
  //save the value in the struct
  cmd->value = atoi(valueStr);
  
  //prints for testing
  
  
  strcpy(cmd->str, temp);
  //for(i=0; i<MAX_CHARACTERS; i++)
    //printf("ascii: %d: %c \n",cmd->str[i],cmd->str[i]);
}