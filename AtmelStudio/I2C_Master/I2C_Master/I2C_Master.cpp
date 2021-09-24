/*
 * I2C_Master.cpp
 *
 * Created: 03/13/2016 12:15:59
 *  Author: Administrator
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lib/Serial.h"
#include "lib/I2C.h"

I2C i2c;
Serial serial;

int main(void)
{
	unsigned char addr = 0x01;
	signed char speed = 0;
	char str[32];
	
	serial.init(38400, true, false);
	i2c.init(400000);
	
    while(1)
    {
		const char command[] = { 0x01 };
		char response[] = { 0x00 };
		//i2c.start();
		//i2c.writeByte((addr<<1) | 0);
		//i2c.writeByte(1);
		//i2c.start();
		//i2c.writeByte((addr<<1) | 1);
		//speed = i2c.readByte(false);
		//i2c.stop();	
		i2c.write(addr, command, 1, true); 		//Send command & repeated start
		i2c.read(addr, response, 1, false);		//Read response
		speed = (signed char)response[0];	
		sprintf(str,"this is: %d\r\n",speed);
		serial.write(str);
		_delay_ms(100);
    }
}