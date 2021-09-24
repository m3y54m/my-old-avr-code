/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : GY86 Module
Version : 3.0.1
Date    : 1393 Bahman 15
Author  : Meysam Parvizi
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
#include <alcd.h>
#include <stdio.h>
#include <string.h>
#include "MPU6050.h"
//#include <math.h>

signed int GYRO_XOUT_OFFSET;
signed int GYRO_YOUT_OFFSET;
signed int GYRO_ZOUT_OFFSET;

unsigned char BYTE_L;
unsigned char BYTE_H;


float theta;
// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here 
   signed int GYRO_ZOUT = 0;
   float wz;
   static float theta_last=0;
   
   #asm("cli")
   
   BYTE_L=MPU6050_read_reg(MPU6050_RA_GYRO_ZOUT_L);
   BYTE_H=MPU6050_read_reg(MPU6050_RA_GYRO_ZOUT_H);  
   GYRO_ZOUT=((BYTE_H<<8)|BYTE_L)-GYRO_ZOUT_OFFSET;
   wz=-(float)GYRO_ZOUT / 141.5;
   
   theta = theta_last + 0.033728*wz;
   theta_last=theta;
   #asm("sei")
}


void main(void)
{
char str[16];
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

// TWI initialization
// Mode: TWI Master
initI2C();
MPU6050_init();
MPU6050_calibrate_gyro();

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 7.813 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
// Timer Period: 32.768 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

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

// Global enable interrupts
#asm("sei")

while (1)
{
   unsigned char l=0;
   unsigned char i=0;
   sprintf(str,"%.2f",theta);
   l=strlen(str);
   lcd_gotoxy(0,0);
   lcd_puts(str);
   for(i=1;i<=(16-l);i++){lcd_puts(" ");}
}

}
