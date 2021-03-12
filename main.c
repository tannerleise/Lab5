/*
 * main.c
 *
 *  Created on: Jun 16, 2020
 *      Author: Tyler Davidson
 *     Updated: Aug, 13, 2020
 *    Modified: Sep 28, 2020
 * Modified by: Arielle Blum
 *
 */

#include "msp.h"
#include "i2c.h"
#include "stIMU.h"
#include "stdio.h"
#include "button.h"

/**
 * main.c
 */

volatile int state = 0;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    //disable interrupts
    __disable_irq();

//    config_button();
//    config_nvic_button();

    //enable interrupts
    __enable_irq();

    I2C_OPEN_STRUCT_TypeDef i2c_open_struct;

    i2c_open_struct.uca10 = 0;                              //no self 10-bit Address
    i2c_open_struct.ucsla10 = 0;                            //no 10-bit Addressing
    i2c_open_struct.ucmm = 0;                               //No Multi-Controller
    i2c_open_struct.ucmst = EUSCI_B_CTLW0_MST;              //Controller Mode
    i2c_open_struct.ucsselx = EUSCI_B_CTLW0_SSEL__SMCLK;    //SMCLK to be selected (3MHz)
    i2c_open_struct.ucbrx = 30;                             //Prescaler for Selected Clock.
                                                            //(100kHz)
     //This sets up the I2C driver to operate with the correct settings.
     //EUSCI_B0 uses P1.7 as SCL and P1.6 as SDA
     i2c_open(EUSCI_B0, &i2c_open_struct);

     config_LIS3MDL();

     int16_t mx, my, mz;
     uint8_t data;
     int i;

     //Neutral Position
     while(state == 0)
     {
         //delay
         for(i=0; i<200000; i++);
         i2c_start(EUSCI_B0, LIS3MDL_MAG_I2C_ADDRESS, READ, &data, 1, LIS3MDL_MAG_STATUS_REG);
         printf("status 1: %X\n",data);
         //delay
         for(i=0; i<1000; i++);
         mx = read_magnetometer_x();
         my = read_magnetometer_y();
         mz = read_magnetometer_z();
         printf("x: %d\n", mx);
         printf("y: %d\n", my);
         printf("z: %d\n", mz);
         printf("\n");
         printf("\n");
     }
     // Where does the 'state' get switched?
     // Students need to figure this out
     while(state == 1){
         //after the button is pressed, the IMU will no longer be communicating with the MSP
    }
}

/* Port1 ISR */
/*void PORT1_IRQHandler(void)
{
    volatile uint32_t j;

    //Check flag

    // Delay for switch debounce, can use __no_operation() instead if you want!
    for(j = 0; j < 100000; j++)

    //end of interrupt, what needs to happen here?
}*/
