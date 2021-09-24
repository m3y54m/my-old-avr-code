/*
 * TimersInterrupt.cpp
 *
 * Created: 03/16/2016 14:09:48
 *  Author: Administrator
 */ 


#define F_CPU 8000000UL

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "lib/Serial.h"

volatile uint8_t n;
volatile uint32_t s;

char str[32];

Serial serial;

ISR(TIMER1_OVF_vect)
{
	// Reinitialize Timer1 value
	TCNT1 = 0x63C0;
	
	n++;
	
	if (n == 200)
	{
		n=0;
		s++;
		sprintf(str,"%d\r\n",s);
		serial.write(str);
	}
	

}



int main(void)
{
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 1000.000 kHz
	// Mode: Normal top=0xFFFF
	// Timer Period: 10 ms
	// Timer1 Overflow Interrupt: On
	//TCCR1B = (1<<CS11);
	//TCNT1 = 0xD8F0;
	
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 8000.000 kHz
	// Mode: Normal top=0xFFFF
	// Timer Period: 5 ms
	// Timer1 Overflow Interrupt: On
	TCCR1B=(1<<CS10);
	TCNT1=0x63C0;
		
	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK = (1<<TOIE1);
	
	serial.init(250000, true, false);
	
	sei();

    while(1)
    {
        //TODO:: Please write your application code 
    }
}