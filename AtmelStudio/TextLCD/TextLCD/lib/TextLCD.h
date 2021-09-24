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
#ifndef TEXT_LCD_H
#define TEXT_LCD_H

#include <inttypes.h>

#define LCD_RS	0 	//define MCU pin connected to LCD RS
#define LCD_RW	1 	//define MCU pin connected to LCD R/W
#define LCD_E	2	//define MCU pin connected to LCD E
#define LCD_D4	4	//define MCU pin connected to LCD D4
#define LCD_D5	5	//define MCU pin connected to LCD D5
#define LCD_D6	6	//define MCU pin connected to LCD D6
#define LCD_D7	7	//define MCU pin connected to LCD D7

#define LCD_DATA_PORT	PORTA		//define MCU port connected to LCD data pins
#define LCD_CTRL_PORT	PORTA		//define MCU port connected to LCD control pins
#define LCD_DATA_DIR	DDRA		//define MCU direction register for port connected to LCD data pins
#define LCD_CTRL_DIR	DDRA		//define MCU direction register for port connected to LCD control pins

#define LCD_CLR             0	//DB0: clear display
#define LCD_HOME            1	//DB1: return to home position
#define LCD_ENTRY_MODE      2	//DB2: set entry mode
#define LCD_ENTRY_INC       1	//DB1: increment
#define LCD_ENTRY_SHIFT     0	//DB2: shift
#define LCD_ON_CTRL         3	//DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY      2	//DB2: turn display on
#define LCD_ON_CURSOR       1	//DB1: turn cursor on
#define LCD_ON_BLINK        0	//DB0: blinking cursor
#define LCD_MOVE            4	//DB4: move cursor/display
#define LCD_MOVE_DISP       3	//DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT      2	//DB2: move right (0-> left)
#define LCD_FUNCTION        5	//DB5: function set
#define LCD_FUNCTION_8BIT   4	//DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3	//DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2	//DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM           6	//DB6: set CG RAM address
#define LCD_DDRAM           7	//DB7: set DD RAM address
// reading:
#define LCD_BUSY            7	//DB7: LCD is busy
#define LCD_LINES			2	//visible lines
#define LCD_LINE_LENGTH		16	//line length (in characters)

// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

// progress bar defines
#define PROGRESSPIXELS_PER_CHAR	6

void lcd_putchar(uint8_t ch);												//forms data ready to send to LCD
void lcd_cmd(uint8_t cmd);											//forms data ready to send to LCD
void lcd_init(void);													//Initializes LCD
void lcd_clear(void);													//Clears LCD
void lcd_home(void);													//LCD cursor home
void lcd_string(char *data, uint8_t nBytes);										//Outputs string to LCD
void lcd_gotoxy(uint8_t x, uint8_t y);										//Cursor to X Y position
void lcd_putsf(const char *flash_str, uint8_t x = 0, uint8_t y = 0);				//copies flash string to LCD at x,y
void lcd_puts(const char *str, uint8_t x = 0, uint8_t y = 0);				//copies string to LCD at x,y
void lcd_defineChar(const char *pc, uint8_t char_code);								//write char to LCD CGRAM
void lcd_shiftRight(uint8_t n);											//shift by n characters Right
void lcd_shiftLeft(uint8_t n);											//shift by n characters Left
void lcd_cursorOn(void);												//Underline cursor ON
void lcd_cursorOnBlink(void);											//Underline blinking cursor ON
void lcd_cursorOff(void);												//Cursor OFF
void lcd_blank(void);													//LCD blank but not cleared
void lcd_visible(void);													//LCD visible
void lcd_cursorLeft(uint8_t n);											//Shift cursor left by n
void lcd_cursorRight(uint8_t n);											//shif cursor right by n

// displays a horizontal progress bar at the current cursor location
// <progress> is the value the bargraph should indicate
// <maxprogress> is the value at the end of the bargraph
// <length> is the number of LCD characters that the bargraph should cover
//adapted from AVRLIB - displays progress only for 8 bit variables
void lcd_progressBar(uint8_t progress, uint8_t maxprogress, uint8_t length);


#endif
