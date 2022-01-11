#define FCY 4000000UL

#include <xc.h>
#include <dsp.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcc_generated_files/system.h"
#include "timer_interrupts.h"
#include "external_interrupts.h"
#include "pwm_setup.h"
#include "adc.h"
#include "uart_funcs.h"
#include "uart_init.h"
#include "SPI_setup.h"

//fractional abcCoefficient[3] __attribute__ ((section(".xbss, bss, xmemory")));
fractional controlHistory[3] __attribute__ ((section(".ybss, bss, ymemory")));


int count = 0;
unsigned int ADCValue = 0;
int j = 0;
int positionreadings[16];

unsigned int recv_position = 0;  //stores what SPI reads NOW
void __attribute__ ((interrupt,no_auto_psv)) _T1Interrupt(void){
    //_LATC5 = ~_LATC5;
    //_LATC6 = ~_LATC6;
    _LATC4 = ~_LATC4;
   // j++;
  // printf("ADC value:%d\n", ADCValue);
    IFS0bits.T1IF = 0;
}
void __attribute__ ((interrupt,no_auto_psv)) _T2Interrupt(void){
    _LATC5 = ~_LATC5;
    _LATC6 = ~_LATC6;
    IFS0bits.T2IF = 0;
}

void __attribute__ ((interrupt,no_auto_psv)) _U2TXInterrupt(void){

    IFS1bits.U2TXIF = 0;    //reset interrupt flag
}

void __attribute__ ((interrupt,no_auto_psv)) _INT1Interrupt(void){
    _LATC4 = ~_LATC4;
    IFS1bits.INT1IF = 0;
}

void Delay_us(unsigned int delay){
    int i =0;
    for ( i = 0; i < delay; i++){
        __asm__ volatile ("repeat #39");
        __asm__ volatile ("nop");
    }
}
void timer1setup(){
    T1CON = 0x0000;
    TMR1 = 0x0000;
   // PR1 = 15625;
    PR1 = 10;
    //T1CONbits.TCKPS = 0b0011;
    T1CONbits.TCKPS = 0b0000;
    //interrupts
    IPC0bits.T1IP = 7;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    
    //turn it on
    T1CONbits.TON = 1;
}
void timer2setup(){
    T2CON = 0x0000;
    TMR2 = 0x0000;
    PR2 = 15625;
    T2CONbits.TCKPS = 0b0011;
    
    //interrupts
    IPC1bits.T2IP = 7;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    
    //turn it on
    T2CONbits.TON = 1;
}
unsigned int readSPI(void);

int main(void)
{
     __C30_UART = 2;
    
   // int ADCValue = 0;
    // initialize the device
    SYSTEM_Initialize();
     UART_initing();
     UART2_start();
    _TRISC4 = 0;
    _TRISB8 = 0;
    _TRISC5 = 0;
    _TRISC6 = 0;
    _TRISC13 = 0;
    _TRISC7 = 1;
    _TRISC8 = 1;
    _TRISC9 = 1;
    _TRISG8 = 0;
    _TRISG6 = 1;
    _TRISA9 = 1;    //sdi input
    _LATC5 = 0;  
    _LATC6 = 1;
    _LATG8 = 1;
    _LATC4 = 1;
    _LATC13 = 1;    //high initially
    _LATB8 = 1;
    
   // timer1setup();
   // timer2setup();
    SPI_init();
 
    
    j = 0;

    initadc1();
 
    printf("Hello!\n");
    while (1)
    {
        //printf("hi!\n");
        _LATB8 = !_LATB8;
        __delay_ms(1000);
  
        printf("%u\n",(unsigned int)(((float)readSPI()/4095)*360));
       // printf("%u\n", readSPI());
           /*
       // updatePWM1(600);
       // j++;
        
       // AD1CON1bits.DONE = 0;
        AD1CON1bits.SAMP = 1;   //start sampling
        Delay_us(10);
        AD1CON1bits.SAMP = 0;
        
        while (AD1CON1bits.DONE == 0){};
       // _LATC4 = 0;
        ADCValue = ADC1BUF0;
        if (ADCValue < 512){
           // 
            printf("ADC:%d\n",ADCValue);
        }
     //   printf("adc:%d\n",ADCValue);
        //updatePWM1(ADCValue);
      //  timer_period(2,ADCValue);   
     */
    }
    return 1; 
}

unsigned int readSPI(){
    //need to add Csn pulses before reading. I think this will trigger the sensor to release data
    //i think it also needs to clear the recv bit after or before reading so dspic can work
    //i think at FCY of 4M, since each cycle is 250 ns, i dont have to put a delay. The instruction cycles will cover the needed delay by the encoder
    
   //Csn pin for encoder has to be active for at least 500ns
    _LATC13 = 1;

    _LATC13 = 0;
     __delay_us(1);       
    //then activate clock signal after the CSnpulse but there must be some delay of 500ns
    //i dont think the delay is needed because writing to the SPI1BUF register may take at least 1 cycle...
    SPI1BUF = 0x0000;   //starts the clock signal
    //wait while the receive buffer is filled
    while(SPI1STATbits.SPIRBF == 0b0){}
    __delay_us(1);  
   // _LATC13 = 1;
    recv_position =  SPI1BUF;    //copy only the lower twelve bits
    recv_position =  0x0FFF & recv_position;
   // SPI1STATbits.SPIRBF = 0b0;
   
    return  recv_position;
   
}
/**
 End of File
*/

