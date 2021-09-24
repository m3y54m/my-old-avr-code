/*
 * UART.cpp
 *
 * Created: 03/13/2016 15:34:09
 * Author: Administrator
 */ 

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lib/Serial.h"

Serial serial;

int main(void)
{	
	char str[32];
	
	serial.init(9600, true, false);
	
	while(1)
	{
		sprintf(str,"Hello World!\r\n");
		serial.write(str);
		_delay_ms(100);
	}
		
    return 0;
}
