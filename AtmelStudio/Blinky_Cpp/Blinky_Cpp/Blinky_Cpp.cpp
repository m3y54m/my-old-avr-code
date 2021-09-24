/*
 * Blinky_Cpp.cpp
 *
 * Created: 03/13/2016 11:00:55
 * Author: Meysam Parvizi
 */ 

#define F_CPU 8000000UL			// CPU clock frequency needed for delay functions

#include <avr/io.h>				// Defines pins, ports, etc
#include <util/delay.h>			// Functions to waste time


int main(void)
{
	DDRC |= (1 << DDRC0);				// Data Direction Register C: writing a one to the bit enables output.
	
	// Event loop
	while (1)
	{
		PORTC ^= (1 << PORTC0);			// Toggle first LED bit/pin in PORTC
		_delay_ms(500);					// Wait for 1 second
	}
			
	return 0;							// This line is never reached
}