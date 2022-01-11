#ifndef TIMER_INTERRUPT_H
#define TIMER_INTERRUPT_H

void timer_enable(int,uint16_t);
void timer_interrupt_setup(int,int);
void timer_period(int, int);
void timer_prescale(int,int);

#endif
