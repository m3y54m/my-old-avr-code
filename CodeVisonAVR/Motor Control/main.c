/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2015-01-08
Author  : 
Company : 
Comments: 


Chip type               : ATmega8A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega8.h>
#include <delay.h>
// Standard Input/Output functions
#include <stdio.h>
// Alphanumeric LCD functions
#include <alcd.h>

#define c0 PIND.2
#define c1 PIND.3
#define c2 PIND.5
#define c3 PIND.6
#define r0 PORTD.7
#define r1 PORTC.0
#define r2 PORTC.1
#define r3 PORTC.2

#define PWM OCR1A
#define DIFF 20      // Precision of motor speed in RPM

// CHECK IF THE PRESSED KEY IS A DIGIT (0,1,2,3,4,5,6,7,8,9)
#define IS_DIGIT (currentKey==0 || currentKey==1 || currentKey==2 || currentKey==4 || currentKey==5 || currentKey==6 || currentKey==8 || currentKey==9 || currentKey==10 || currentKey==13)

//c0, c1, c2, and c3 must be pulled down by 10k-100k resistors

// Declare your global variables here
unsigned char Keys[16]={
'1','2','3','A',
'4','5','6','B',
'7','8','9','C',
'*','0','#','D'};

unsigned int encoder=0; // This variable counts number of TIMER0 OVERFLOWs
unsigned int pulse=0;   // This variable counts total number of encoder pulses

void init(void);
signed char keyFinder();
signed char columnTracer(char row);
unsigned int reverseNum(unsigned int num, unsigned char len);

// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)

// USART Receiver buffer
#define RX_BUFFER_SIZE 8
char rx_buffer[RX_BUFFER_SIZE];

#if RX_BUFFER_SIZE <= 256
unsigned char rx_wr_index=0,rx_rd_index=0;
#else
unsigned int rx_wr_index=0,rx_rd_index=0;
#endif

#if RX_BUFFER_SIZE < 256
unsigned char rx_counter=0;
#else
unsigned int rx_counter=0;
#endif

// This flag is set on USART Receiver buffer overflow
bit rx_buffer_overflow;

// USART Receiver interrupt service routine
interrupt [USART_RXC] void usart_rx_isr(void)
{
char status,data;
status=UCSRA;
data=UDR;
if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {
   rx_buffer[rx_wr_index++]=data;
#if RX_BUFFER_SIZE == 256
   // special case for receiver buffer size=256
   if (++rx_counter == 0) rx_buffer_overflow=1;
#else
   if (rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
   if (++rx_counter == RX_BUFFER_SIZE)
      {
      rx_counter=0;
      rx_buffer_overflow=1;
      }
#endif
   }
}

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART Receiver buffer
#define _ALTERNATE_GETCHAR_
#pragma used+
char getchar(void)
{
char data;
while (rx_counter==0);
data=rx_buffer[rx_rd_index++];
#if RX_BUFFER_SIZE != 256
if (rx_rd_index == RX_BUFFER_SIZE) rx_rd_index=0;
#endif
#asm("cli")
--rx_counter;
#asm("sei")
return data;
}
#pragma used-
#endif

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
   encoder++;           // Counts number of TIMER0 OVERFLOWs
   pulse=encoder*256;   // According to TIMER0's setting each OVERFLOW occurs when TCNT0 becomes 256, in other words when 256 pulses are produced by encoder         
}

