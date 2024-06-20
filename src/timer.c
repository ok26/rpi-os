#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"

const unsigned int interval = 200000;
unsigned int curTick = 0;

void timer_init() {
	curTick = get32(TIMER_CLO);
	curTick += interval;
	put32(TIMER_C1, curTick);
}

void handle_timer_irq()  {
	curTick += interval;
	put32(TIMER_C1, curTick);
	put32(TIMER_CS, TIMER_CS_M1);
	printf("Recieved timer interrupt\r\n");
}
