/*
 * File:   pwm_setup.c
 * Author: Soren
 *
 * Created on March 22, 2020, 5:06 PM
 */

#include "xc.h"


//dont forget about the current MIPS which is 40 MIPS
void pwm_setup(void) {
/* Set PWM Period on Primary Time Base */
PTPER = 40000;
/* Set Phase Shift */
PHASE1 = 0;
PHASE2 = 100;
PHASE3 = 200;
/* Set Duty Cycles */
PDC1 = 900;
PDC2 = 200;
PDC3 = 400;
/* Set Dead Time Values */
DTR1 = DTR2 = DTR3 = 0;
ALTDTR1 = ALTDTR2 = ALTDTR3 = 0;
/* Set PWM Mode to Redundant */
IOCON1 = IOCON2 = IOCON3 = 0xC400;
/* Set Primary Time Base, Edge-Aligned Mode and Independent Duty Cycles */
PWMCON1 = PWMCON2 = PWMCON3 = 0x0000;
PWMCON1bits.IUE = 1;
/* Configure Faults */
FCLCON1 = FCLCON2 = FCLCON3 = 0x0003;
/* 1:1 Prescaler */
PTCON2 = 0x0000;
/* Enable PWM Module */
PTCONbits.EIPU  =1;
PTCON = 0x8000;
}

void updatePWM1(int dc1){
    PDC1 = dc1;
}
