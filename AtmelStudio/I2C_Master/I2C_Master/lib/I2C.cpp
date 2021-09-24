/* 
* I2C.cpp
*
* Created: 03/15/2016 12:20:01
* Author: Meysam Parvizi
*/


#include "I2C.h"
#include <inttypes.h>
#include <util/twi.h>
#include "twi_base.h"

// default constructor
I2C::I2C()
{
} //I2C

void I2C::init(uint32_t hz)
{
	twi_init(hz);
}

uint8_t I2C::read(uint8_t address, char *data, uint8_t length, bool repeated)
{
	uint8_t count, status;
	
	status = twi_start();

	if ((status != 0x10) && (status != 0x08)) {
		twi_stop();
		//return I2C_ERROR_BUS_BUSY;
	}

	status = twi_write_byte((address<<1) | TW_READ);
	if (status != 0x40) {
		twi_stop();
		//return I2C_ERROR_NO_SLAVE;
	}


	// Read in all except last byte
	for (count = 0; count < (length - 1); count++) {
		uint8_t value = twi_read_byte_ack();
		status = twi_status();
		if (status != 0x50) {
			twi_stop();
			return count;
		}
		data[count] = (char) value;
	}

	// read in last byte
	uint8_t value = twi_read_byte_no_ack();
	status = twi_status();
	if (status != 0x58) {
		twi_stop();
		return length - 1;
	}

	data[count] = (char) value;

	// If not repeated start, send stop.
	if (!repeated) {
		twi_stop();
	}

	return 0;
}

uint8_t I2C::readByte(bool ack)
{
	if (ack)
		return twi_read_byte_ack();
	else
		return twi_read_byte_no_ack();
}

uint8_t I2C::write(uint8_t address, const char *data, uint8_t length, bool repeated)
{
    uint8_t i, status;
	
    status = twi_start();
    
    if ((status != 0x10) && (status != 0x08)) {
	    twi_stop(); 
		//return I2C_ERROR_BUS_BUSY;
    }
    
    status = twi_write_byte((address<<1) | TW_WRITE);
    if (status != 0x18) {
	    twi_stop();
		//return I2C_ERROR_NO_SLAVE; 
    }
    
    for (i=0; i<length; i++) {
	    status = twi_write_byte(data[i]);
	    if(status != 0x28) {
		    twi_stop();
		    return i;
	    }
    }
	
    // If not repeated start, send stop.
    if (!repeated) {
	    twi_stop();
    }
    
	return 0;
}

uint8_t I2C::writeByte(uint8_t data)
{
	return twi_write_byte(data);
}

void I2C::start(void)
{
	twi_start();
}

void I2C::stop(void)
{
	twi_stop();
}

// default destructor
I2C::~I2C()
{
} //~I2C
