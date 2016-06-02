#define LCD_E  GPIO_Pin_15
#define LCD_RS GPIO_Pin_13
#define LCD_RW GPIO_Pin_14

#define LCD_D7 GPIO_Pin_3
#define LCD_D6 GPIO_Pin_5
#define LCD_D5 GPIO_Pin_4
#define LCD_D4 GPIO_Pin_10

#define LCD_GPIO GPIOB
#define LCD_RCCGPIO RCC_AHB1Periph_GPIOB

void lcd_start(void);
void lcd_send_data(int data_value);
void lcd_cursorpos(int row, int col);
