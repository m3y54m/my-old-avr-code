/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 1.0.9
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
#include <alcd.h>
#include <stdio.h>
#include <math.h>

#define MPU6050_ADDRESS 0b1101000
#define MS5611_ADDRESS  0b1110110

#define MPU6050_RA_XG_OFFS_TC 0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_YG_OFFS_TC 0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_ZG_OFFS_TC 0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_X_FINE_GAIN 0x03 //[7:0] X_FINE_GAIN
#define MPU6050_RA_Y_FINE_GAIN 0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_RA_Z_FINE_GAIN 0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_RA_XA_OFFS_H 0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC 0x07
#define MPU6050_RA_YA_OFFS_H 0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC 0x09
#define MPU6050_RA_ZA_OFFS_H 0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC 0x0B
#define MPU6050_RA_XG_OFFS_USRH 0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL 0x14
#define MPU6050_RA_YG_OFFS_USRH 0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL 0x16
#define MPU6050_RA_ZG_OFFS_USRH 0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL 0x18
#define MPU6050_RA_SMPLRT_DIV 0x19
#define MPU6050_RA_CONFIG 0x1A
#define MPU6050_RA_GYRO_CONFIG 0x1B
#define MPU6050_RA_ACCEL_CONFIG 0x1C
#define MPU6050_RA_FF_THR 0x1D
#define MPU6050_RA_FF_DUR 0x1E
#define MPU6050_RA_MOT_THR 0x1F
#define MPU6050_RA_MOT_DUR 0x20
#define MPU6050_RA_ZRMOT_THR 0x21
#define MPU6050_RA_ZRMOT_DUR 0x22
#define MPU6050_RA_FIFO_EN 0x23
#define MPU6050_RA_I2C_MST_CTRL 0x24
#define MPU6050_RA_I2C_SLV0_ADDR 0x25
#define MPU6050_RA_I2C_SLV0_REG 0x26
#define MPU6050_RA_I2C_SLV0_CTRL 0x27
#define MPU6050_RA_I2C_SLV1_ADDR 0x28
#define MPU6050_RA_I2C_SLV1_REG 0x29
#define MPU6050_RA_I2C_SLV1_CTRL 0x2A
#define MPU6050_RA_I2C_SLV2_ADDR 0x2B
#define MPU6050_RA_I2C_SLV2_REG 0x2C
#define MPU6050_RA_I2C_SLV2_CTRL 0x2D
#define MPU6050_RA_I2C_SLV3_ADDR 0x2E
#define MPU6050_RA_I2C_SLV3_REG 0x2F
#define MPU6050_RA_I2C_SLV3_CTRL 0x30
#define MPU6050_RA_I2C_SLV4_ADDR 0x31
#define MPU6050_RA_I2C_SLV4_REG 0x32
#define MPU6050_RA_I2C_SLV4_DO 0x33
#define MPU6050_RA_I2C_SLV4_CTRL 0x34
#define MPU6050_RA_I2C_SLV4_DI 0x35
#define MPU6050_RA_I2C_MST_STATUS 0x36
#define MPU6050_RA_INT_PIN_CFG 0x37
#define MPU6050_RA_INT_ENABLE 0x38
#define MPU6050_RA_DMP_INT_STATUS 0x39
#define MPU6050_RA_INT_STATUS 0x3A
#define MPU6050_RA_ACCEL_XOUT_H 0x3B
#define MPU6050_RA_ACCEL_XOUT_L 0x3C
#define MPU6050_RA_ACCEL_YOUT_H 0x3D
#define MPU6050_RA_ACCEL_YOUT_L 0x3E
#define MPU6050_RA_ACCEL_ZOUT_H 0x3F
#define MPU6050_RA_ACCEL_ZOUT_L 0x40
#define MPU6050_RA_TEMP_OUT_H 0x41
#define MPU6050_RA_TEMP_OUT_L 0x42
#define MPU6050_RA_GYRO_XOUT_H 0x43
#define MPU6050_RA_GYRO_XOUT_L 0x44
#define MPU6050_RA_GYRO_YOUT_H 0x45
#define MPU6050_RA_GYRO_YOUT_L 0x46
#define MPU6050_RA_GYRO_ZOUT_H 0x47
#define MPU6050_RA_GYRO_ZOUT_L 0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
#define MPU6050_RA_MOT_DETECT_STATUS 0x61
#define MPU6050_RA_I2C_SLV0_DO 0x63
#define MPU6050_RA_I2C_SLV1_DO 0x64
#define MPU6050_RA_I2C_SLV2_DO 0x65
#define MPU6050_RA_I2C_SLV3_DO 0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL 0x67
#define MPU6050_RA_SIGNAL_PATH_RESET 0x68
#define MPU6050_RA_MOT_DETECT_CTRL 0x69
#define MPU6050_RA_USER_CTRL 0x6A
#define MPU6050_RA_PWR_MGMT_1 0x6B
#define MPU6050_RA_PWR_MGMT_2 0x6C
#define MPU6050_RA_BANK_SEL 0x6D
#define MPU6050_RA_MEM_START_ADDR 0x6E
#define MPU6050_RA_MEM_R_W 0x6F
#define MPU6050_RA_DMP_CFG_1 0x70
#define MPU6050_RA_DMP_CFG_2 0x71
#define MPU6050_RA_FIFO_COUNTH 0x72
#define MPU6050_RA_FIFO_COUNTL 0x73
#define MPU6050_RA_FIFO_R_W 0x74
#define MPU6050_RA_WHO_AM_I 0x75

