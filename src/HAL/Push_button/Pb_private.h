/*
 * Pb_private.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohamed Ramadan
 */

#ifndef HAL_PUSH_BOTTON_PB_PRIVATE_H
#define HAL_PUSH_BOTTON_PB_PRIVATE_H

/**
* IDs of Pbs 
*/
#define Pb1_ID   1
#define Pb2_ID   2
#define Pb3_ID   3

/**
* Direction of Pb
*/
#define Pb_INPUT 0

/**
* Delay to detect pouncing
*/
#define DELAY_FOR_DEPOUNCING 20

/*define statues of connection of Push butoon */
#define INTERNAL_PULL_UP   1
#define INTERNAL_PULL_DOWN 2

/**
* Statues of Pb
*/

#define NOT_PRESSED 1
#define PRESSED     0

/*delay function*/
#define ARM_DELAY(d)   do{unsigned long int i=(d * 5000); while(i--){asm("nop");}}while(0)

#endif /* HAL_PUSH_BOTTON_PB_PRIVATE_H */
