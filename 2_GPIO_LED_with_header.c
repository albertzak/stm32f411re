#include <stm32f4xx.h>

int i;

int main() {

  // Step 1:
  // Enable Clock for GPIO A via Reset & Clock Control (RCC)
  // GPIO A is part of Advanced Hyper Bus 1 (AHB)

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // Step 2:
  // Set Pin5 of GPIOA as output
  // All pins are inputs by default
  // to avoid bus collisions when powering up
  // Set GPIO Mode Register for port A Pin 5,
  // which is at Bit 11 and Bit 10 to 01 (Output)
  // Bit 11 is 0 by default, so it's enough to modify Bit 10

  GPIOA->MODER |= (1<<10);

  // Step 2.5:
  // GPIO State is "Push-Pull" by default
  // Output speed doesn't matter either
  // No need to change anyhting here

  // Step 3:
  // Write "1" to output data register GPIOA_ODR Bit 5 to 1
  // Or use Bit Set/Reset Register (which are read-only!)

  GPIOA->BSRR = GPIO_BSRR_BS_5;


  // Keep uC running indefinitely
  while(1) {
    // Sleep
    for(i = 0; i < 500000; i++);

    // XOR Output Data Register with 1,
    // this toggles the LED
    GPIOA->ODR ^= GPIO_ODR_ODR_5;
  }

}