#define gyro_xsensitivity 66.5 //66.5 Dead on at last check
#define gyro_ysensitivity 66.5 //72.7 Dead on at last check
#define gyro_zsensitivity 65.5

void LDByteWriteI2C(unsigned char addr, unsigned char reg, unsigned char val);
void LDByteReadI2C(unsigned char addr, unsigned char reg, unsigned char *data, unsigned char length);
void Setup_MPU6050();
void MPU6050_Test_I2C();
void Calibrate_Gyros();
void Get_Accel_Values();
void Get_Accel_Angles();
void Get_Gyro_Rates();

signed int ACCEL_XOUT = 0;
signed int ACCEL_YOUT = 0;
signed int ACCEL_ZOUT = 0;
float GYRO_XRATE = 0;
float GYRO_YRATE = 0;
float GYRO_ZRATE = 0;
int GYRO_XRATERAW = 0;
int GYRO_YRATERAW = 0;
int GYRO_ZRATERAW = 0;

unsigned char GYRO_XOUT_L = ' ';
unsigned char GYRO_XOUT_H = ' ';
unsigned char GYRO_YOUT_L = ' ';
unsigned char GYRO_YOUT_H = ' ';
unsigned char GYRO_ZOUT_L = ' ';
unsigned char GYRO_ZOUT_H = ' ';
signed int GYRO_XOUT = 0;
signed int GYRO_YOUT = 0;
signed int GYRO_ZOUT = 0;	

unsigned char ACCEL_XOUT_L = ' ';
unsigned char ACCEL_XOUT_H = ' ';
unsigned char ACCEL_YOUT_L = ' ';
unsigned char ACCEL_YOUT_H = ' ';
unsigned char ACCEL_ZOUT_L = ' ';
unsigned char ACCEL_ZOUT_H = ' ';

signed long GYRO_XOUT_OFFSET_1000SUM = 0;
signed long GYRO_YOUT_OFFSET_1000SUM = 0;
signed long GYRO_ZOUT_OFFSET_1000SUM = 0;

float GYRO_XANGLE = 0;
float GYRO_YANGLE = 0;
float GYRO_ZANGLE = 0;
long GYRO_XANGLERAW = 0;
long GYRO_YANGLERAW = 0;
long GYRO_ZANGLERAW = 0;
float ACCEL_XANGLE = 0;
float ACCEL_YANGLE = 0;
float ACCEL_ZANGLE = 0;

float KALMAN_XANGLE = 0;
float KALMAN_YANGLE = 0;
float KALMAN_ZANGLE = 0;

signed int GYRO_XOUT_OFFSET = -84;
signed int GYRO_YOUT_OFFSET = -12;
signed int GYRO_ZOUT_OFFSET = -3;

