/*
 * File:   external_interrupts.c
 * Author: Soren
 *
 * Created on March 21, 2020, 7:55 PM
 */


#include "xc.h"

void ext_interr_setup(void){
    RPINR0bits.INT1R = 0b0110111; //RP55 011 0111
}

void ext_interr_enable (int internum, int prio, int edge){
    if (internum == 0){
        
    }
    else if (internum == 1){
        IFS1bits.INT1IF = 0;
        IEC1bits.INT1IE = 1;
        IPC5bits.INT1IP = prio;
        INTCON2bits.INT1EP = edge;
    }
}
