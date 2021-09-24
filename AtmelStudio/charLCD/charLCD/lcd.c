
//*****************************************************************************
//
// File Name	: 'lcd.h'
// Title		: 8 and 4 bit LCd interface + mixed pins modes
// Author		: Scienceprog.com - Copyright (C) 2007
// Created		: 2007-03-29
// Revised		: 2011-12-13
// Version		: 2.0
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#define F_CPU 8000000UL

#include "lcd.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

const char lcd_custom_char[] PROGMEM =//define 8 custom LCD chars
{
	0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, // 0. 0/5 full progress block
	0x00, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, // 1. 1/5 full progress block
	0x00, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x00, // 2. 2/5 full progress block
	0x00, 0x1F, 0x1C, 0x1C, 0x1C, 0x1C, 0x1F, 0x00, // 3. 3/5 full progress block
	0x00, 0x1F, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x00, // 4. 4/5 full progress block
	0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, // 5. 5/5 full progress block
	0x03, 0x07, 0x0F, 0x1F, 0x0F, 0x07, 0x03, 0x00, // 6. rewind arrow
	0x18, 0x1C, 0x1E, 0x1F, 0x1E, 0x1C, 0x18, 0x00  // 7. fast-forward arrow
};

void lcd_init(void)//Initializes LCD
{
	//4 bit part
	_delay_ms(15);
	//zero to data pins
	LCD_DATA_PORT &= ~(1 << LCD_D7 | 1 << LCD_D6 | 1 << LCD_D5 | 1 << LCD_D4);
	//zero to control pins
	LCD_CTRL_PORT &= ~(1 << LCD_E | 1 << LCD_RW | 1 << LCD_RS);
	LCD_DATA_DIR |= 1 << LCD_D7 | 1 << LCD_D6 | 1 << LCD_D5 | 1 << LCD_D4;
	LCD_CTRL_DIR |= 1 << LCD_E | 1 << LCD_RW | 1 << LCD_RS;
	//---------one------
	LCD_DATA_PORT = 0 << LCD_D7 | 0 << LCD_D6 | 1 << LCD_D5 | 1 << LCD_D4; //4 bit mode
	LCD_CTRL_PORT |= 1 << LCD_E | 0 << LCD_RW | 0 << LCD_RS;
	_delay_ms(1);
	LCD_CTRL_PORT &= ~(1 << LCD_E);
	_delay_ms(1);
	//-----------two-----------
	LCD_DATA_PORT = 0 << LCD_D7 | 0 << LCD_D6 | 1 << LCD_D5 | 1 << LCD_D4; //4 bit mode
	LCD_CTRL_PORT |= 1 << LCD_E | 0 << LCD_RW | 0 << LCD_RS;
	_delay_ms(1);
	LCD_CTRL_PORT &= ~(1 << LCD_E);
	_delay_ms(1);
	//-------three-------------
	LCD_DATA_PORT = 0 << LCD_D7 | 0 << LCD_D6 | 1 << LCD_D5 | 0 << LCD_D4; //4 bit mode
	LCD_CTRL_PORT |= 1 << LCD_E | 0 << LCD_RW | 0 << LCD_RS;
	_delay_ms(1);
	LCD_CTRL_PORT &= ~(1 << LCD_E);
	_delay_ms(1);
	//--------4 bit--dual line---------------
	lcd_sendCommand(0b00101000);
	//-----increment address, invisible cursor shift------
	lcd_sendCommand(0b00001100);

	//init 8 custom chars
	char ch = 0, chn = 0;
	while (ch<64)
	{
		lcd_defineChar((lcd_custom_char + ch), chn++);
		ch = ch + 8;
	}
}

void lcd_sendChar(uint8_t ch)		//Sends Char to LCD
{
	//4 bit part
	LCD_DATA_PORT = (ch & 0b11110000);
	LCD_CTRL_PORT |= 1 << LCD_RS;
	LCD_CTRL_PORT |= 1 << LCD_E;
	_delay_ms(1);
	LCD_CTRL_PORT &= ~(1 << LCD_E);
	LCD_CTRL_PORT &= ~(1 << LCD_RS);
	_delay_ms(1);
	LCD_DATA_PORT = ((ch & 0b00001111) << 4);
	LCD_CTRL_PORT |= 1 << LCD_RS;
	LCD_CTRL_PORT |= 1 << LCD_E;
	_delay_ms(1);
	LCD_CTRL_PORT &= ~(1 << LCD_E);
	LCD_CTRL_PORT &= ~(1 << LCD_RS);
	_delay_ms(1);
}
void lcd_sendCommand(uint8_t cmd)	//Sends Command to LCD
{
	//4 bit part
	LCD_DATA_PORT = (cmd & 0b11110000);
	LCD_CTRL_PORT |= 1 << LCD_E;
	_delay_ms(1);
	LCD_CTRL_PORT &= ~(1 << LCD_E);
	_delay_ms(1);
	LCD_DATA_PORT = ((cmd & 0b00001111) << 4);
	LCD_CTRL_PORT |= 1 << LCD_E;
	_delay_ms(1);
	LCD_CTRL_PORT &= ~(1 << LCD_E);
	_delay_ms(1);
}

