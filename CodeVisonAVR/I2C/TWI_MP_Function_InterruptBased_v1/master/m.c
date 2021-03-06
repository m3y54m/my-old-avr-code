/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
? Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
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

// Standard Input/Output functions
#include <stdio.h>

// TWI Master receive buffer
unsigned char twi_rx_buffer[8];
unsigned char twi_rx_count;
unsigned char twi_rx_index;

// TWI Master transmit buffer
unsigned char twi_tx_buffer[8];
unsigned char twi_tx_count;
unsigned char twi_tx_index;

// TWI Slave 7-bit address
unsigned char twi_slave_addr;

bit twi_mode=0; // Master Transmitter:0 , Master Receiver:1

// TWI Master Transmitter or Receiver mode selection
#define TWI_WRITE 0
#define TWI_READ 1

bit twi_rx_complete=0;
bit twi_tx_complete=0;

void twi_init()
{
   // Prescaler=1
   TWSR=0;
   // Bit Rate=100 khz (if XTAL=8Mhz)                                    
   TWBR=32;
}

void twi_exchange(unsigned char slave_addr,unsigned char tx_count,unsigned char rx_count)
{
   if (tx_count!=0 || rx_count!=0)
   {
      twi_tx_index=0;
      twi_rx_index=0;
      twi_tx_count=tx_count;
      twi_rx_count=rx_count;
      twi_slave_addr=slave_addr;
      
      if (tx_count==0)
         twi_mode=1;
      else
         twi_mode=0; 
      
      // Send START condition and enable TWI interrupt
      TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
   }   
}


interrupt [TWI] void twi_interrupt(void)
{
   unsigned char twi_status;
   twi_status = TWSR & 0xF8;
   printf("  STATUS:%X-TWWC:%d-TR:%d\r\n",twi_status,(TWCR & (1<<TWWC))>>TWWC,twi_mode);
   // 10ms delay to complete the read or write operation
   //delay_ms(10);
   
   switch (twi_status)
   {  
      // A START condition has been transmitted
      case 0x08:
      // A repeated START condition has been transmitted
      case 0x10:
         if (twi_mode==0)
         {
            // SLA+W will be transmitted; ACK or NOT ACK will be received
            TWDR = (twi_slave_addr<<1) | TWI_WRITE;   
         }
         else // if (twi_mode==1)
         { 
            // SLA+R will be transmitted; ACK or NOT ACK will be received
            TWDR = (twi_slave_addr<<1) | TWI_READ;
         }
         TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
         break;
            
      // SLA+W has been transmitted; ACK has been received
      case 0x18:
         if (twi_tx_index<twi_tx_count)
         {
            // Data byte will be transmitted and ACK or NOT ACK will be received
            TWDR = twi_tx_buffer[twi_tx_index];
            twi_tx_index++;
            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
            
            if (twi_tx_index==twi_tx_count) 
               twi_tx_complete=1;
            printf("Transmitted=%d\r\n",twi_tx_buffer[twi_tx_index-1]);
         }
         break;
         
      // SLA+R has been transmitted; ACK has been received
      case 0x40:
         if (twi_rx_count==1)
         {
             // Data byte will be received and NOT ACK will be returned
            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
         }
         else // if (twi_rx_count>1)
         {
            // Data byte will be received and ACK will be returned
            TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
         }
         break;
         
      // Data byte has been received; ACK has been returned
      case 0x50:
         if (twi_rx_index<twi_rx_count-2)
         {
            // Data byte will be received and ACK will be returned
            twi_rx_buffer[twi_rx_index] = TWDR;
            TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
            twi_rx_index++;
            
            printf("Received=%d\r\n",twi_rx_buffer[twi_rx_index-1]);
         }
         else if (twi_rx_index==twi_rx_count-2)
         {
            // Data byte will be received and NOT ACK will be returned
            twi_rx_buffer[twi_rx_index] = TWDR;
            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
            twi_rx_index++;
            
            printf("DReceived=%d\r\n",twi_rx_buffer[twi_rx_index-1]);
         }
         break;
            
      // Data byte has been transmitted; ACK has been received
      case 0x28:
         if (twi_tx_index<twi_tx_count)
         {
            // Data byte will be transmitted and ACK or NOT ACK will be received
            TWDR = twi_tx_buffer[twi_tx_index];
            twi_tx_index++;
            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
            
            if (twi_tx_index==twi_tx_count) 
               twi_tx_complete=1;
            printf("Transmitted=%d\r\n",twi_tx_buffer[twi_tx_index-1]);
         }
         else if (twi_rx_count==0)
         {
            // STOP condition will be transmitted and TWSTO Flag will be reset
            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) | (1<<TWIE);
         }
         else if (twi_rx_count!=0)
         {
            // Without releasing control of the bus send a REPEATED START condition and prepare to go to Master Receiver mode
            TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
            twi_mode = 1;
         }
         break;
         
      // Data byte has been received; NOT ACK has been returned
      case 0x58:
         twi_rx_buffer[twi_rx_index] = TWDR;
         // STOP condition will be transmitted and TWSTO Flag will be reset
         TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) | (1<<TWIE);
         
         twi_rx_complete=1;
         printf("RReceived=%d\r\n",twi_rx_buffer[twi_rx_index]);
         break;
            
      // SLA+W has been transmitted; NOT ACK has been received
      case 0x20:         
      // Data byte has been transmitted; NOT ACK has been received   
      case 0x30:   
      // SLA+R has been transmitted; NOT ACK has been received
      case 0x48:
         // STOP condition will be transmitted and TWSTO Flag will be reset
         TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) | (1<<TWIE);
         break;     
   }
}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
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
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

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

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// Mode: TWI Master
twi_init();

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
   unsigned char str[16];
   
   twi_tx_buffer[0]++;
   twi_exchange(0x01,1,1);
   delay_ms(10);
   
   
   
   if (twi_tx_complete==1)
   {
      lcd_clear();
      twi_tx_complete=0;
      sprintf(str,"Transmitted=%d",twi_tx_buffer[0]);
      lcd_gotoxy(0,1);
      lcd_puts(str);  
   }
   if (twi_rx_complete==1) 
   {  
      twi_rx_complete=0;
      sprintf(str,"Received=%d",twi_rx_buffer[0]);
      lcd_gotoxy(0,0);
      lcd_puts(str);
   }


}

}
