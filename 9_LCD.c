#include "stm32f4xx.h"
#include "9_LCD.h"

void wait_ms(int time) {
  int i, j;
  for(i = 0; i < time; i++) {
    // 100 MHz = 10ns / cycle * 100k * 5 instructions = 1ms
    for(j = 0; j < 20000; j++);
  }
}

// Pulse the enable pin (LOW-HIGH-LOW)
void pulse_e() {
  wait_ms(1);
  GPIO_SetBits(LCD_GPIO, LCD_E);
  wait_ms(1);
  GPIO_ResetBits(LCD_GPIO, LCD_E);
  wait_ms(1);
}

// Send one byte as command to display,
// split in two parts for 4bit interface
void lcd_send_cmd(int cmd_value) {
  GPIO_ResetBits(LCD_GPIO, LCD_RS | LCD_RW);
  GPIO_ResetBits(LCD_GPIO, LCD_D7 | LCD_D6 | LCD_D5 | LCD_D4);

  // Send first half
  if (cmd_value & (1<<7)) GPIO_SetBits(LCD_GPIO, LCD_D7);
  if (cmd_value & (1<<6)) GPIO_SetBits(LCD_GPIO, LCD_D6);
  if (cmd_value & (1<<5)) GPIO_SetBits(LCD_GPIO, LCD_D5);
  if (cmd_value & (1<<4)) GPIO_SetBits(LCD_GPIO, LCD_D4);
  pulse_e();

  // Send second half
  GPIO_ResetBits(LCD_GPIO, LCD_D7 | LCD_D6 | LCD_D5 | LCD_D4);
  if (cmd_value & (1<<3)) GPIO_SetBits(LCD_GPIO, LCD_D7);
  if (cmd_value & (1<<2)) GPIO_SetBits(LCD_GPIO, LCD_D6);
  if (cmd_value & (1<<1)) GPIO_SetBits(LCD_GPIO, LCD_D5);
  if (cmd_value & (1<<0)) GPIO_SetBits(LCD_GPIO, LCD_D4);
  pulse_e();

}


// Send one byte as command to display,
// split in two parts for 4bit interface
void lcd_send_data(int data_value) {
  GPIO_SetBits(LCD_GPIO, LCD_RS);
  GPIO_ResetBits(LCD_GPIO, LCD_RW);
  GPIO_ResetBits(LCD_GPIO, LCD_D7 | LCD_D6 | LCD_D5 | LCD_D4);

  // Send first half
  if (data_value & (1<<7)) GPIO_SetBits(LCD_GPIO, LCD_D7);
  if (data_value & (1<<6)) GPIO_SetBits(LCD_GPIO, LCD_D6);
  if (data_value & (1<<5)) GPIO_SetBits(LCD_GPIO, LCD_D5);
  if (data_value & (1<<4)) GPIO_SetBits(LCD_GPIO, LCD_D4);
  pulse_e();

  // Send second half
  GPIO_ResetBits(LCD_GPIO, LCD_D7 | LCD_D6 | LCD_D5 | LCD_D4);
  if (data_value & (1<<3)) GPIO_SetBits(LCD_GPIO, LCD_D7);
  if (data_value & (1<<2)) GPIO_SetBits(LCD_GPIO, LCD_D6);
  if (data_value & (1<<1)) GPIO_SetBits(LCD_GPIO, LCD_D5);
  if (data_value & (1<<0)) GPIO_SetBits(LCD_GPIO, LCD_D4);
  pulse_e();

}

// Set cursor position
void lcd_cursorpos(int row, int col) {
  lcd_send_cmd(0x80 + row * 0x40 + col);
}

// Init Routine
// http://sprut.de/electronic/lcd/
// Pinout:
// RS RW - D7 D6 D5 D5 (D3 D2 D1 D0)
void lcd_start() {
  // Wait 15ms
  wait_ms(15);

  // Set interface to 8 Bits
  GPIO_ResetBits(LCD_GPIO, LCD_RS | LCD_RW | LCD_D7 | LCD_D6);
  GPIO_SetBits(LCD_GPIO, LCD_D5 | LCD_D4);
  pulse_e(); // 00-0011

  // Wait 4.1ms
  wait_ms(5);

  // Pulse again (Set interface to 8 Bits)
  pulse_e();

  // Wait 100us and pulse again
  wait_ms(1);
  pulse_e();

  // Set interface to 4 Bits
  GPIO_ResetBits(LCD_GPIO, LCD_D4);
  pulse_e(); // 00-0010

  // From now on, send bytes in two parts
  // First:  7 6 5 4
  // Second: 3 2 1 0

  // 2 lines, 5x8
  pulse_e(); // 00-0010....
  GPIO_ResetBits(LCD_GPIO, LCD_D5);
  GPIO_SetBits(LCD_GPIO, LCD_D7);
  pulse_e(); // + ....1000

  // Display off
  GPIO_ResetBits(LCD_GPIO, LCD_D7);
  pulse_e();

  GPIO_SetBits(LCD_GPIO, LCD_D7);
  pulse_e();

  // Clear
  GPIO_ResetBits(LCD_GPIO, LCD_D7);
  pulse_e();

  GPIO_SetBits(LCD_GPIO, LCD_D4);
  pulse_e();

  // Cursor right, no display shift
  GPIO_ResetBits(LCD_GPIO, LCD_D4);
  pulse_e();

  GPIO_SetBits(LCD_GPIO, LCD_D6 | LCD_D5);
  pulse_e();

  // Display on
  GPIO_ResetBits(LCD_GPIO, LCD_D6 | LCD_D5);
  pulse_e();

  // To enable cursor: Add LCD_D5 | LCD_D4
  GPIO_SetBits(LCD_GPIO, LCD_D7 | LCD_D6);
  pulse_e();
}
