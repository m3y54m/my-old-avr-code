/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : GY86 Module
Version : 4.0.0
Date    : 1393 Bahman 15
Author  : Meysam Parvizi
Company : 
Comments: 


Chip type               : ATmega16A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega16a.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
#include <string.h>
#include "MPU6050.h"
#include <math.h>

signed int GYRO_XOUT_OFFSET;
signed int GYRO_YOUT_OFFSET;
signed int GYRO_ZOUT_OFFSET;



float gyro_x(signed int gyro_x_offset)
{
   unsigned char BYTE_L;
   unsigned char BYTE_H;
   signed int GYRO_XOUT = 0;
   
   BYTE_L=MPU6050_read_reg(MPU6050_RA_GYRO_XOUT_L);
   BYTE_H=MPU6050_read_reg(MPU6050_RA_GYRO_XOUT_H);  
   GYRO_XOUT=((BYTE_H<<8)|BYTE_L)-gyro_x_offset;
   
   return -(float)GYRO_XOUT / 131;
}

float gyro_y(signed int gyro_y_offset)
{
   unsigned char BYTE_L;
   unsigned char BYTE_H;
   signed int GYRO_YOUT = 0;
   
   BYTE_L=MPU6050_read_reg(MPU6050_RA_GYRO_YOUT_L);
   BYTE_H=MPU6050_read_reg(MPU6050_RA_GYRO_YOUT_H);  
   GYRO_YOUT=((BYTE_H<<8)|BYTE_L)-gyro_y_offset;
   
   return -(float)GYRO_YOUT / 131;
}

float gyro_z(signed int gyro_z_offset)
{
   unsigned char BYTE_L;
   unsigned char BYTE_H;
   signed int GYRO_ZOUT = 0;
   
   BYTE_L=MPU6050_read_reg(MPU6050_RA_GYRO_ZOUT_L);
   BYTE_H=MPU6050_read_reg(MPU6050_RA_GYRO_ZOUT_H);  
   GYRO_ZOUT=((BYTE_H<<8)|BYTE_L)-gyro_z_offset;
   
   return -(float)GYRO_ZOUT / 141.5;
}

float accel_x(void)
{
   unsigned char BYTE_L;
   unsigned char BYTE_H;
   signed int ACCEL_XOUT = 0;
   
   BYTE_L=MPU6050_read_reg(MPU6050_RA_ACCEL_XOUT_L);
   BYTE_H=MPU6050_read_reg(MPU6050_RA_ACCEL_XOUT_H);  
   ACCEL_XOUT=((BYTE_H<<8)|BYTE_L);
   
   return -(float)ACCEL_XOUT / 16384;
}

float accel_y(void)
{
   unsigned char BYTE_L;
   unsigned char BYTE_H;
   signed int ACCEL_YOUT = 0;
   
   BYTE_L=MPU6050_read_reg(MPU6050_RA_ACCEL_YOUT_L);
   BYTE_H=MPU6050_read_reg(MPU6050_RA_ACCEL_YOUT_H);  
   ACCEL_YOUT=((BYTE_H<<8)|BYTE_L);
   
   return -(float)ACCEL_YOUT / 16384;
}

float accel_z(void)
{
   unsigned char BYTE_L;
   unsigned char BYTE_H;
   signed int ACCEL_ZOUT = 0;
   
   BYTE_L=MPU6050_read_reg(MPU6050_RA_ACCEL_ZOUT_L);
   BYTE_H=MPU6050_read_reg(MPU6050_RA_ACCEL_ZOUT_H);  
   ACCEL_ZOUT=((BYTE_H<<8)|BYTE_L);
   
   return -(float)ACCEL_ZOUT / 16384;
}

float theta_wz;
float theta_wy;
float theta_wx;

float theta_ax;
float theta_ay;
float theta_az;

float theta_x;
float theta_y;
float theta_z;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here 
   
   float wx,wy,wz;
   float ax,ay,az;
   static float theta_z_last=0;
   static float theta_y_last=0;
   static float theta_x_last=0;
   float k=0.8;
   
   
   #asm("cli")
   
   wz=gyro_z(GYRO_ZOUT_OFFSET);
   wy=gyro_y(GYRO_YOUT_OFFSET);
   wx=gyro_x(GYRO_XOUT_OFFSET);
   
   ax=accel_x();
   ay=accel_y();
   az=accel_z();
   
   theta_wz = theta_z_last + 0.032768*wz;
   theta_wy = theta_y_last - 0.032768*wx;
   theta_wx = theta_x_last + 0.032768*wy;
   
   //theta_az = atan2(az,sqrt(ax*ax+ay*ay)) * 180/PI;
   theta_ay = -atan2(ay,sqrt(ax*ax+az*az)) * 180/PI;
   theta_ax = -atan2(ax,sqrt(az*az+ay*ay)) * 180/PI;
    
   theta_z = theta_wz;
   // Complementary Filter
   theta_y = k*(theta_wy) + (1-k)*(theta_ay);
   theta_x = k*(theta_wx) + (1-k)*(theta_ax);
   
   theta_z_last = theta_z;
   theta_y_last = theta_y;
   theta_x_last = theta_x;
   
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
MPU6050_calibrate_gyro(&GYRO_XOUT_OFFSET,&GYRO_YOUT_OFFSET,&GYRO_ZOUT_OFFSET);

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
   sprintf(str,"%.1f|%.1f|%.1f",theta_x,theta_y,theta_z);
   l=strlen(str);
   lcd_gotoxy(0,0);
   lcd_puts(str);
   for(i=1;i<=(16-l);i++){lcd_puts(" ");}
}

}
