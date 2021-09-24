/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/5/2014
Author  : Meysam Parvizi
Company : Tabin
Comments: 


Chip type               : ATmega32A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32a.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>

#define XTAL 8000000UL

// 7bit slave I2C address
#define address 0xA0<<1
char data=0x77;

void twi_error(char status, char f)
{
      printf("ERROR %d - %X\r\n",f,status);
}

int c=0;
interrupt [TWI] void twi_interrupt(void) {
      c++;
      printf("%d\r\n",c);     
}

void main(void)
{
      // USART initialization
      // Communication Parameters: 8 Data, 1 Stop, No Parity
      // USART Receiver: On
      // USART Transmitter: On
      // USART Mode: Asynchronous
      // USART Baud Rate: 9600
      UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
      UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
      UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
      UBRRH=0x00;
      UBRRL=0x33;

      // Alphanumeric LCD initialization
      // Connections are specified in the
      // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
      // RS - PORTA Bit 0
      // RD - PORTA Bit 1
      // EN - PORTA Bit 2
      // D4 - PORTA Bit 4
      // D5 - PORTA Bit 5
      // D6 - PORTA Bit 6
      // D7 - PORTA Bit 7
      // Characters/line: 16
      lcd_init(16);
      
      //--- Start Condition and Transmitting SLA+W ----
      TWBR = 32;                    // Bit rate = 100Khz
      TWCR = 0xA4;                  // Transmit Start Condition

      while(TWCR & 0x80 == 0);      // Waiting for TWINT flag

      if(TWSR & 0xF8 == 0x08)       // Start Condition Transmitted?
      {
            TWDR = address | 0;     // SLA+W
            TWCR = 0x84;            // Enable TWI and Clear TWINT
      }
      else
            twi_error(TWSR & 0xF8,0);
      //--------------- Transmitting Data -------------
      while(TWCR & 0x80 == 0);      // Waiting for TWINT flag

      if(TWSR & 0xF8 == 0x18)       // SLA+W has been send with ACK?
      {
            TWDR = data;            // Loading data
            TWCR = 0x84;            // Enable TWI and Clear TWINT
      }
      else
            twi_error(TWSR & 0xF8,1);
      //--------- Transmitting Stop Condition ----------
      while(TWCR & 0x80 == 0);      // Waiting for TWINT flag

      if(TWSR & 0xF8 == 0x28)       // Data has been send with ACK?
      TWCR = 0x94;                  // Transmit Stop Condition
      //------------------------------------------------

      while(1);

}