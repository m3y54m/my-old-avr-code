
/*
* charLCD.c
*
* Created: 2015-02-20 12:06:51 PM
*  Author: Administrator
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"

//Strings stored in AVR Flash memory
const char lcd_welcome_line_one[] PROGMEM = "AVR LCD DEMO";
const char lcd_progress[] PROGMEM = "Loading...";
const char lcd_animation[] PROGMEM = " LCD animation";

// additional custom LCD characters
const char backslash[8] PROGMEM =
{
	0b00000000,//back slash
	0b00010000,
	0b00001000,
	0b00000100,
	0b00000010,
	0b00000001,
	0b00000000,
	0b00000000
};

//delay 1s
void delay_1s(void)
{
	uint8_t i;
	for (i = 0; i<100; i++)
	{
		_delay_ms(10);
	}
}

//demonstration of progress bar
void progress(void)
{
	lcd_clear();
	lcd_puts(lcd_welcome_line_one, 3, 0);
	delay_1s();
	lcd_clear();
	lcd_puts(lcd_progress, 3, 0);
	for (uint8_t i = 0; i<255; i++)
	{
		_delay_ms(10);
		lcd_gotoxy(0, 1);
		lcd_progressBar(i, 255, 16);
	}
}

//demonstration of animation
void demo_animation(void)
{
	lcd_clear();
	lcd_defineChar(backslash, 0);
	lcd_puts(lcd_animation, 0, 0);
	for (uint8_t i = 0; i<3; i++)
	{
		lcd_gotoxy(8, 1);
		lcd_sendChar(0);
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_sendChar('-');
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_sendChar('/');
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_sendChar('|');
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_sendChar(8);//backslash
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_sendChar('-');
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_sendChar('/');
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_sendChar('|');
		delay_1s();
	}
}

int main(void)
{
	lcd_init();			//init LCD bit, dual line, cursor right
	lcd_clear();		//clears LCD
	while (1)			//loop demos
	{
		//progress();
		//delay_1s();
		//demo_animation();
		lcd_puts(lcd_animation,0,0);
		delay_1s();
	}
	return 0;
}
