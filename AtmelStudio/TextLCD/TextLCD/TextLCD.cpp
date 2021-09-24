/*
 * TextLCD.cpp
 *
 * Created: 03/17/2016 11:22:27
 *  Author: Administrator
 */ 


#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lib/Serial.h"
#include "lib/TextLCD.h"

// additional custom LCD characters ( 5x7 )
const char backslash[8] PROGMEM =
{
	0b00011111,//back slash
	0b00000000,
	0b00001010,
	0b00010001,
	0b00001110,
	0b00000000,
	0b00011111,
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
	lcd_puts("AVR LCD DEMO", 3, 0);
	delay_1s();
	lcd_clear();
	lcd_puts("Loading...", 3, 0);
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
	lcd_defineChar(backslash, 7);
	lcd_puts(" LCD animation", 0, 0);

		lcd_gotoxy(8, 1);
		lcd_putchar(7);
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_putchar(1);
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_putchar(2);
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_putchar(3);
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_putchar(4);
		delay_1s();
		lcd_gotoxy(8, 1);
		lcd_putchar(7);
		delay_1s();
	
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
		lcd_puts("Hello World!");
	}
	return 0;
}