float COMPLEMENTARY_XANGLE = 0;
float COMPLEMENTARY_YANGLE = 0;

float TARGET_XANGLE = 0;
float TARGET_YANGLE = 0;
float TARGET_ZRATE = 0;

float PID_XOUTPUT = 0;
float PID_YOUTPUT = 0;
float PID_ZOUTPUT = 0;

float KP = 26.0; //25 27/6/12
float KI = 200.0; //85 5/6/12
float KD = 7; //7 27/6/12

float ZKP = 40.0; //40 8/6/12
float ZKD = 25.0; //25 8/6/12

float XERROR = 0;
float YERROR = 0;
float ZERROR = 0;

float throttle = 0;

float OC1_output = 0.0;
float OC2_output = 0.0;
float OC3_output = 0.0;
float OC4_output = 0.0;

int count = 0;

float XINTEGRAL = 0;
float YINTEGRAL = 0;

int throttle_input = 0;
int yaw_input = 0;
int pitch_input = 0;
int roll_input = 0;

// TWI Master Transmitter or Receiver mode selection
#define TWI_WRITE 0
#define TWI_READ  1

// TWI Master receive buffer
unsigned char twi_rx_buffer[2];
unsigned char twi_rx_count;
unsigned char twi_rx_index;

// TWI Master transmit buffer
unsigned char twi_tx_buffer[2];
unsigned char twi_tx_count;
unsigned char twi_tx_index;

// TWI Slave 7-bit address
unsigned char twi_slave_addr;

bit twi_mode=0; // Master Transmitter:0 , Master Receiver:1

bit twi_rx_complete=0;
bit twi_tx_complete=0;
bit twi_error=0;

void twi_init()
{
   // Prescaler=1
   TWSR=0;
   // Bit Rate=100 khz (if XTAL=8Mhz)                                    
   TWBR=32;
}

unsigned char twi_exchange(unsigned char slave_addr,unsigned char tx_count,unsigned char rx_count)
{
   if (tx_count!=0 || rx_count!=0)
   {
      twi_tx_index=0;
      twi_rx_index=0;
      twi_tx_count=tx_count;
      twi_rx_count=rx_count;
      twi_slave_addr=slave_addr;
      twi_error=0;
      
      if (tx_count==0)
         twi_mode=1;
      else
         twi_mode=0; 
      
      // Send START condition and enable TWI interrupt
      TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
      
      if(tx_count!=0)
      {
         twi_tx_complete=0;
         while(twi_tx_complete==0 && twi_error==0);
         if (twi_error==1)
         {
            //puts("TWI TX ERROR\r\n");
            return 0;
         }
      }
         
      if(rx_count!=0)
      {
         twi_rx_complete=0; 
         while(twi_rx_complete==0 && twi_error==0);
         if (twi_error==1)
         {  
            //puts("TWI RX ERROR\r\n");
            return 0;
         }
      }
      
      return 1;
   }
   else 
      return 1; 
}

interrupt [TWI] void twi_interrupt(void)
{
   unsigned char twi_status;
   twi_status = TWSR & 0xF8;
   //printf("  STATUS:%X-TWWC:%d-TR:%d\r\n",twi_status,(TWCR & (1<<TWWC))>>TWWC,twi_mode);
   
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
         }
         else if (twi_rx_index==twi_rx_count-2)
         {
            // Data byte will be received and NOT ACK will be returned
            twi_rx_buffer[twi_rx_index] = TWDR;
            TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
            twi_rx_index++;
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
            twi_mode=1;
         }
         break;
         
      // Data byte has been received; NOT ACK has been returned
      case 0x58:
         twi_rx_buffer[twi_rx_index] = TWDR;
         // STOP condition will be transmitted and TWSTO Flag will be reset
         TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) | (1<<TWIE);
         
         twi_rx_complete=1;
         break;
            
      // SLA+W has been transmitted; NOT ACK has been received
      case 0x20:         
      // Data byte has been transmitted; NOT ACK has been received   
      case 0x30:   
      // SLA+R has been transmitted; NOT ACK has been received
      case 0x48:
         // STOP condition will be transmitted and TWSTO Flag will be reset
         TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO) | (1<<TWIE);
         twi_error=1;
         break;     
   }
}

