/*
 * bitOperations.c
 *
 * Created: 2015-02-19 10:56:14 PM
 *  Author: Administrator
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BV(bit) (1 << bit)
#define setBit(byte, bit) (byte |= BV(bit))
#define clearBit(byte, bit) (byte &= ~BV(bit))
#define toggleBit(byte, bit) (byte ^= BV(bit))

int main(void)
{
	DDRC=0xff;
	PORTC=0b00000001;
	
    while(1)
    {
        PORTC=PORTC<<1;
		if (PORTC==0b01000000) PORTC=1;
		_delay_ms(1000);
		
    }
	
	return 0;
}