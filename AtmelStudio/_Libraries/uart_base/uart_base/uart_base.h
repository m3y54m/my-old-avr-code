/*
 * uart_base.h
 *
 * Created: 03/13/2016 17:50:08
 *  Author: Administrator
 */ 


#ifndef UART_BASE_H_
#define UART_BASE_H_


void uart_init(unsigned int baud);
void uart_putc(unsigned char data);
unsigned char uart_getc();
void uart_puts(const char *str);


#endif /* UART_BASE_H_ */