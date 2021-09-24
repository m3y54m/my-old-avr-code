
#pragma used+
sfrb TWBR=0;
sfrb TWSR=1;
sfrb TWAR=2;
sfrb TWDR=3;
sfrb ADCL=4;
sfrb ADCH=5;
sfrw ADCW=4;      
sfrb ADCSRA=6;
sfrb ADCSR=6;     
sfrb ADMUX=7;
sfrb ACSR=8;
sfrb UBRRL=9;
sfrb UCSRB=0xa;
sfrb UCSRA=0xb;
sfrb UDR=0xc;
sfrb SPCR=0xd;
sfrb SPSR=0xe;
sfrb SPDR=0xf;
sfrb PIND=0x10;
sfrb DDRD=0x11;
sfrb PORTD=0x12;
sfrb PINC=0x13;
sfrb DDRC=0x14;
sfrb PORTC=0x15;
sfrb PINB=0x16;
sfrb DDRB=0x17;
sfrb PORTB=0x18;
sfrb PINA=0x19;
sfrb DDRA=0x1a;
sfrb PORTA=0x1b;
sfrb EECR=0x1c;
sfrb EEDR=0x1d;
sfrb EEARL=0x1e;
sfrb EEARH=0x1f;
sfrw EEAR=0x1e;   
sfrb UBRRH=0x20;
sfrb UCSRC=0X20;
sfrb WDTCR=0x21;
sfrb ASSR=0x22;
sfrb OCR2=0x23;
sfrb TCNT2=0x24;
sfrb TCCR2=0x25;
sfrb ICR1L=0x26;
sfrb ICR1H=0x27;
sfrb OCR1BL=0x28;
sfrb OCR1BH=0x29;
sfrw OCR1B=0x28;  
sfrb OCR1AL=0x2a;
sfrb OCR1AH=0x2b;
sfrw OCR1A=0x2a;  
sfrb TCNT1L=0x2c;
sfrb TCNT1H=0x2d;
sfrw TCNT1=0x2c;  
sfrb TCCR1B=0x2e;
sfrb TCCR1A=0x2f;
sfrb SFIOR=0x30;
sfrb OSCCAL=0x31;
sfrb TCNT0=0x32;
sfrb TCCR0=0x33;
sfrb MCUCSR=0x34;
sfrb MCUCR=0x35;
sfrb TWCR=0x36;
sfrb SPMCR=0x37;
sfrb TIFR=0x38;
sfrb TIMSK=0x39;
sfrb GIFR=0x3a;
sfrb GICR=0x3b;
sfrb OCR0=0X3c;
sfrb SPL=0x3d;
sfrb SPH=0x3e;
sfrb SREG=0x3f;
#pragma used-

#asm
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x80
	.EQU __sm_mask=0x70
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0x60
	.EQU __sm_ext_standby=0x70
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
#endasm

#pragma used+

void delay_us(unsigned int n);
void delay_ms(unsigned int n);

#pragma used-

typedef char *va_list;

#pragma used+

char getchar(void);
void putchar(char c);
void puts(char *str);
void putsf(char flash *str);

char *gets(char *str,unsigned int len);

void printf(char flash *fmtstr,...);
void sprintf(char *str, char flash *fmtstr,...);
void snprintf(char *str, unsigned int size, char flash *fmtstr,...);
void vprintf (char flash * fmtstr, va_list argptr);
void vsprintf (char *str, char flash * fmtstr, va_list argptr);
void vsnprintf (char *str, unsigned int size, char flash * fmtstr, va_list argptr);
signed char scanf(char flash *fmtstr,...);
signed char sscanf(char *str, char flash *fmtstr,...);

#pragma used-

#pragma library stdio.lib

#asm
   .equ __lcd_port=0x1B ;PORTA
#endasm

#pragma used+

void _lcd_ready(void);
void _lcd_write_data(unsigned char data);

void lcd_write_byte(unsigned char addr, unsigned char data);

unsigned char lcd_read_byte(unsigned char addr);

void lcd_gotoxy(unsigned char x, unsigned char y);

void lcd_clear(void);
void lcd_putchar(char c);

void lcd_puts(char *str);

void lcd_putsf(char flash *str);

unsigned char lcd_init(unsigned char lcd_columns);

void lcd_control (unsigned char control);

#pragma used-
#pragma library lcd.lib

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

switch (row) {

case 0:

PORTC.3=1;
PORTC.2=0;
PORTC.1=0;
PORTC.0=0;

delay_ms(delayTime);

if (PINC.7==1) return 0;
else if (PINC.6==1) return 1;
else if (PINC.5==1) return 2;
else if (PINC.4==1) return 3;
else return -1;

break;

case 1:

PORTC.3=0;
PORTC.2=1;
PORTC.1=0;
PORTC.0=0;

delay_ms(delayTime);

if (PINC.7==1) return 4;
else if (PINC.6==1) return 5;
else if (PINC.5==1) return 6;
else if (PINC.4==1) return 7;
else return -1;

break;

case 2:

PORTC.3=0;
PORTC.2=0;
PORTC.1=1;
PORTC.0=0;

delay_ms(delayTime);

if (PINC.7==1) return 8;
else if (PINC.6==1) return 9;
else if (PINC.5==1) return 10;
else if (PINC.4==1) return 11;
else return -1;

break;

case 3:

PORTC.3=0;
PORTC.2=0;
PORTC.1=0;
PORTC.0=1;

delay_ms(delayTime);

if (PINC.7==1) return 12;
else if (PINC.6==1) return 13;
else if (PINC.5==1) return 14;
else if (PINC.4==1) return 15;
else return -1;

break;

default:
return -1;
};
}

void main(void)
{

lcd_init(16);

while (1)
{

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

if (x==0 && y==0) {lcd_gotoxy(x,y); lcd_putchar('');}
else if (x==0 && y==1) {x=15; y=0; lcd_gotoxy(x,y); lcd_putchar('');}
else {x--; lcd_gotoxy(x,y); lcd_putchar('');}
delay_ms(250);

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
