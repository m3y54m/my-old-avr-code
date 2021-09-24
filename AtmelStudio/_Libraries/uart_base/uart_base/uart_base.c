/*
 * uart_base.c
 *
 * Created: 03/13/2016 17:44:02
 *  Author: Administrator
 */ 

#include "uart_base.h"

#include <avr/io.h>

void uart_init(unsigned int baud)
{
	/* Set baud rate */
	//UBRRH = (unsigned char)(baud>>8);
	//UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	//UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	//UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

void uart_putc(unsigned char data)
{
	// Wait for empty transmit buffer
	while ( !( UCSRA & (1<<UDRE)) );
	// Put data into buffer, sends the data
	UDR = data;
}

unsigned char uart_getc()
{
	// Wait for data to be received
	while ( !(UCSRA & (1<<RXC)) );
	// Get and return received data from buffer
	return UDR;
}


void uart_puts(const char *str) {
	while (*str)
		uart_putc(*str ++);
}