void main(void)
{

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

Setup_MPU6050();
Calibrate_Gyros();
while (1)
{
//   signed int ACCEL_XOUT;
//   signed int ACCEL_YOUT;
//   signed int GYRO_ZOUT;
//   char temp_h;
//   char temp_l;
  char str[16];
   float ax;
   float ay;
//   float wz;
//   
//   LDByteReadI2C(MPU6050_ADDRESS,MPU6050_RA_ACCEL_XOUT_L,&temp_l,1);
//   LDByteReadI2C(MPU6050_ADDRESS,MPU6050_RA_ACCEL_XOUT_H,&temp_h,1);  
//   ACCEL_XOUT=((temp_h<<8)|temp_l);
//   ax=(float)ACCEL_XOUT / 16384;
//   
//   LDByteReadI2C(MPU6050_ADDRESS,MPU6050_RA_ACCEL_YOUT_L,&temp_l,1);
//   LDByteReadI2C(MPU6050_ADDRESS,MPU6050_RA_ACCEL_YOUT_H,&temp_h,1);  
//   ACCEL_YOUT=((temp_h<<8)|temp_l);
//   ay=(float)ACCEL_YOUT / 16384;
//   
//   LDByteReadI2C(MPU6050_ADDRESS,MPU6050_RA_GYRO_ZOUT_L,&temp_l,1);
//   LDByteReadI2C(MPU6050_ADDRESS,MPU6050_RA_GYRO_ZOUT_H,&temp_h,1);  
//   GYRO_ZOUT=((temp_h<<8)|temp_l);
//   wz=(float)ACCEL_XOUT / 65.5;
//   
//   
//   sprintf(str,"%.2f - %.2f",ax,ay);
//   //lcd_clear();
//   lcd_gotoxy(0,0);
//   lcd_puts(str);
//   lcd_gotoxy(0,1);
//   sprintf(str,"%.2f",wz);
//   lcd_puts(str);

   Get_Accel_Values();
   Get_Accel_Angles();
   Get_Gyro_Rates();
   
   ax=-(float)ACCEL_XOUT / 16384;
   ay=-(float)ACCEL_YOUT / 16384;
   
   lcd_clear();
   sprintf(str,"ax:%.2f",ax);
   lcd_gotoxy(0,0);
   lcd_puts(str);
   sprintf(str,"ay:%.2f",ay);
   lcd_gotoxy(0,1);
   lcd_puts(str);
//   lcd_gotoxy(0,1);
//   sprintf(str,"%.2f",GYRO_ZRATE);
//   lcd_puts(str);
   delay_ms(100);
}

}


void LDByteWriteI2C(unsigned char addr, unsigned char reg, unsigned char val)
{
      twi_tx_buffer[0]=reg;
      twi_tx_buffer[1]=val;
      while(!twi_exchange(addr,2,0));  
}

void LDByteReadI2C(unsigned char addr, unsigned char reg, unsigned char *data, unsigned char length)
{
      twi_tx_buffer[0]=reg;
      while(!twi_exchange(addr,1,length));
      *data=twi_rx_buffer[0]; 
}