void lcd_clear(void)				//Clears LCD
{
	lcd_sendCommand(1 << LCD_CLR);
}

void lcd_home(void)			//LCD cursor home
{
	lcd_sendCommand(1 << LCD_HOME);
}

void lcd_string(char *data, uint8_t nBytes)	//Outputs string to LCD
{
	register uint8_t i;

	// check to make sure we have a good pointer
	if (!data) return;

	// print data
	for (i = 0; i<nBytes; i++)
	{
		lcd_sendChar(data[i]);
	}
}
void lcd_gotoxy(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch (y)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR + x; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR + x; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR + x; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR + x; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR + x;
	}
	// set data address
	lcd_sendCommand(1 << LCD_DDRAM | DDRAMAddr);

}
//Copies string from flash memory to LCD at x y position
//const uint8_t welcomeln1[] PROGMEM="AVR LCD DEMO\0";
//CopyStringtoLCD(welcomeln1, 3, 1);	
void lcd_puts(const char *flash_str, uint8_t x, uint8_t y)
{
	uint8_t i;
	lcd_gotoxy(x, y);
	for (i = 0; (uint8_t)pgm_read_byte(&flash_str[i]); i++)
	{
		lcd_sendChar((uint8_t)pgm_read_byte(&flash_str[i]));
	}
}
//defines char symbol in CGRAM
/*
const uint8_t backslash[] PROGMEM=
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
LCDdefinechar(backslash,0);
*/
void lcd_defineChar(const char *pc, uint8_t char_code){
	uint8_t a, pcc;
	uint16_t i;
	a = (char_code << 3) | 0x40;
	for (i = 0; i<8; i++){
		pcc = pgm_read_byte(&pc[i]);
		lcd_sendCommand(a++);
		lcd_sendChar(pcc);
	}
}

void lcd_shiftLeft(uint8_t n)	//Scrol n of characters Right
{
	for (uint8_t i = 0; i<n; i++)
	{
		lcd_sendCommand(0x1E);
	}
}
void lcd_shiftRight(uint8_t n)	//Scrol n of characters Left
{
	for (uint8_t i = 0; i<n; i++)
	{
		lcd_sendCommand(0x18);
	}
}
void lcd_cursorOn(void) //displays LCD cursor
{
	lcd_sendCommand(0x0E);
}
void lcd_cursorOnBlink(void)	//displays LCD blinking cursor
{
	lcd_sendCommand(0x0F);
}
void lcd_cursorOff(void)	//turns OFF cursor
{
	lcd_sendCommand(0x0C);
}
void lcd_blank(void)		//blanks LCD
{
	lcd_sendCommand(0x08);
}
void lcd_visible(void)		//Shows LCD
{
	lcd_sendCommand(0x0C);
}
void lcd_cursorLeft(uint8_t n)	//Moves cursor by n poisitions left
{
	for (uint8_t i = 0; i<n; i++)
	{
		lcd_sendCommand(0x10);
	}
}
void lcd_cursorRight(uint8_t n)	//Moves cursor by n poisitions left
{
	for (uint8_t i = 0; i<n; i++)
	{
		lcd_sendCommand(0x14);
	}
}
//adapted fro mAVRLIB
void lcd_progressBar(uint8_t progress, uint8_t maxprogress, uint8_t length)
{
	uint8_t i;
	uint16_t pixelprogress;
	uint8_t c;

	// draw a progress bar displaying (progress / maxprogress)
	// starting from the current cursor position
	// with a total length of "length" characters
	// ***note, LCD chars 0-5 must be programmed as the bar characters
	// char 0 = empty ... char 5 = full

	// total pixel length of bargraph equals length*PROGRESSPIXELS_PER_CHAR;
	// pixel length of bar itself is
	pixelprogress = ((progress*(length*PROGRESSPIXELS_PER_CHAR)) / maxprogress);

	// print exactly "length" characters
	for (i = 0; i<length; i++)
	{
		// check if this is a full block, or partial or empty
		// (u16) cast is needed to avoid sign comparison warning
		if (((i*(uint16_t)PROGRESSPIXELS_PER_CHAR) + 5) > pixelprogress)
		{
			// this is a partial or empty block
			if (((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)) > pixelprogress)
			{
				// this is an empty block
				// use space character?
				c = 0;
			}
			else
			{
				// this is a partial block
				c = pixelprogress % PROGRESSPIXELS_PER_CHAR;
			}
		}
		else
		{
			// this is a full block
			c = 5;
		}

		// write character to display
		lcd_sendChar(c);
	}

}
