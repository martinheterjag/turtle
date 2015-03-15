/****************************************************
servoControl.c
Author  Martin Eriksson
Date    2015-03-10

Brief   Handles the PWM signal for the servo that controls if the pen
        is up or down.

****************************************************/

#include "servoControl.h"


//++++ init USART on PD8(TX) and PD9(RX) ++++
void initPWM(void)
{
  //---init output pin as pwm----
  
  // declare init-structs
  GPIO_InitTypeDef GPIO_InitStructure;
  
  // start port D Clock
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
  
  //PD8 USART3.TX => Alternative Function Output
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  // set alternate function to PWM
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_2);
  
  
  //---init pwm-timer!----
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  
  // enable timer clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
  
  // configure timer
  //50 Hz PWM with timer period of 1,000 => 50*1,000 = 50,000
  //system clock / 50,000 = 1440 => fits in timer counter!
  //prescaler = systemclock/50k = 0...1439.
  TIM_TimeBaseStructInit (& TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / 50000 - 1; // 0..1439
  TIM_TimeBaseStructure.TIM_Period = 1000 - 1; // 0..999
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4 , &TIM_TimeBaseStructure);
  
  // PWM1 Mode configuration: Channel 2
  // Edge -aligned; not single pulse mode
  TIM_OCStructInit (& TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OC2Init(TIM4 , &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_Cmd(TIM4 , ENABLE);
  
  // start with pen up.
  penUp();
  
}


void penUp(void)
{
//set pw to 5%
  TIM_SetCompare2(TIM4 , 50);
}

void penDown(void)
{
//set pw to 3%
  TIM_SetCompare2(TIM4 , 30);
}
