/* 
* Serial.h
*
* Created: 03/13/2016 18:48:23
* Author: Meysam Parvizi
*/


#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <inttypes.h>

class Serial
{
//functions
public:
	Serial();
	void init(uint32_t baud, bool enableTx, bool enableRx);
	void _putc(uint8_t data);
	uint8_t _getc();
	void write(const char *str);
	~Serial();
}; //Serial

#endif //__SERIAL_H__
