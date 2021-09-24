/*
 * blinkLED.c
 *
 * Created: 2015-02-19 10:21:43 PM
 *  Author: Meysam Parvizi
 */ 

/* Blinker Demo */

// ------- Preamble -------- //

#define F_CPU 8000000UL

#include <avr/io.h>				/* Defines pins, ports, etc */
#include <util/delay.h>			/* Functions to waste time */


int main(void)
{
	// -------- Inits --------- //
	DDRC |= (1 << DDRC0);			/* Data Direction Register C: writing a one to the bit enables output. */
	
	// ------ Event loop ------ //
	while (1)
	{
		PORTC = 0b00000001;			/* Turn on first LED bit/pin in PORTC */
		_delay_ms(1000);			/* wait */
		
		PORTC = 0b00000000;			/* Turn off all C pins, including LED */
		_delay_ms(1000);			/* wait */
		
	} /* End event loop */
	
	return 0;						/* This line is never reached */
}