void main(void)
{
// Declare your local variables here

init();  // Initialize microcontroller registers 

lcd_clear();
lcd_puts("INPUT: 0    RPM ");

while (1)
      {
      // Place your code here
      char str[16];
      signed char currentKey=-1;
      static char x=7;
      static char step=0;
      char n;
      static unsigned int s=1;
      static char l=0;
      static unsigned int rpm=0;
      static unsigned int rpmEncoder=0;
      static unsigned char k=0;
      
      currentKey=keyFinder();
      
      if (currentKey!=-1)
      {
          if (currentKey==12) {     // If '*' is pressed, all values are cleared 
              x=7;
              s=1;
              step=0;
              rpm=0;
              l=0;
              encoder=0;
              pulse=0;
              lcd_gotoxy(0,0);
              lcd_puts("INPUT: 0    RPM ");
          }
          else {  
              if (IS_DIGIT) {      // If any digit (0,1,2,3,4,5,6,7,8,9) is pressed
                   
                  switch (currentKey) {
                      case 13: n=0; break;
                      
                      case 8:  n=7; break;
                      case 9:  n=8; break;
                      case 10: n=9; break;
                      
                      case 4:  n=4; break;
                      case 5:  n=5; break;
                      case 6:  n=6; break;
                      
                      case 0:  n=1; break;
                      case 1:  n=2; break;
                      case 2:  n=3; break;
                  }
                  
                  if (n!=0 || step==1) {
                     if (step==3)
                     {
                        rpm=0;
                        lcd_gotoxy(0,0);
                        lcd_puts("INPUT: 0    RPM ");
                     }
                     step=1;
                     if (l<4)
                     {
                        l++;       // l is length of the input digit
                        rpm+=s*n;  
                        s*=10;     // s is 10 to the power of (l-1)
                     }
                  }                     
               }

               else if (currentKey==14)  // If '#' is pressed, control process starts
               {
                      step=2;
                      rpm=reverseNum(rpm,l);   // reverses the input number. for example 1673 => 3761 (because when you enter a number by keypad, you first enter the Most Significant Digit)
                      
                      // Limiting possible input numbers
                      if (rpm<=0) rpm=0;
                      if (rpm>=9999) rpm=9999;
                      
                      l=0;
                      s=1;
               }
               else if (currentKey==3 || currentKey==7 || currentKey==11 || currentKey==15)
               {
                      step=2;
                      switch (currentKey) {
                        case 3: rpm=rpm+100; break;
                        case 7: rpm=rpm+10; break;
                        case 11: rpm=rpm-10; break;
                        case 15: rpm=rpm-100; break;
                      }
                      
                      if (rpm<=0) rpm=0;
                      if (rpm>=9999) rpm=9999;
                      
                      l=0;
                      s=1;
               }
               
               
               if (step==1)
               {
                  if (x<11)
                  {
                     lcd_gotoxy(x,0);
                     lcd_putchar(Keys[currentKey]);
                     x++;
                  }
               }
               
               if (step==2)
               {
                  x=7;
                  if (rpm>=0 && rpm<2500) k=32;
                  if (rpm>=2500 && rpm<5000) k=64;
                  if (rpm>=5000 && rpm<7500) k=128;
                  if (rpm>=7500 && rpm<=9999) k=192;
                  step=3; 
               }
               
          delay_ms(200);      
          }  
      }
      
      if (step!=1)
      {
         sprintf(str,"INPUT: %-4d RPM ",rpm);
         lcd_gotoxy(0,0);
         lcd_puts(str);
            
         sprintf(str,"SPEED: %-4d RPM ",rpmEncoder);
         lcd_gotoxy(0,1);
         lcd_puts(str);
      }
         
         
      if (step==3)
      {
         PWM=k;
         
         /******* START TIMER0 TO READ ENCODER *******/
         // Timer/Counter 0 initialization
         // Clock source: T0 pin Rising Edge
         TCCR0=(1<<CS02) | (1<<CS01) | (1<<CS00);
         TCNT0=0x00;
         
         encoder=0;
         pulse=0;
         
         // Count number of pulses produced by encoder in 200 mili-seconds
         delay_ms(200); 
         
         // Total pulse is (pulse+TCNT0)
         // The encoder produces 45 pulses per revolution
         // Convert pulses per second to Revolutions per Minute
         rpmEncoder=(int)(((float)(pulse+TCNT0)*300)/45);
         
         /******* STOP TIMER0 *******/
         // Timer/Counter 0 initialization
         // Clock source: System Clock
         // Clock value: Timer 0 Stopped
         TCCR0=(0<<CS02) | (0<<CS01) | (0<<CS00);
         TCNT0=0x00;
         
         sprintf(str,"SPEED: %d RPM\r\n",rpmEncoder);
         puts(str);    // Send the motor speed (in rpm) to Serial Port
         
         sprintf(str,"CURRENT: %d mA\r\n", (int)((((float)read_adc(5)/1024)*5 + 0.3)*100));
         puts(str);    // Send the motor current (in mili-amperes) to Serial Port
         
         /******* CLOSED LOOP CONTROL *******/
         // Comparing our desired speed (INPUT / rpm) with real speed (OUTPUT / rpmEncoder)                                                
         if ((rpm-rpmEncoder < DIFF) || ( rpmEncoder-rpm < DIFF))
         {
             // Done 
         }
         else
         {
            if (rpm > rpmEncoder) 
            {
               if (k<255) k+=1;
            }
            else
            {
               if (k>0) k-=1;
            }
         }
         /******* CLOSED LOOP CONTROL *******/
      }
      
      }
}

signed char keyFinder()
{
      char i;
      signed char key=-1;
      
      for (i=0;i<=3;i++) {
          key=columnTracer(i);
          if (key!=-1) break;   
      }
      
      return key;
}

signed char columnTracer(char row)
{
    unsigned char delayTime=1;
    
    DDRC=0x0F;
    PORTC=0x00;
    
    //c0, c1, c2, and c3 must be pulled down by 10k-100k resistors
    
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

void init(void)
{
// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=Out Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (1<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=0 Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit6=In Bit5=In Bit4=In Bit3=In Bit2=Out Bit1=Out Bit0=Out 
DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit6=T Bit5=T Bit4=T Bit3=T Bit2=0 Bit1=0 Bit0=0 
PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=(0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Ph. correct PWM top=0x00FF
// OC1A output: Non-Inverted PWM
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 4.08 ms
// Output Pulse(s):
// OC1A Period: 4.08 ms Width: 0 us
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (1<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;


// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(1<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x33;

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);

// ADC initialization
// ADC Clock frequency: 125.000 kHz
// ADC Voltage Reference: AVCC pin
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ACME);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 2
// EN - PORTB Bit 3
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")
}