#include "commands.h"
#include "main.h"
#include "USART.h"
#include <stdbool.h>
#include <stdio.h>


int main()
{
  initUSART();
  USART3PrintString("*** WELCOME TO TURTLE COMMANDS ***\r\n\n");
  command cmd;
  
  for(uint8_t i = 0; i < MAX_CHARACTERS ; i++)
  {
    cmd.str[i] = '\0';
  }
  
  
  while (1)
  {
    checkUSART3Input(&cmd);
  }
}
