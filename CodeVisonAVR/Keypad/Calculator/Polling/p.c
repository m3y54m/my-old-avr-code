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

#define c0 PINA.7
#define c1 PINA.6
#define c2 PINA.5
#define c3 PINA.4
#define r0 PORTA.3
#define r1 PORTA.2
#define r2 PORTA.1
#define r3 PORTA.0

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
    }
}

unsigned int reverseNum(unsigned int num, unsigned char len)
{
    unsigned int s=0;
    char r=0;
    char i;
    unsigned int biggestTen=1;
    
    if (len==1) {
        return num;
    }
    else {
        for (i=1;i<len;i++) {
            biggestTen*=10;    
        }
        
        while (1) {
            r=num%10;
            num=num/10;
            s+=biggestTen*r;
            if (num==0) break;
            biggestTen/=10;
        }
        return s; 
    }   
}

void main(void)
{
// Declare your local variables here

// LCD module initialization
lcd_init(16);
lcd_clear();
lcd_gotoxy(0,0);
lcd_putchar('0');

while (1)
      {
      // Place your code here
      char str[16];
      signed char currentKey=-1;
      char i;
      static char x=0;
      static char y=0;
      static char step=0;
      char n;
      static unsigned int s=1;
      static char l=0;
      
      static float num1=0;
      static unsigned int num2=0;
      static float ans=0;
      static char op=4;
      
      for (i=0;i<=3;i++) {
          currentKey=columnTracer(i);
          if (currentKey!=-1) break;   
      }

      if (currentKey!=-1)
      {
          if (currentKey==12) {
              x=0;
              y=0;
              s=1;
              step=0;
              num1=0;
              num2=0;
              ans=0;
              l=0;
              op=0;
              lcd_clear();
              lcd_gotoxy(0,0);
              lcd_putchar('0');
          }
          else {  
              //Digits
              if (currentKey==0 || currentKey==1 || currentKey==2 ||
              currentKey==4 || currentKey==5 || currentKey==6 ||
              currentKey==8 || currentKey==9 || currentKey==10 || currentKey==13) {
              
                  switch (currentKey) {
                      case 13: n=0; break;
                      case 8:  n=1; break;
                      case 9:  n=2; break;
                      case 10: n=3; break;
                      case 4:  n=4; break;
                      case 5:  n=5; break;
                      case 6:  n=6; break;
                      case 0:  n=7; break;
                      case 1:  n=8; break;
                      case 2:  n=9; break;
                  }
                  
                  if (n!=0 || step==1 || step==3) {
                      if (step==0 || step==1) {
                          step=1;
                          l++; 
                          num1+=s*n;
                          s*=10;
                      }
                      if (step==2 || step==3) {
                      if (l==0) {
                         lcd_clear();
                         x=0;
                         y=0;
                      }
                          step=3;
                          l++; 
                          num2+=s*n;
                          s*=10;
                      }
                  }
                      
               }
               else if (currentKey==3 || currentKey==7 || currentKey==11 || currentKey==15) {
                  
                  lcd_gotoxy(15,1);
                  switch (currentKey) {
                      case 15: op=0; lcd_putchar('+'); break; // +
                      case 11: op=1; lcd_putchar('-'); break; // -
                      case 7:  op=2; lcd_putchar('x'); break; // *
                      case 3:  op=3; lcd_putchar('?'); break; // /
                  }
                  
                  if (step==0) {
                      step=2; 
                      num1=0;
                      s=1;
                      l=0;                        
                  }
                  
                  if (step==1) {
                      step=2; 
                      num1=reverseNum(num1,l);
                      s=1;
                      l=0;                                           
                  }
                  
                  if (step==3) {
                      num2=reverseNum(num2,l);
                      switch (op) {
                          case 0: ans=num1+num2; break;
                          case 1: ans=num1-num2; break;
                          case 2: ans=num1*num2; break;
                          case 3: ans=(float)num1/num2; break;
                      }
                      step=4; 
                      num1=ans;
                      num2=0;
                      s=1;
                      l=0;
                       
                  }
               }
               else if (currentKey==14) {
                  if (step==3) {
                      num2=reverseNum(num2,l);
                      switch (op) {
                          case 0: ans=num1+num2; break;
                          case 1: ans=num1-num2; break;
                          case 2: ans=num1*num2; break;
                          case 3: ans=(float)num1/num2; break;
                      }
                      step=4; 
                      num1=ans;
                      num2=0;
                      s=1;
                      l=0; 
                  }
               }
               
               if (x==16 && y==0) {x=0; y=1;}
               if (x==16 && y==1) {x=0; y=0; lcd_clear();}
               if (step==1) {
                  lcd_gotoxy(x,y);
                  lcd_putchar(Keys[currentKey]);
                  x++;
               }
               if (step==4) {
                  step=2;
                  lcd_clear();
                  x=0;
                  y=0;
                  lcd_gotoxy(x,y);
                  sprintf(str,"%.2f",ans);
                  lcd_puts(str);     
               }
               if (step==3) {
                  lcd_gotoxy(x,y);
                  lcd_putchar(Keys[currentKey]);
                  x++;
               }
               delay_ms(250);
          }  
      }
      }
}
