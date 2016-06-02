#include "stm32f4xx.h"

int main() {
  // GPIO
  GPIO_InitTypeDef GPIO_InitStructure;

  // Step 1: Configure RCC to enable GPIOA
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  // Step 2: Configure GPIOA Pin5 as Alternate Function (not output)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Define where the Alternate Function comes from
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);

  // Step 3: Configure Timer 2
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);
  TIM_TimeBaseInitStructure.TIM_Prescaler = 49999;
  TIM_TimeBaseInitStructure.TIM_Period = 1000;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

  // Configure output compare channel to generate PWM signal
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 200; // 1/2 of maximum period (1000)

  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_Cmd(TIM2, ENABLE);

  while(1);
}
