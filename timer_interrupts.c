/*
 * File:   timer_interrupts.c
 * Author: Soren
 *
 * Created on March 21, 2020, 12:34 PM
 */

#include "xc.h"
#include <stdint.h>

/*
 * PRx is the period, TMRx is the counter
 PRx = timer period/(prescaler*(Fosc/2))
 prescalers: 11 = 256, 10 = 64, 01 = 8, 00 = 1
 * 
 */
void timer_enable(int numberen, uint16_t bits) {
    if (numberen == 1){
        T1CON = bits;
        TMR1 = 0x0000;
    }
    else if (numberen == 2){
        T2CON = bits;
        TMR2 = 0x0000;
    }
}

void timer_interrupt_setup(int timerset, int prio){
    if (timerset == 1){
        IPC0bits.T1IP = prio;
        IFS0bits.T1IF = 0;
        IEC0bits.T1IE = 1;
    }
    else if (timerset == 2){
        IPC1bits.T2IP = prio;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
}


void timer_period(int numberprd, int bits2){
    if (numberprd == 1){
        PR1 = bits2;
    }
    else if (numberprd == 2){
        PR2 = bits2;
    }
}

void timer_prescale(int numberpre, int bits){
    if (numberpre == 1){
        T1CONbits.TCKPS = bits;
    }
    else if (numberpre == 2){
        T2CONbits.TCKPS = bits;
    }
}
