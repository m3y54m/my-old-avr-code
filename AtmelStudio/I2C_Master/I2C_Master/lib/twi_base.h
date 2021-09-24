/*
 * twi_base.h
 *
 * Created: 03/15/2016 10:04:55
 * Author: Meysam Parvizi
 */ 


#ifndef TWI_BASE_H_
#define TWI_BASE_H_

#ifndef F_CPU
/* prevent compiler error by supplying a default */
#warning "F_CPU not defined for twi_base.h"
#define F_CPU 8000000UL
#endif

// Initializes bus speed
void twi_init(unsigned long frequency);
// Waits until the hardware sets the TWINT flag
void twi_wait_for_complete(void);
// Sends a start condition (sets TWSTA)
unsigned char twi_start(void);
// Sends a stop condition (sets TWSTO)
void twi_stop(void);
// Loads data, sends it out, waiting for completion
unsigned char twi_write_byte(unsigned char data);
// Read in from slave, sending ACK when done (sets TWEA)
unsigned char twi_read_byte_ack(void);
// Read in from slave, sending NOACK when done (no TWEA)
unsigned char twi_read_byte_no_ack(void);
unsigned char twi_status(void);

#endif /* TWI_BASE_H_ */
