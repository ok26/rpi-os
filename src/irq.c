#include "utils.h"
#include "printf.h"
#include "timer.h"
#include "io.h"
#include "entry.h"
#include "peripherals/irq.h"

void enable_interrupt_controller() {
    put32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1 | AUX_IRQ);
}

void entry_error(int type, unsigned long esr, unsigned long address) {
    printf("Type: %s, ESR: %x, address: %x\r\n", type, esr, address);
}

void handle_irq() {
    while (1) {
        unsigned int irq = get32(IRQ_PENDING_1);
        switch (irq) {
            case (SYSTEM_TIMER_IRQ_1):
                handle_timer_irq();
                break;
            case (AUX_IRQ):
                handle_uart_irq();
                break;
            default:
                printf("Unkownn pending irq: %x\r\n", irq);
                return;
        }
    }
}