/*
 * Pb_conf.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohamed Ramadan
 */

#ifndef HAL_PUSH_BOTTON_PB_CONF_H
#define HAL_PUSH_BOTTON_PB_CONF_H
/**
      ** Connections **
	  
 *Options of Pbx_PORT are :
            *GPIO_PORTA
			*GPIO_PORTB
			*GPIO_PORTC
			*GPIO_PORTD

 *Options of Pbx_PIN are :
            *GPIO_PIN0
			*GPIO_PIN1
			*GPIO_PIN2
			*GPIO_PIN3
			*GPIO_PIN4
			*GPIO_PIN5
			*GPIO_PIN6
			*GPIO_PIN7
			*GPIO_PIN8
			*GPIO_PIN9
			*GPIO_PIN10
			*GPIO_PIN11
			*GPIO_PIN12
			*GPIO_PIN13
			*GPIO_PIN14
			*GPIO_PIN15
			
	where x is the ID of Pb "x = 1 or 2 or 3"
*/

/**
 * Options of A_u8Pb_ID 
        *Pb1_ID 
		*Pb2_ID 
		*Pb3_ID 
*/

/*
 * "for Pb_PIN PA13 , PA14 , PA15 are forbidden pins"
 * "for Pb_PIN PB2 , PB3 , PB4 are forbidden pins"
 * "for Pb_PIN PC13 , PC14 , PC15 are only allowed pins"
 */

/**
 * connection of Pb 1
*/
#define Pb1_PORT    GPIO_PORTB
#define Pb1_PIN     GPIO_PIN5

/**
 * connection of Pb 2
*/
#define Pb2_PORT    GPIO_PORTB
#define Pb2_PIN     GPIO_PIN1

/**
 * connection of Pb 3
*/
#define Pb3_PORT    GPIO_PORTA
#define Pb3_PIN     GPIO_PIN2

/**
 *TYPE of connection
 *Options
 **INTERNAL_PULL_UP
 **INTERNAL_PULL_DOWN
 */
#define Pb1_CONNECTION  INTERNAL_PULL_UP
#define Pb2_CONNECTION  INTERNAL_PULL_UP
#define Pb3_CONNECTION  INTERNAL_PULL_UP


#endif /* HAL_PUSH_BOTTON_PB_CONF_H */
