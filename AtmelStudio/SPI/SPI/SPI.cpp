/*
 * SPI.cpp
 *
 * Created: 03/17/2016 15:22:08
 *  Author: Administrator
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lib/TextLCD.h"

#define SPI_PORT	PORTB
#define SPI_DDR		DDRB
#define SPI_MOSI	PORTB5
#define SPI_MISO	PORTB6
#define SPI_SCK		PORTB7
#define SPI_SS		PORTB4

void spi_init(void)
{
	SPI_DDR |= (1 << SPI_SS);		// set SS output
	SPI_PORT |= (1 << SPI_SS);		// start off not selected (high)
	SPI_DDR |= (1 << SPI_MOSI);		// output on MOSI
	SPI_PORT |= (1 << SPI_MISO);	// pullup on MISO
	SPI_DDR |= (1 << SPI_SCK);		// output on SCK
	
	SPCR |= (1 << MSTR);			// clockmaster
	SPCR |= (1 << SPE);				// enable
}

uint8_t spi_writeByte(uint8_t byte)
{
	SPDR = byte;							// SPI starts sending immediately
	while ( !( SPSR & (1<<SPIF)) );			// wait until done
	// SPDR now contains the received byte
	return SPDR;
}

void spi_write(const char *str)
{
	while (*str)
		spi_writeByte(*str++);
}

int main(void)
{
	spi_init();
	
	SPI_PORT &= ~(1 << SPI_SS);				// select slave (low)
	
	lcd_init();
    lcd_clear();
	
    while(1)
    {
      static unsigned char c=0;
      char str[16];
      spi_tradeByte(c);

      lcd_gotoxy(0,0);
      sprintf(str,"%d",c);
      lcd_puts(str);
      c++;
	  _delay_ms(100);
    }
}