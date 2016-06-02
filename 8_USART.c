#include "stm32f4xx.h"

int main() {
  // Enable clock for USART2 and GPIOA via RCC
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  // Initialize GPIO
  GPIO_InitTypeDef GPIOInit;
  GPIOInit.GPIO_Mode = GPIO_Mode_AF;
  GPIOInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIOInit.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;

  GPIO_Init(GPIOA, &GPIOInit);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

  // Initialize USART
  USART_InitTypeDef USARTInit;
  USARTInit.USART_BaudRate = 9600;
  USARTInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USARTInit.USART_WordLength = USART_WordLength_8b;
  USARTInit.USART_Parity = USART_Parity_No;
  USARTInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USARTInit.USART_StopBits = USART_StopBits_1;

  USART_Init(USART2, &USARTInit);
  USART_Cmd(USART2, ENABLE);

  // Enable receive interrupt
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  // Configure NVIC
  NVIC_InitTypeDef NVICInit;
  NVICInit.NVIC_IRQChannel = USART2_IRQn;
  NVICInit.NVIC_IRQChannelCmd = ENABLE;
  NVICInit.NVIC_IRQChannelPreemptionPriority = 0;
  NVICInit.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVICInit);

  for (int a = 65; a < 91; a++) {
    // Check if transmit buffer is empty
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);

    USART_SendData(USART2, a);
  }

  while(1);
}

void USART2_IRQHandler() {
  USART_ClearITPendingBit(USART2, USART_IT_RXNE);

  char rx;
  rx = (char) USART_ReceiveData(USART2);

  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);

  // Convert Uppercase to lowercase and vice-versa
  if (rx >= 'A' && rx <= 'Z') {
    USART_SendData(USART2, rx + 32);
  } else if (rx >= 'a' && rx <= 'z') {
    USART_SendData(USART2, rx - 32);
  }

}
