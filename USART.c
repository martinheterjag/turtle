/*
Author: Martin Eriksson

Uses functions from: 
stm32f30x_gpio.c stm32f30x_misc.c 
stm32f30x_rcc.c stm32f30x_uart.c

needs function void USART3_IRQHandler(void) in stm32f30x_it.c
to handle the interrupt from USART Tx
  
USART.c for turtle project
KTH, course IS1300 Inbyggda System
*/
#include "USART.h"
#include <stdbool.h>
#include <stdlib.h>
#include "stm32f30x.h"
#include "stm32f3_discovery.h"



//local variables, used for usart interrupt;    
static volatile bool newData = false;
static volatile char recievedCommand[MAX_CHARACTERS];
static volatile uint8_t charCount = 0;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//      init USART on PD8(TX) and PD9(RX)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
void initUSART(void)
{
  // declare init-structs
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  // Enable USART3
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  
  // Enable clocking for port D
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
  
  
  // Connect pins to alternate function Tx och Rx
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_7);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_7);

  //PD8 USART3.TX => Alternative Function Output
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  //PD9 USART3.RX => Input
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  // USART communication defined
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART3, &USART_InitStructure);  
 
  // Settings for USART3 Interrupt, low priority
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
  
  // Enable USART3 Interrupt
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  
  // Enable USART
  USART_Cmd(USART3, ENABLE);
}


//++++ called from interrupt handler +++
void USART3InterruptEvent(void)
{
  uint8_t character = USART_ReceiveData(USART3);
  
  //won't take commands longer than MAX_CHARACTERS
  if(charCount <= MAX_CHARACTERS)
  {
    // Reads data from USART3 input register
    recievedCommand[charCount] = character; 
    charCount++;
    newData = true;
  }
  // If the buffer is full and there is a return character in the input register
  else if(character == '\r') 
  {
    recievedCommand[charCount-1] = character;
    newData = true;
  }   
}


//++++ sends a character on USART3 ++++
void USART3Print(uint8_t ch)
{ 
  while(!USART_GetFlagStatus(USART3,USART_FLAG_TXE)); 
  USART_SendData(USART3, ch);
}


//++++ sends a string on USART3 ++++
void USART3PrintString(volatile char* str)
{
  uint8_t len = strlen((char*)str);
  
  uint8_t i;
  for(i = 0; i < len; i++)
  {
    USART3Print(str[i]);
  }
  USART3Print('\n');
}


//++++ handles data if any new input data! ++++
void checkUSART3Input(command* cmd)
{
  //declare the command struct
  
  
  if(newData)
  {
    //if the last char was 'return'
    if(recievedCommand[charCount-1] == '\r')
    {
      //char str[MAX_CHARACTERS];
      
      //copy input to a temp string to work with.
      strcpy(cmd->str, (char*) recievedCommand);
      // reset the command input
      uint8_t i=0;
      for(i = 0; i< MAX_CHARACTERS; i++)
      {
        recievedCommand[i] = '\0';
      }
      charCount = 0;
      
      //parse string and compare it to list of commands
      parseString(cmd);
      
      // echo command
      USART3PrintString(strcat(cmd->str, " "));
      
      char temp[4] = 
        {(cmd->value/100 + '0'),
        (cmd->value/10)%10 + '0', 
        (cmd->value%100 + '0', 
        '\0')};
      USART3PrintString(strcat(temp, "\n\n\r"));
      
      
      //USART3PrintString("\n\r");
      
      
      if(checkCommandString(cmd->str))
      {
        USART3PrintString("valid command \n\r");
      }
      else
      {
        USART3PrintString("invalid command \n\r");
      }
      
    }
    newData = false;
  }
}
