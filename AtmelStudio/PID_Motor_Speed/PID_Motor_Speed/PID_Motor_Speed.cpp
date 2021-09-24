/*
 * PID_Motor_Speed.cpp
 *
 * Created: 03/30/2016 17:18:49
 *  Author: Meysam Parvizi
 */ 

#define F_CPU 12000000UL
#include <avr/io.h>
#include <stdio.h>
/*
   If the full functionality including the "floating point" conversions
   is required, the following options should be used:
   
   -Wl,-u,vfprintf -lprintf_flt -lm
   
   in Properties -> Toolchain -> AVR/GNU Linker -> Miscellaneous
*/
#include <util/delay.h>
#include <inttypes.h>
#include <math.h>
#include <avr/interrupt.h>
#include "lib/Serial.h"
#include "lib/PID.h"

#define encoderA (PIND & _BV(PIND2)) >> PIND2
#define encoderB (PIND & _BV(PIND3)) >> PIND3
#define maxSpeed 127
#define RATIO (127.0F / maxSpeed)

#define MOTOR_PWM OCR0 // PORTB3

#define ENCODER_PHASE_A INT0_vect
#define ENCODER_PHASE_B INT0_vect

Serial serial;

#define RATE  0.04
#define Kc	0.035
#define Ti	0.1
#define Td	0.0

PID pid(Kc, Ti, Td, RATE);

char str[32];
bool countStart = 0;
signed int position = 0;  // pulses count with direction
signed int lastPosition = 0;
signed int speed = 0;     // pulses per n*10ms
signed char data = 0;

unsigned char lastStateA = 0;
unsigned char currentStateB = 0;

// External Interrupt 0 service routine
ISR(INT0_vect)
{
	if (currentStateB ^ lastStateA)
	position++;
	else
	position--;

	lastStateA = encoderA;

	//printf("%d\r\n",position);
}

// External Interrupt 1 service routine
ISR(INT1_vect)
{
	currentStateB = encoderB;
  
	if (currentStateB ^ lastStateA)
	position++;
	else
	position--;

	//printf("%d\r\n",position);
}

// Timer1 overflow interrupt service routine
ISR(TIMER1_OVF_vect)
{
	// Reinitialize Timer1 value
	TCNT1 = 0x15A0;

	if (countStart==0)
	{
		countStart=1;
		lastPosition = position;
		position = 0;  // reset position
	}
	else
	{
		int temp;
		    
		speed = position - lastPosition;
		    
		temp = (signed int)(RATIO * speed);
		    
		if (temp > 127) temp = 127;     //overflow
		if (temp < -127) temp = -127;   //overflow // -128 reserved for error situations
		    
		data = temp;
		    
		countStart=0;
		
		if (speed < 0) speed = 0;
		
		pid.setProcessValue(speed);
		MOTOR_PWM = (uint8_t)(pid.compute());
		
		sprintf(str,"%d\r\n",speed);
		serial.write(str);
		
		//serial._putc((uint8_t)speed);
	}
}



int main(void)
{
	// Port B initialization
	// Function: Bit3=Out
	DDRB = _BV(DDRB3);
	
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 12000.000 kHz
	// Mode: Phase correct PWM top=0xFF
	// OC0 output: Non-Inverted PWM
	// Timer Period: 0.0425 ms
	// Output Pulse(s):
	// OC0 Period: 0.0425 ms Width: 0 us
	TCCR0=(1<<WGM00) | (1<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (1<<CS00);
	TCNT0=0x00;
	OCR0=0x00;

	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 1500.000 kHz
	// Mode: Normal top=0xFFFF
	// OC1A output: Disconnected
	// OC1B output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer Period: 40 ms
	// Timer1 Overflow Interrupt: On
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
	TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
	TCNT1H=0x15;
	TCNT1L=0xA0;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;

	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

	// External Interrupt(s) initialization
	// INT0: On
	// INT0 Mode: Any change
	// INT1: On
	// INT1 Mode: Any change
	// INT2: Off
	GICR|=(1<<INT1) | (1<<INT0) | (0<<INT2);
	MCUCR=(0<<ISC11) | (1<<ISC10) | (0<<ISC01) | (1<<ISC00);
	MCUCSR=(0<<ISC2);
	GIFR=(1<<INTF1) | (1<<INTF0) | (0<<INTF2);
	
	serial.init(250000, true, false);
	
	pid.setInputLimits(0, 90);
	pid.setOutputLimits(0, 255);
	pid.setBias(0);
	pid.setMode(AUTO_MODE);
	pid.setSetPoint(50);
	
	sei();
	
    while(1);
}