void Setup_MPU6050()
{
    //Sets sample rate to 8000/1+7 = 1000Hz
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_SMPLRT_DIV, 0x07);
    //Disable FSync, 256Hz DLPF
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_CONFIG, 0x00);
    //Disable gyro self tests, scale of 500 degrees/s
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, 0b00001000);
    //Disable accel self tests, scale of +-2g, no DHPF
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, 0x00);
    //Freefall threshold of |0mg|
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_FF_THR, 0x00);
    //Freefall duration limit of 0
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_FF_DUR, 0x00);
    //Motion threshold of 0mg
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_MOT_THR, 0x00);
    //Motion duration of 0s
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_MOT_DUR, 0x00);
    //Zero motion threshold
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_THR, 0x00);
    //Zero motion duration threshold
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_ZRMOT_DUR, 0x00);
    //Disable sensor output to FIFO buffer
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, 0x00);
 
    //AUX I2C setup
    //Sets AUX I2C to single master control, plus other config
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, 0x00);
    //Setup AUX I2C slaves
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_ADDR, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_REG, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_CTRL, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_ADDR, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_REG, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_CTRL, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_ADDR, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_REG, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_CTRL, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_ADDR, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_REG, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_CTRL, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_ADDR, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_REG, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DO, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_CTRL, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV4_DI, 0x00);
 
    //MPU6050_RA_I2C_MST_STATUS //Read-only
    //Setup INT pin and AUX I2C pass through
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, 0x00);
    //Enable data ready interrupt
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, 0x00);
 
    //MPU6050_RA_DMP_INT_STATUS        //Read-only
    //MPU6050_RA_INT_STATUS 3A        //Read-only
    //MPU6050_RA_ACCEL_XOUT_H         //Read-only
    //MPU6050_RA_ACCEL_XOUT_L         //Read-only
    //MPU6050_RA_ACCEL_YOUT_H         //Read-only
    //MPU6050_RA_ACCEL_YOUT_L         //Read-only
    //MPU6050_RA_ACCEL_ZOUT_H         //Read-only
    //MPU6050_RA_ACCEL_ZOUT_L         //Read-only
    //MPU6050_RA_TEMP_OUT_H         //Read-only
    //MPU6050_RA_TEMP_OUT_L         //Read-only
    //MPU6050_RA_GYRO_XOUT_H         //Read-only
    //MPU6050_RA_GYRO_XOUT_L         //Read-only
    //MPU6050_RA_GYRO_YOUT_H         //Read-only
    //MPU6050_RA_GYRO_YOUT_L         //Read-only
    //MPU6050_RA_GYRO_ZOUT_H         //Read-only
    //MPU6050_RA_GYRO_ZOUT_L         //Read-only
    //MPU6050_RA_EXT_SENS_DATA_00     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_01     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_02     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_03     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_04     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_05     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_06     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_07     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_08     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_09     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_10     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_11     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_12     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_13     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_14     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_15     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_16     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_17     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_18     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_19     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_20     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_21     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_22     //Read-only
    //MPU6050_RA_EXT_SENS_DATA_23     //Read-only
    //MPU6050_RA_MOT_DETECT_STATUS     //Read-only
 
    //Slave out, dont care
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV0_DO, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV1_DO, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV2_DO, 0x00);
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_SLV3_DO, 0x00);
    //More slave config
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
    //Reset sensor signal paths
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
    //Motion detection control
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_MOT_DETECT_CTRL, 0x00);
    //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_USER_CTRL, 0x00);
    //Sets clock source to gyro reference w/ PLL
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, 0b00000010);
    //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_2, 0x00);
    //MPU6050_RA_BANK_SEL            //Not in datasheet
    //MPU6050_RA_MEM_START_ADDR        //Not in datasheet
    //MPU6050_RA_MEM_R_W            //Not in datasheet
    //MPU6050_RA_DMP_CFG_1            //Not in datasheet
    //MPU6050_RA_DMP_CFG_2            //Not in datasheet
    //MPU6050_RA_FIFO_COUNTH        //Read-only
    //MPU6050_RA_FIFO_COUNTL        //Read-only
    //Data transfer to and from the FIFO buffer
    LDByteWriteI2C(MPU6050_ADDRESS, MPU6050_RA_FIFO_R_W, 0x00);
    //MPU6050_RA_WHO_AM_I             //Read-only, I2C address
 
    //printf("\r\nMPU6050 Setup Complete");
}

void MPU6050_Test_I2C()
{
    unsigned char Data = 0x00;
    LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, &Data, 1);
 
    if(Data == 0x68)
    {
        printf("\nI2C Read Test Passed, MPU6050 Address: 0x%x", Data);
    }
    else
    {
        printf("ERROR: I2C Read Test Failed, Stopping. MPU6050 Address! 0x%x", Data);
    
    }    
}

