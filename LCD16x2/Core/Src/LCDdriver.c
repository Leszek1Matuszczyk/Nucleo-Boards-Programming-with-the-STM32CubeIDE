# include "main.h"

//Rise fall Edge On EN
void LCD_RF()
{
HAL_GPIO_WritePin(EN_GPIO_Port, EN_GPIO_Port, 1);
HAL_Delay(0.1);
HAL_GPIO_WritePin(EN_GPIO_Port, EN_GPIO_Port, 0);
HAL_Delay(0.1);
}

//Write Command to LCD

void LCD_cmd(unsigned char c)
{

	unsigned int d;
	d =c;
	d =(d << 4) & 0x0F00;
	GPIOA ->ODR = d;
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 0);
	LCD_RF();
	d =c;
	d =(d << 8) & 0x0F00;
	GPIOA ->ODR = d;
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 0);
	LCD_RF();
	HAL_Delay(0.1);

}

//Write data to LCD

void LCD_data(unsigned char c)
{

	unsigned int d;
	d=c;
	d =(d << 4) & 0x0F00;
	GPIOA ->ODR = d;
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
	LCD_RF();
	d =c;
	d =(d << 8) & 0x0F00;
	GPIOA ->ODR = d;
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
	LCD_RF();


}

//Clear LCD

void LCD_clear(void)
{

	LCD_cmd(0x1);
	HAL_Delay(5);

}

//Write String to LCD

void LCD_STR(const char * s)
{

	while(*s)
		LCD_data(*s++);

}

//Write Char to LCD

void LCD_char(char c)
{

	unsigned int d;
	d=c;
	d =(d << 4) & 0x0F00;
	GPIOA ->ODR = d;
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 1);
	LCD_RF();
	d =c;
	d =(d << 8) & 0x0F00;
	GPIOA ->ODR = d;
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 1);
	LCD_RF();

}

//Set Cursor on LCD

void LCD_cursor(int col, int row)
{

	char address;
	if (row ==0)address=0;
	if (row ==1)address=0x40;
	address += col-1;
	LCD_cmd(0x80 | address);


}

//Initialize the LCD

void LCD_init(void)
{

	GPIOA ->ODR =0;

	HAL_Delay(50);

	GPIOA -> ODR = 0x0300;
	LCD_RF();
	HAL_Delay(30);
	LCD_RF();
	HAL_Delay(30);
	LCD_RF();
	HAL_Delay(20);
	LCD_RF();
	HAL_Delay(20);
	GPIOA ->ODR = 0x0200;
	LCD_RF();
	HAL_Delay(5);
	LCD_cmd(0x28);
	HAL_Delay(5);
	LCD_cmd(0x0F);
	HAL_Delay(5);
	LCD_cmd(0x01);
	HAL_Delay(5);
	LCD_cmd(0x06);
	HAL_Delay(5);

}
