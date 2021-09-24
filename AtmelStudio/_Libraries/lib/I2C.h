/* 
* I2C.h
*
* Created: 03/15/2016 12:20:01
* Author: Meysam Parvizi
*/


#ifndef __I2C_H__
#define __I2C_H__

#include <inttypes.h>

class I2C
{
//functions
public:
	I2C();
	~I2C();
    void init(uint32_t hz);
    uint8_t read(uint8_t address, char *data, uint8_t length, bool repeated = false);
	uint8_t readByte(bool ack = false);
    uint8_t write(uint8_t address, const char *data, uint8_t length, bool repeated = false);
    uint8_t writeByte(uint8_t data);
    void start(void);
    void stop(void);
private:
	I2C( const I2C &c );
	I2C& operator=( const I2C &c );

}; //I2C

#endif //__I2C_H__
