#include "stm32f4xx.h"

void EXTI15_10_IRQHandler() {
  TIM2->CCR1 += 100;

  // Don't forget to reset the Pending Bit
  EXTI_ClearITPendingBit(EXTI_Line13);
}

int main() {
  // GPIO
  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure RCC to enable GPIOA (LED)
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  // Configure GPIOA Pin5 as Alternate Function (not output)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Define where the Alternate Function comes from
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);

  // Confugure RCC to enable GPIOC (Button)
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  // Clock to Sysconfig
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  // Port C is the source for EXTI Line 13
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

  // Configure Timer 2
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);
  TIM_TimeBaseInitStructure.TIM_Prescaler = 49999;
  TIM_TimeBaseInitStructure.TIM_Period = 2000;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

  // Configure output compare channel to generate PWM signal
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 90; // 1/2 of maximum period (1000)

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_Cmd(TIM2, ENABLE);

  // Configure EXTI
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line13;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);

  // Configure NVIC
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

  NVIC_Init(&NVIC_InitStructure);

  while(1);
}
