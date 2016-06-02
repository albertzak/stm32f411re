#include "stm32f4xx.h"

void TIM4_IRQHandler() {
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
  GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
}

int main() {
  // GPIO
  GPIO_InitTypeDef GPIO_InitStructure;

  // Step 1: Configure RCC to enable GPIOA
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  // Step 2: Configure GPIOA Pin5 as output
  // Config data has to be passed as struct
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_SetBits(GPIOA, GPIO_Pin_5);


  // TIMER

  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

  // Step 1: Configure RCC to enale Timer 4
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  // Step 2: Configure Timer 4

  // Prescaler: 50MHz -> 1 kHz
  TIM_TimeBaseInitStructure.TIM_Prescaler = 49999;

  // Period: 1kHz -> 1 Hz
  TIM_TimeBaseInitStructure.TIM_Period = 1000;

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

  TIM_Cmd(TIM4, ENABLE);

  // Allow TIM4 to send interrupt
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);


  // NVIC

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;

  NVIC_Init(&NVIC_InitStructure);

  while(1);
}
