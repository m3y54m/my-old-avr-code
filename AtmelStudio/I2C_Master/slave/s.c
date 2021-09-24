/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/12/2014
Author  : 
Company : 
Comments: 


Chip type               : ATmega32A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32a.h>

#include <delay.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
bit countStart=0;
signed char data=57;

// Standard Input/Output functions
#include <stdio.h>

// TWI Slave receive buffer
#define TWI_RX_BUFFER_SIZE 1
unsigned char twi_rx_buffer=0;

// TWI Slave transmit buffer
#define TWI_TX_BUFFER_SIZE 1
unsigned char twi_tx_buffer=0;

// TWI Slave 7-bit address
// Shaft Encoder 1
#define TWI_SLAVE_ADDR 0x01

bit twi_tx_flag=0;
bit twi_rx_flag=0;

interrupt [TWI] void twi_interrupt(void)
{
   unsigned char twi_status;
   #asm("wdr")
   
   if (0)
   {     
        //Switched to the not addressed Slave mode; own SLA will be recognized; GCA will be recognized if TWGCE = “1”
        TWDR=-128; //error: data not ready
        TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
   }
   else
   {
       twi_status=TWSR & 0xF8;
       //printf("%X\r\n",twi_status);
             
       switch (twi_status)
       {
          // Own SLA+W has been received; ACK has been returned
          case 0x60:
          // General call address has been received; ACK has been returned
          case 0x70:
             // Data byte will be received and ACK will be returned 
             TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
             break;
             
          // Previously addressed with own SLA+W; data has been received; ACK has been returned
          case 0x80:
          // Previously addressed with general call; data has been received; ACK has been returned
          case 0x90:
             // Data byte will be received and ACK will be returned
             twi_rx_buffer = TWDR;
             twi_rx_flag = 1; 
             TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
             //printf("Received=%d\r\n",twi_rx_buffer);
             break;
             
          // Own SLA+R has been received; ACK has been returned
          case 0xA8:
             switch (twi_rx_buffer)
             {
                 case 1:
                    twi_tx_buffer = data;
                    break;
             }
             
             // Load data byte
             TWDR = twi_tx_buffer;
             twi_tx_flag = 1;
             // Last data byte will be transmitted and NOT ACK should be received
             TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
             //printf("Transmitted=%d\r\n",twi_tx_buffer);
             break;
          
          // A STOP condition or repeated START condition has been received while still addressed as slave
          case 0xA0:
          // Data byte in TWDR has been transmitted; NOT ACK has been received
          case 0xC0:
          // Last data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received
          case 0xC8:
             //Switched to the not addressed Slave mode; own SLA will be recognized; GCA will be recognized if TWGCE = “1”
             TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
             break;
                
          // Data byte in TWDR has been transmitted; ACK has been received
          case 0xB8:
             // Last data byte will be transmitted and NOT ACK should be received
             TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
             break;         
       }
   }
}

void main(void)
{
// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 38400
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x0C;

// TWI initialization
// Mode: TWI Slave
// Match Any Slave Address: Off
// I2C Bus Slave Address: 0x01      
// TWGCE=1 means TWI module will respond to general call address (0x00)                          
TWAR=(TWI_SLAVE_ADDR<<1) | (0<<TWGCE);
// Enable TWI module in Slave mode and enable TWI interrupt    
TWCR=(1<<TWEA) | (1<<TWEN) | (1<<TWIE);

// Global enable interrupts
#asm("sei")

while (1);


}
