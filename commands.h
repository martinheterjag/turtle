/*
author: Martin Eriksson.
Command list for turtle project.
*/

#ifndef __COMMANDS_H
#define __COMMANDS_H

//+++ includes +++
#include "stm32f30x_it.h"
#include <stdbool.h>

//+++ defines +++
#define MAX_CHARACTERS 128

//+++ structures +++
typedef struct 
{
  char str[MAX_CHARACTERS];
  int value;
}command;


//+++ functions +++
bool checkCommandString(char* command);
void parseString(command* cmd);

#endif