void Calibrate_Gyros()
{
   int x = 0;
   for(x = 0; x<1000; x++)
   {
      LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H, &GYRO_XOUT_H, 1);
      LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_L, &GYRO_XOUT_L, 1);
      LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_H, &GYRO_YOUT_H, 1);
      LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_L, &GYRO_YOUT_L, 1);
      LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_H, &GYRO_ZOUT_H, 1);
      LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_L, &GYRO_ZOUT_L, 1);
 
      GYRO_XOUT_OFFSET_1000SUM += ((GYRO_XOUT_H<<8)|GYRO_XOUT_L);
      GYRO_YOUT_OFFSET_1000SUM += ((GYRO_YOUT_H<<8)|GYRO_YOUT_L);
      GYRO_ZOUT_OFFSET_1000SUM += ((GYRO_ZOUT_H<<8)|GYRO_ZOUT_L);
 
      delay_ms(1);
   }   
   GYRO_XOUT_OFFSET = GYRO_XOUT_OFFSET_1000SUM/1000;
   GYRO_YOUT_OFFSET = GYRO_YOUT_OFFSET_1000SUM/1000;
   GYRO_ZOUT_OFFSET = GYRO_ZOUT_OFFSET_1000SUM/1000;
 
//   printf("\nGyro X offset sum: %ld Gyro X offset: %d", GYRO_XOUT_OFFSET_1000SUM, GYRO_XOUT_OFFSET);
//   printf("\nGyro Y offset sum: %ld Gyro Y offset: %d", GYRO_YOUT_OFFSET_1000SUM, GYRO_YOUT_OFFSET);
//   printf("\nGyro Z offset sum: %ld Gyro Z offset: %d", GYRO_ZOUT_OFFSET_1000SUM, GYRO_ZOUT_OFFSET);
}   
 
//Gets raw accelerometer data, performs no processing
void Get_Accel_Values()
{
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, &ACCEL_XOUT_H, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_L, &ACCEL_XOUT_L, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_H, &ACCEL_YOUT_H, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_L, &ACCEL_YOUT_L, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_H, &ACCEL_ZOUT_H, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_L, &ACCEL_ZOUT_L, 1);
 
   ACCEL_XOUT = ((ACCEL_XOUT_H<<8)|ACCEL_XOUT_L);
   ACCEL_YOUT = ((ACCEL_YOUT_H<<8)|ACCEL_YOUT_L);
   ACCEL_ZOUT = ((ACCEL_ZOUT_H<<8)|ACCEL_ZOUT_L);      
}   
 
//Converts the already acquired accelerometer data into 3D euler angles
void Get_Accel_Angles()
{
   ACCEL_XANGLE = 57.295*atan((float)ACCEL_YOUT/ sqrt(pow((float)ACCEL_ZOUT,2)+pow((float)ACCEL_XOUT,2)));
   ACCEL_YANGLE = 57.295*atan((float)-ACCEL_XOUT/ sqrt(pow((float)ACCEL_ZOUT,2)+pow((float)ACCEL_YOUT,2)));   
}   
 
//Function to read the gyroscope rate data and convert it into degrees/s
void Get_Gyro_Rates()
{
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H, &GYRO_XOUT_H, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_L, &GYRO_XOUT_L, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_H, &GYRO_YOUT_H, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_L, &GYRO_YOUT_L, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_H, &GYRO_ZOUT_H, 1);
   LDByteReadI2C(MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_L, &GYRO_ZOUT_L, 1);
 
   GYRO_XOUT = ((GYRO_XOUT_H<<8)|GYRO_XOUT_L) - GYRO_XOUT_OFFSET;
   GYRO_YOUT = ((GYRO_YOUT_H<<8)|GYRO_YOUT_L) - GYRO_YOUT_OFFSET;
   GYRO_ZOUT = ((GYRO_ZOUT_H<<8)|GYRO_ZOUT_L) - GYRO_ZOUT_OFFSET;
 
 
   GYRO_XRATE = (float)GYRO_XOUT/gyro_xsensitivity;
   GYRO_YRATE = (float)GYRO_YOUT/gyro_ysensitivity;
   GYRO_ZRATE = (float)GYRO_ZOUT/gyro_zsensitivity;
}
