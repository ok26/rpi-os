#ifndef _IO_H
#define _IO_H

void uart_init();
void uart_send();
char uart_recv();
void putc(void* p, char c);

void handle_uart_irq();

#endif