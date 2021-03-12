/*
 * button.h
 *
 *  Created on: Sep 30, 2020
 *      Author:
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "msp.h"


/* Configure the S1 Button */
void config_button(void);

/* Configure NVIC for Interrupt Source */
void config_nvic_button(void);



#endif /* BUTTON_H_ */
