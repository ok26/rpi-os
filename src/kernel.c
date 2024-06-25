#include "utils.h"
#include "printf.h"
#include "io.h"
#include "timer.h"
#include "irq.h"

void main() {
    uart_init();
    init_printf(0, putc);
    irq_vector_init();
    timer_init();
    enable_interrupt_controller();
    enable_irq();

    printf("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?=+,.\n> ");

    while (1) {
        char c = uart_recv();
        if (c == 0x7F) {
            uart_send((char)0x08);
            uart_send(c);
            uart_send((char)0x08);
        }
        else uart_send(c);
        
        if (c == 0x0D) {
            printf("\nNot implemented\n> ");
            int current_ind = 0;
        }
    };
}