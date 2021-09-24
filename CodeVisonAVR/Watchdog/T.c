/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 08/20/2015
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
#include <stdio.h>
#include <alcd.h>
int i=0;
void main(void)
{
// Watchdog Timer initialization
// Watchdog Timer Prescaler: OSC/32k
WDTCR=(0<<WDTOE) | (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);

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

while (1)
      {
      char str[16];
      unsigned long k=0;
      

      
      lcd_clear();
      sprintf(str,"%d",i);                
      lcd_puts(str);
      
      // make manual delay
      for(k=0;k<1000;k++)
      {
//        if(k==200000)
//        {
//            #asm("wdr")
//        }
      }
      // delay_ms automatically resets the wtachdog timer every 1ms by generating the wdr instruction. 
      //delay_ms(100);
      i++;
      }
}
