/**
 * BalancingRobot.cpp
 *
 * Created: 03/15/2016 15:12:35
 * Author: Meysam Parvizi
 */ 

#define F_CPU 8000000UL
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
#include "lib/I2C.h"
#include "lib/MPU6050.h"
#include "lib/PID.h"

#define MOTOR_A_DIRECTION PORTB0
#define MOTOR_B_DIRECTION PORTB1
#define MOTOR_A_ENABLE    PORTD5
#define MOTOR_B_ENABLE    PORTD4

#define MPU6050_INTA INT0_vect

#define LCD_RS PORTA0
#define LCD_RW PORTA1
#define LCD_E  PORTA2
#define LCD_D4 PORTA4
#define LCD_D5 PORTA5
#define LCD_D6 PORTA6
#define LCD_D7 PORTA7

Serial serial;
I2C i2c;
MPU6050 mpu6050;

#define RATE  0.008
#define Kc	10.0
#define Ti	1.0
#define Td	0.001

PID pid(Kc, Ti, Td, RATE);

void motorDrive(char motor, signed int pwm);

char str[32];
float thetaAccel;
float thetaGyro;
float theta;
float drive;

ISR(TIMER0_OVF_vect)
{
	// Reinitialize Timer0 value
	TCNT0=0x06;
		
	mpu6050.readAccelData(accelData);
	mpu6050.getAres();
	//ax = accelData[0]*aRes;// - accelBias[0];
	ay = accelData[1]*aRes;// - accelBias[1];
	az = accelData[2]*aRes;// - accelBias[2];

	mpu6050.readGyroData(gyroData);
	mpu6050.getGres();
	gx = gyroData[0]*gRes;
	//gy = gyroData[1]*gRes;
	//gz = gyroData[2]*gRes;

	thetaAccel = atan2(ay,az) * 180 / PI;   
	thetaGyro = theta + gx * RATE;					// Angle around the X-axis
	
	// Apply Complementary Filter
	theta = thetaGyro * 0.98 + thetaAccel * 0.02;
	
	pid.setSetPoint(62.0);					// At 60 Degrees is balanced -> setPoint = 60
	pid.setProcessValue(theta);
	drive = pid.compute();

	if (drive != 0)
	{
		if (fabs(drive) < 100) drive = (fabs(drive) / drive) * 100;
	}

	motorDrive(1, (signed int)drive);
	motorDrive(2, (signed int)drive);

	//sprintf(str,"%d\r\n",(int)theta);
	//sprintf(str,"%.3f\r\n",gx);
	//serial.write(str);
}

int main(void)
{
	DDRB = _BV(MOTOR_A_DIRECTION) | _BV(MOTOR_B_DIRECTION);
	DDRD = _BV(MOTOR_A_ENABLE) | _BV(MOTOR_B_ENABLE);
	
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 1000.000 kHz
	// Mode: Ph. correct PWM top=0x00FF
	// OC1A output: Non-Inverted PWM
	// OC1B output: Non-Inverted PWM
	// Timer Period: 0.51 ms
	// Output Pulse(s):
	// OC1A Period: 0.51 ms Width: 0 us
	// OC1B Period: 0.51 ms Width: 0 us
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	TCCR1B = (1<<CS11);
	OCR1AL = 0x00;
	OCR1BL = 0x00;
	
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 31.250 kHz
	// Mode: Normal top=0xFF
	// Timer Period: 8 ms
	TCCR0 = (1<<CS02);
	TCNT0 = 0x06;
	
	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK = (1<<TOIE0);
	
	serial.init(500000, true, false);
	
	i2c.init(400000);
	
	mpu6050.whoAmI();                              // Communication test: WHO_AM_I register reading
	mpu6050.calibrate(accelBias,gyroBias);         // Calibrate MPU6050 and load biases into bias registers		
	mpu6050.init();                                // Initialize the sensors
	
	pid.setInputLimits(30, 90);
	pid.setOutputLimits(-255, 255);
	pid.setBias(0);
	pid.setMode(AUTO_MODE);
	
	sei();
	
    while(1);
}

void motorDrive(char motor, signed int pwm)
{
	switch(motor)
	{
		case 1:
		
			if (pwm > 0)        // Motor A Forward
			{
				PORTB |= _BV(MOTOR_A_DIRECTION);
				OCR1AL = (uint8_t)pwm;
			}
			else if (pwm < 0)   // Motor A Backward
			{
				PORTB &= ~_BV(MOTOR_A_DIRECTION);
				OCR1AL = (uint8_t)(-pwm);
			}
		
			break;
		
		case 2:
		
			if (pwm > 0)        // Motor B Forward
			{
				PORTB |= _BV(MOTOR_B_DIRECTION);
				OCR1BL = (uint8_t)pwm;
			}
			else if (pwm < 0)   // Motor B Backward
			{
				PORTB &= ~_BV(MOTOR_B_DIRECTION);
				OCR1BL = (uint8_t)(-pwm);
			}
		
			break;
	}
}