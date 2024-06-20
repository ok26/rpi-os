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

    printf("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?=+,.\r\n");
    
    while (1);
}