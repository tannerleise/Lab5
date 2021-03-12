/*
 * button.c
 *
 *  Created on: Sep 30, 2020
 *      Author:
 */

#include "button.h"

/* Configure the S1 Button */
void config_button(void)
{
    //config S1 on the MSP432P401R SimpleLink Launchpad as a button interrupt
    //set up Button Interrupt

    P1->DIR &= ~BIT1; //sets p1.1 as input
    P1->REN |= BIT1; //uses pullup resistor configuration
    P1->OUT |= BIT1;

    P1->SEL0 &= ~BIT1; //0000000000 GENERAL IO PIN CONFIG
    P1->SEL1 &= ~BIT1;// 0000000000
    P1->DIR &= ~BIT1; //sets p1.1 as input

    P1->REN |= BIT1; //uses pullup resistor config
    P1->IES |= BIT1; //Falling edge interrupt trigger
    P1->IFG &= ~BIT1; //Clears initial interrupt flag
    P1->IE |= BIT1; //Enables interrupt functionality for P1.1
}

/* Configure NVIC for Interrupt Source */
void config_nvic_button(void)
{
    //configure the NVIC for the button interrupt source
    __NVIC_EnableIRQ(PORT1_IRQn);
}


