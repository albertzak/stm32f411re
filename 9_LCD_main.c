#include "stm32f4xx.h"
#include "9_LCD.h"

// Ones, Tens, Hundreds, Thousands
int X, XX, XXX, XXXX;
int i;

void rcc_start() {
  RCC_AHB1PeriphClockCmd(LCD_RCCGPIO, ENABLE);
}

void gpio_start() {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Pin = LCD_E | LCD_RS | LCD_RW | LCD_D7 | LCD_D6 | LCD_D5 | LCD_D4;
  GPIO_Init(LCD_GPIO, &GPIO_InitStructure);
}

int main() {
  rcc_start();
  gpio_start();
  lcd_start();

  lcd_send_data('U');
  lcd_send_data('n');
  lcd_send_data('i');
  lcd_send_data('c');
  lcd_send_data('o');
  lcd_send_data('r');
  lcd_send_data('n');

  while(1) {

    X = i - (i/10) * 10; // Ones
    XX = (i - (i/100) * 100 - X) / 10; // Tens
    XXX = (i - (i/1000) * 1000 - X - XX) / 100; // Hundreds
    XXXX = (i - X - XX - XXX) / 1000; // Thousands

    lcd_cursorpos(1, 2);
    lcd_send_data(0x30 + XXXX);
    lcd_send_data(0x30 + XXX);
    lcd_send_data(0x30 + XX);
    lcd_send_data(0x30 + X);

    i++;

    if (i > 9999) i = 0;
  };
}
