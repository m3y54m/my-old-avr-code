/*
 * uart_base.h
 *
 * Created: 03/13/2016 17:50:08
 * Author: Meysam Parvizi
 */ 


#ifndef UART_BASE_H_
#define UART_BASE_H_

#ifndef F_CPU
/* prevent compiler error by supplying a default */
#warning "F_CPU not defined for uart_base.h"
#define F_CPU 12000000UL
#endif

#include <avr/io.h>

void uart_init(unsigned long baud, bool enableTx, bool enableRx);
void uart_putchar(unsigned char data);
unsigned char uart_getchar(void);
void uart_puts(const char *str);

#endif /* UART_BASE_H_ */
