#include "stm32f4xx.h"

int main() {

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

  while(1) {
    for(int i=0; i<10000000; i++);
    GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
  }
}
