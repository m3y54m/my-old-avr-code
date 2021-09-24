#include "MPU6050.h"

unsigned char BYTE_L;
unsigned char BYTE_H;

unsigned char MPU6050_write_reg(unsigned char reg, unsigned char val)
{
   i2cStart();
   i2cSend((MPU6050_ADDRESS<<1) | TWI_WRITE);
   i2cSend(reg);
   i2cSend(val);
   i2cStop();
   return 1;  
}

unsigned char MPU6050_read_reg(unsigned char reg)
{
   unsigned char data;
   i2cStart();
   i2cSend((MPU6050_ADDRESS<<1) | TWI_WRITE);
   i2cSend(reg);
   i2cStart();
   i2cSend((MPU6050_ADDRESS<<1) | TWI_READ);
   data = i2cReadNoAck();
   i2cStop();
   return data;		
}

unsigned char MPU6050_init(void)
{
   unsigned char success=1;

   //Sets sample rate to 8000/1+7 = 1000Hz
   success &= MPU6050_write_reg(MPU6050_RA_SMPLRT_DIV, 0x07);
   //Disable FSync, 256Hz DLPF
   success &= MPU6050_write_reg(MPU6050_RA_CONFIG, 0x00);
   //Disable gyro self tests, scale of 250 degrees/s
   success &= MPU6050_write_reg(MPU6050_RA_GYRO_CONFIG, 0x00);
   //Disable accel self tests, scale of +-2g, no DHPF
   success &= MPU6050_write_reg(MPU6050_RA_ACCEL_CONFIG, 0x00);
   //Freefall threshold of |0mg|
   success &= MPU6050_write_reg(MPU6050_RA_FF_THR, 0x00);
   //Freefall duration limit of 0
   success &= MPU6050_write_reg(MPU6050_RA_FF_DUR, 0x00);
   //Motion threshold of 0mg
   success &= MPU6050_write_reg(MPU6050_RA_MOT_THR, 0x00);
   //Motion duration of 0s
   success &= MPU6050_write_reg(MPU6050_RA_MOT_DUR, 0x00);
   //Zero motion threshold
   success &= MPU6050_write_reg(MPU6050_RA_ZRMOT_THR, 0x00);
   //Zero motion duration threshold
   success &= MPU6050_write_reg(MPU6050_RA_ZRMOT_DUR, 0x00);
   //Disable sensor output to FIFO buffer
   success &= MPU6050_write_reg(MPU6050_RA_FIFO_EN, 0x00);
   
   //AUX I2C setup
   //Sets AUX I2C to single master control, plus other config
   success &= MPU6050_write_reg(MPU6050_RA_I2C_MST_CTRL, 0x00);
   //Setup AUX I2C slaves
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV0_ADDR, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV0_REG, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV0_CTRL, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV1_ADDR, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV1_REG, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV1_CTRL, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV2_ADDR, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV2_REG, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV2_CTRL, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV3_ADDR, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV3_REG, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV3_CTRL, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV4_ADDR, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV4_REG, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV4_DO, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV4_CTRL, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV4_DI, 0x00);
    
   //MPU6050_RA_I2C_MST_STATUS //Read-only
   //Setup INT pin and AUX I2C pass through
   success &= MPU6050_write_reg(MPU6050_RA_INT_PIN_CFG, 0x00);
   //Enable data ready interrupt
   success &= MPU6050_write_reg(MPU6050_RA_INT_ENABLE, 0x00);
     
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
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV0_DO, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV1_DO, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV2_DO, 0x00);
   success &= MPU6050_write_reg(MPU6050_RA_I2C_SLV3_DO, 0x00);
   //More slave config
   success &= MPU6050_write_reg(MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
   //Reset sensor signal paths
   success &= MPU6050_write_reg(MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
   //Motion detection control
   success &= MPU6050_write_reg(MPU6050_RA_MOT_DETECT_CTRL, 0x00);
   //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
   success &= MPU6050_write_reg(MPU6050_RA_USER_CTRL, 0x00);
   //Sets clock source to gyro reference w/ PLL
   success &= MPU6050_write_reg(MPU6050_RA_PWR_MGMT_1, 0b00000010);
   //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
   success &= MPU6050_write_reg(MPU6050_RA_PWR_MGMT_2, 0x00);
   //MPU6050_RA_BANK_SEL            //Not in datasheet
   //MPU6050_RA_MEM_START_ADDR        //Not in datasheet
   //MPU6050_RA_MEM_R_W            //Not in datasheet
   //MPU6050_RA_DMP_CFG_1            //Not in datasheet
   //MPU6050_RA_DMP_CFG_2            //Not in datasheet
   //MPU6050_RA_FIFO_COUNTH        //Read-only
   //MPU6050_RA_FIFO_COUNTL        //Read-only
   //Data transfer to and from the FIFO buffer
   success &= MPU6050_write_reg(MPU6050_RA_FIFO_R_W, 0x00);
   //MPU6050_RA_WHO_AM_I             //Read-only, I2C address

   return success;
}

void MPU6050_calibrate_gyro(signed int *GYRO_XOUT_OFFSET,signed int *GYRO_YOUT_OFFSET,signed int *GYRO_ZOUT_OFFSET)
{
	int x = 0;
	signed long GYRO_XOUT_OFFSET_1000SUM = 0;
	signed long GYRO_YOUT_OFFSET_1000SUM = 0;
	signed long GYRO_ZOUT_OFFSET_1000SUM = 0;
	for(x = 0; x<1000; x++)
	{
		BYTE_H=MPU6050_read_reg(MPU6050_RA_GYRO_XOUT_H);
		BYTE_L=MPU6050_read_reg(MPU6050_RA_GYRO_XOUT_L);
		GYRO_XOUT_OFFSET_1000SUM += ((BYTE_H<<8)|BYTE_L);
      
      BYTE_H=MPU6050_read_reg(MPU6050_RA_GYRO_YOUT_H);
		BYTE_L=MPU6050_read_reg(MPU6050_RA_GYRO_YOUT_L);
		GYRO_YOUT_OFFSET_1000SUM += ((BYTE_H<<8)|BYTE_L);
      
		BYTE_H=MPU6050_read_reg(MPU6050_RA_GYRO_ZOUT_H);
		BYTE_L=MPU6050_read_reg(MPU6050_RA_GYRO_ZOUT_L);
		GYRO_ZOUT_OFFSET_1000SUM += ((BYTE_H<<8)|BYTE_L);
		
		delay_ms(1);
	}	
	*GYRO_XOUT_OFFSET = GYRO_XOUT_OFFSET_1000SUM/1000;
	*GYRO_YOUT_OFFSET = GYRO_YOUT_OFFSET_1000SUM/1000;
	*GYRO_ZOUT_OFFSET = GYRO_ZOUT_OFFSET_1000SUM/1000;
}

unsigned char MPU6050_test(void)
{
    unsigned char data=0x00;
    
    data=MPU6050_read_reg(MPU6050_RA_WHO_AM_I);
    
    if(data==MPU6050_ADDRESS)
        return data;
    else
        return 0;   
}

void initI2C(void) {
TWBR = 32; /* set bit rate, see p. 242 */
/* 8MHz / (16+2*TWBR*1) ~= 100kHz */
TWCR |= (1 << TWEN); /* enable */
}
void i2cWaitForComplete(void) {
while (!(TWCR & (1<<TWINT)));
}
void i2cStart(void) {
TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
i2cWaitForComplete();
}
void i2cStop(void) {
TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}
unsigned char i2cReadAck(void) {
TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
i2cWaitForComplete();
return (TWDR);
}
unsigned char i2cReadNoAck(void) {
TWCR = (1<<TWINT) | (1<<TWEN);
i2cWaitForComplete();
return (TWDR);
}
void i2cSend(unsigned char data) {
TWDR = data;
TWCR = (1<<TWINT) | (1<<TWEN); /* init and enable */
i2cWaitForComplete();
}