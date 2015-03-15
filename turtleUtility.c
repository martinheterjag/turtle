/*******************************************************************
turtleUtility.c

Author  Martin Eriksson
Date    2015-03-10

Brief   Utility functions for the turtle, at the moment there is only
        functionality for delays and timings.
*********************************************************************/

#include "turtleUtility.h"


// timer counter for delay
static __IO uint32_t TimingDelay;



// ***** starts the timer interrupts *****
void initSystemTimer(void)
{
  if(SysTick_Config( SystemCoreClock / 1000 ) )
  {
    while(1);
  }
}

// ***** Waits for nTime to decrese to 0.
void delay(__IO uint32_t n_ms)
{
  TimingDelay = n_ms;
  while(TimingDelay != 0);
}


// ***** timer interrupt calls this function.

void timingDelayDecrement(void)
{
  if (TimingDelay != 0)
  {
    TimingDelay--;
  }
}