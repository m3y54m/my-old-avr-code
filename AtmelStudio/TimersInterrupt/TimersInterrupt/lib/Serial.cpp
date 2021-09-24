/* 
* Serial.cpp
*
* Created: 03/13/2016 18:48:23
* Author: Meysam Parvizi
*/


#include "Serial.h"

// default constructor
Serial::Serial()
{
} //Serial

void Serial::init(uint32_t baud, bool enableTx, bool enableRx)
{
	uart_init(baud, enableTx, enableRx);
}

void Serial::_putc(uint8_t data)
{
	uart_putc(data);
}

uint8_t Serial::_getc()
{
	return uart_getc();
}

void Serial::write(const char *str)
{
	uart_puts(str);
}

// default destructor
Serial::~Serial()
{
} //~Serial
