#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

unsigned char counter = 0; //this will be the counter to count the number of interrupts for timer1 module
void main(void) {
    TRISB0 = 0; //RB0 OUTPUT
    RB0 = 0; // RB0 ISN'T WORKING (GETS NO VOLTAGE)
    TMR1IE = 1; //TIMER 1 INTERRUPT ENABLE (GO BACK TO THE INTERRUPT TUTORIAL)
            PEIE = 1; //PERIPHERAL INTERRUPT ENABLE BIT
            GIE = 1; //GLOBAL INTERRUPT ENABLE BIT
            //THIS MEANS YOU ENABLED TIMER 1 INTERRUPT AND ONCE THERE IS AN OVERFLOW IN TIMER 1 MODULE IT WILL GENERATE
            //AN INTERRUPT SIGNAL THAT WILL REACH THE CPU(AKA PIC16F877A)
           
    //[Configure timer module to work on timer mode (because timer has 2 modes : timer mode , counter mode)]
    //open pic16F877A datasheet and go to timer1 module chapter 6  
            
    //first clear the timer1 module to start counting from 0
    TMR1 = 15536;
    TMR1CS = 0; // SELECT LOCAL CLOCK AS TMR1 CLOCK SOURCE
    T1CKPS0 = 0;//Timer1 Input Clock Prescaler Select bits, 0 0 = 1:1 prescale value
    T1CKPS1 = 0; 
     //prescaler is used to divide the 4MHZ freq.
    //TURN ON TIMER1 MODULE
    TMR1ON = 1;
    //Write the system's main routine (infinite while loop)
    while(1){
        
    }
    return;
}
//Write the ISR INTERRUPT HANDLER
void __interrupt() ISR(){
    if(TMR1IF){
        TMR1 = 15536;
        counter++;
        if(counter == 20){
            RB0 = ~RB0; //this means toggle and it reverses it's state to 1 until you get out of if and it gets it back to 0
            counter = 0;
        }
        TMR1IF = 0; //clearing the interrupt flag to 0 THIS IS VERY IMPORTANT
    }
}
