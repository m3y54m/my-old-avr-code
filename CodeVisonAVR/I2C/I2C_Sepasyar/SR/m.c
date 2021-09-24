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
char data;

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
      
      //-------------- Initial Setting ---------------
      TWAR = address | (1<<TWGCE);        // Slave Address
      TWBR = 32;                          // Bit rate = 100Khz
      TWCR = 0xC4;                        // Clear Int, Set TWEA and TWEN
      while(TWCR & 0x80 == 0);            // Waiting for TWINT flag
      //--------- Transmit a Byte to Master ----------
      if(TWSR & 0xF8 == 0x60)             // SLA+W Received?
      {
            TWCR = 0xC4;                  // Clear Int, Set TWEA and TWEN
      }
      else
            twi_error((TWSR & 0xF8),0);
      //------------ Slave Receive a Byte ------------
      while(TWCR & 0x80 == 0);            // Waiting for TWINT flag
      twi_error((TWSR),11);
      if(TWSR & 0xF8 == 0x80)             // Slave has been Receive Byte?
      {
            data = TWDR;                  //Receive incoming data
            TWCR = 0x84;                  // Clear TWINT
      }
      else
            twi_error((TWSR & 0xF8),1);
      //---------- Receiving Stop Condition ----------
      while(TWCR & 0x80 == 0);            // Waiting for TWINT flag
      if ((TWSR & 0xF8) == 0xA0)          //Stop Condition Received?
      TWCR = 0x84;                        // Clear TWINT
      
      printf("%d",data);
      while(1);
}