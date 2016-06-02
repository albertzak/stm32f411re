#include "stm32f4xx.h"

int main() {
  // 1. Enable ADC1 via RCC
  RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC2EN, ENABLE);

  // 2. Enable GPIOC via RCC
  RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN, ENABLE);

  // 3. GPIOC Pin3 is an analog input
  GPIO_InitTypeDef GPIOInitStruct;
  GPIOInitStruct.GPIO_Mode = GPIO_Mode_AIN;
  GPIOInitStruct.GPIO_Pin = GPIO_Pin_3;
  GPIOInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIOInitStruct.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_Init(GPIOC, &GPIOInitStruct);

  // 4. Common ADC Config
  ADC_CommonInitTypeDef ADCCommonInitStruct;
  ADCCommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADCCommonInitStruct.ADC_Mode = ADC_Mode_Independent;
  ADCCommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div6;
  ADCCommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
  ADC_CommonInit(&ADCCommonInitStruct);

  // 5. ADC specific config
  ADC_InitTypeDef ADCInitStruct;
  ADCInitStruct.ADC_ContinuousConvMode = ENABLE; // 7. Continuous mode
  ADCInitStruct.ADC_DataAlign = ADC_DataAlign_Right;
  ADCInitStruct.ADC_NbrOfConversion = 1;
  ADCInitStruct.ADC_Resolution = ADC_Resolution_8b;
  ADC_Init(ADC1, &ADCInitStruct);

  // 6. Config regular ADC group for channel
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_15Cycles);

  // 7. Start ADC
  ADC_Cmd(ADC1, ENABLE);

  // 8. Kick off first conversion
  ADC_SoftwareStartConv(ADC1);

  while(1);
}
