/*
 * uart_base.c
 *
 * Created: 03/13/2016 17:44:02
 * Author: Meysam Parvizi
 * Based on "Interrupt UART library with receive/transmit circular buffers" by Peter Fleury <pfleury@gmx.ch>   http://jump.to/fleury
 */ 

#include "uart_base.h"

#include <avr/io.h>

void uart_init(unsigned long baud, bool enableTx, bool enableRx)
{
	unsigned int baudrate = F_CPU / (16UL * baud) - 1UL;
	
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	
	// Set Baud Rate:
	UBRRH = (unsigned char)(baudrate>>8);
	UBRRL = (unsigned char) baudrate;
	
	// Enable receiver or transmitter
	if (enableTx)
		UCSRB |= (1<<TXEN);
		
	if (enableRx)
		UCSRB |= (1<<RXEN);
}

void uart_putc(unsigned char data)
{
	// Wait for empty transmit buffer
	while ( !( UCSRA & (1<<UDRE)) );
	// Put data into buffer, sends the data
	UDR = data;
}

unsigned char uart_getc(void)
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
