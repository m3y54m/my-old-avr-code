/*
 * ExternalInterrupt.cpp
 *
 * Created: 03/13/2016 12:29:51
 *  Author: Administrator
 */ 

#define F_CPU 8000000UL

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t n;

ISR(INT0_vect)
{
	n++;
}

int main(void)
{
	// External Interrupt(s) initialization
	// INT0: On
	// INT0 Mode: Rising Edge
	// INT1: Off
	// INT2: Off
	GICR |= (0<<INT1) | (1<<INT0) | (0<<INT2);
	MCUCR = (0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (1<<ISC00);
	MCUCSR = (0<<ISC2);
	GIFR = (0<<INTF1) | (1<<INTF0) | (0<<INTF2);
	
	// USART initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: Off
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud Rate: 9600
	UCSRA = (0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
	UCSRB = (0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
	UCSRC = (1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
	UBRRH = 0x00;
	UBRRL = 0x33;
	
	// Port A initialization
	// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
	DDRA = (1<<DDRA7) | (1<<DDRA6) | (1<<DDRA5) | (1<<DDRA4) | (1<<DDRA3) | (1<<DDRA2) | (1<<DDRA1) | (1<<DDRA0);
	
	// Global enable interrupts
	sei();
	
	while (1)
	{
		static uint8_t temp = 0;
	
		if (temp != n)
		{
			UDR = n;
			PORTA = n;
		}
				
		temp = n;
	}

}