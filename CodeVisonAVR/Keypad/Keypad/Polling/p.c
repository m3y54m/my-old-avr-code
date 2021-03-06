/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.9 Standard
Automatic Program Generator
? Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2014/08/01
Author  : MP
Company : TABIN
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>
#include <delay.h>
#include <stdio.h>

// Alphanumeric LCD Module functions
#asm
   .equ __lcd_port=0x1B ;PORTA
#endasm
#include <lcd.h>

#define c0 PINC.7
#define c1 PINC.6
#define c2 PINC.5
#define c3 PINC.4
#define r0 PORTC.3
#define r1 PORTC.2
#define r2 PORTC.1
#define r3 PORTC.0

// Declare your global variables here

unsigned char Keys[16]={
'7','8','9','/',
'4','5','6','*',
'1','2','3','-',
'C','0','=','+'};

signed char columnTracer(char row)
{
    unsigned char delayTime=1;
    
    DDRC=0x0F;
    PORTC=0x00;
    
    //PINC.7, PINC.6, PINC.5, and PINC.4 must be pulled down by 10k-100k resistors
    
    switch (row) {
    
    case 0:
    
        r0=1;
        r1=0;
        r2=0;
        r3=0;
        
        delay_ms(delayTime);
        
             if (c0==1) return 0;
        else if (c1==1) return 1;
        else if (c2==1) return 2;
        else if (c3==1) return 3;
        else return -1;
        
    break;
    
    case 1:
    
        r0=0;
        r1=1;
        r2=0;
        r3=0;
    
        delay_ms(delayTime);
        
             if (c0==1) return 4;
        else if (c1==1) return 5;
        else if (c2==1) return 6;
        else if (c3==1) return 7;
        else return -1;
        
    break;
    
    case 2:
    
        r0=0;
        r1=0;
        r2=1;
        r3=0;
        
        delay_ms(delayTime);
        
             if (c0==1) return 8;
        else if (c1==1) return 9;
        else if (c2==1) return 10;
        else if (c3==1) return 11;
        else return -1;
        
    break;
    
    case 3:
    
        r0=0;
        r1=0;
        r2=0;
        r3=1;
        
        delay_ms(delayTime);
        
             if (c0==1) return 12;
        else if (c1==1) return 13;
        else if (c2==1) return 14;
        else if (c3==1) return 15;
        else return -1;
        
    break;
    
    default:
        return -1;
    };
}

void main(void)
{
// Declare your local variables here

// LCD module initialization
lcd_init(16);

while (1)
      {
      // Place your code here
      signed char currentKey=-1;
      char i;
      static char x=0;
      static char y=0;
      
      for (i=0;i<=3;i++) {
          currentKey=columnTracer(i);
          if (currentKey!=-1) break;   
      };

      
      if (currentKey!=-1)
      {
          if (currentKey==12) {
              // Character by character clearing
              if (x==0 && y==0) {lcd_gotoxy(x,y); lcd_putchar('');}
              else if (x==0 && y==1) {x=15; y=0; lcd_gotoxy(x,y); lcd_putchar('');}
              else {x--; lcd_gotoxy(x,y); lcd_putchar('');}
              delay_ms(250);
              
              
              // Total clearing
              /*
              x=0;
              y=0;
              lcd_clear();
              */
          }
          
          else {  
              if (x==16 && y==0) {x=0; y=1;}
              if (x==16 && y==1) {x=0; y=0; lcd_clear();}
              lcd_gotoxy(x,y);
              lcd_putchar(Keys[currentKey]);
              x++;
              delay_ms(250);
          }
      }
      
      };
}
