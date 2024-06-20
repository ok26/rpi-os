#include "utils.h"
#include "peripherals/io.h"
#include "peripherals/gpio.h"

void uart_init() {
    unsigned int selector;

	selector = get32(GPFSEL1);				  // pins 10-19
	selector &= ~(7 << 12);                   // gpio14
	selector |= 2 << 12;                      // set alt5 for gpio14
	selector &= ~(7 << 15);                   // gpio15
	selector |= 2 << 15;                      // set alt5 for gpio15
	put32(GPFSEL1, selector);

	put32(GPPUD, 0);
	delay(150);
	put32(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);
	put32(GPPUDCLK0, 0);

	put32(AUX_ENABLES, 1);     				// Enable mini uart
	put32(AUX_MU_CNTL_REG, 0); 				// Disable auto flow control and disable receiver and transmitter (for now)
	put32(AUX_MU_IER_REG, MU_IER_RXEN); 	// Enable receive interrupts
	put32(AUX_MU_LCR_REG, 3);           	// Enable 8 bit mode
	put32(AUX_MU_MCR_REG, 0);           	// Set RTS line to be always high
	put32(AUX_MU_BAUD_REG, 270);        	// Set baud rate to 115200

	put32(AUX_MU_CNTL_REG, 3); // 
}

void uart_send(unsigned char ch) {
    while (!(get32(AUX_MU_LSR_REG) & 0x20)); 
    put32(AUX_MU_IO_REG, (unsigned int)ch);
}

char uart_recv() {
    while (!(get32(AUX_MU_LSR_REG) & 0x01)); 
    return (unsigned char)(get32(AUX_MU_IO_REG) & 0xFF);
}

void putc(void* p, char c) {
	uart_send(c);
}

void handle_uart_irq() {
	if (get32(AUX_MU_IIR_REG) & MU_IIR_RX_READY) {
		char c = get32(AUX_MU_IO_REG) & 0xFF;
		put32(AUX_MU_IIR_REG, MU_IIR_RX_CLR);
		
		uart_send(c);
  	}
}