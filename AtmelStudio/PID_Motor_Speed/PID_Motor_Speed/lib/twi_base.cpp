/*
 * twi_base.cpp
 *
 * Created: 03/15/2016 10:29:21
 * Author: Meysam Parvizi
 * Based on "Make: AVR Programming" by by Elliot Williams, Chapter 17. I2C
 */ 

#include "twi_base.h"

void twi_init(unsigned long frequency)
{
	TWSR = 0;
	// I2C_frequency = F_CPU / (16 + 2 * TWBR * 4^TWPS)
	TWBR =  ((F_CPU / frequency) - 16) / 2; // set I2C frequency
	TWCR |= (1 << TWEN); // enable
}

void twi_wait_for_complete(void)
{
	while (!(TWCR & (1<<TWINT)));
}

unsigned char twi_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	twi_wait_for_complete();
	return twi_status();
}

void twi_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

unsigned char twi_read_byte_ack(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	twi_wait_for_complete();
	return (TWDR);
}

unsigned char twi_read_byte_no_ack(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	twi_wait_for_complete();
	return (TWDR);
}

unsigned char twi_write_byte(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN); // init and enable
	twi_wait_for_complete();
	return twi_status();
}

unsigned char twi_status(void)
{
	return TW_STATUS;
}

