/*
 * Pb_prog.h
 *
 *  Created on: May 18, 2022
 *      Author: Mohamed Ramadan
 */
 
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_init.h"
#include "Pb_int.h"
#include "Pb_private.h"
#include "Pb_conf.h"

#if Pb1_PORT == GPIO_PORTA
    #if Pb1_PIN > GPIO_PIN12
        #error  "for Pb1_PIN PA13 , PA14 , PA15 are forbidden pins"
    #endif
#endif

#if Pb1_PORT == GPIO_PORTB
    #if (Pb1_PIN >= GPIO_PIN2 && Pb1_PIN <= GPIO_PIN4)
        #error  "for Pb1_PIN PB2 , PB3 , PB4 are forbidden pins"
    #endif
#endif

#if Pb1_PORT == GPIO_PORTC
    #if Pb1_PIN < GPIO_PIN13
        #error  "for Pb1_PIN PC13 , PC14 , PC15 are only allowed pins"
    #endif
#endif

#if Pb2_PORT == GPIO_PORTA
    #if Pb2_PIN > GPIO_PIN12
        #error  "for Pb2_PIN PA13 , PA14 , PA15 are forbidden pins"
    #endif
#endif

#if Pb2_PORT == GPIO_PORTB
    #if (Pb2_PIN >= GPIO_PIN2 && Pb2_PIN <= GPIO_PIN4)
        #error  "for Pb2_PIN PB2 , PB3 , PB4 are forbidden pins"
    #endif
#endif

#if Pb2_PORT == GPIO_PORTC
    #if Pb2_PIN < GPIO_PIN13
        #error  "for Pb2_PIN PC13 , PC14 , PC15 are only allowed pins"
    #endif
#endif

#if Pb3_PORT == GPIO_PORTA
    #if Pb3_PIN > GPIO_PIN12
        #error  "for Pb3_PIN PA13 , PA14 , PA15 are forbidden pins"
    #endif
#endif

#if Pb3_PORT == GPIO_PORTB
    #if (Pb3_PIN >= GPIO_PIN2 && Pb1_PIN <= GPIO_PIN4)
        #error  "for Pb3_PIN PB2 , PB3 , PB4 are forbidden pins"
    #endif
#endif

#if Pb3_PORT == GPIO_PORTC
    #if Pb3_PIN < GPIO_PIN13
        #error  "for Pb3_PIN PC13 , PC14 , PC15 are only allowed pins"
    #endif
#endif

extern MGPIO_Config_t config_input_pin_pull_up   ;
extern MGPIO_Config_t config_input_pin_pull_down ;

void HPushBotton_voidPbIint (u8 A_u8PbID)
{
	switch (A_u8PbID)
	{                  /** make direction of Pb1 is input pull up*/
		case Pb1_ID :
			           #if Pb1_CONNECTION == INTERNAL_PULL_UP
			               MGPIO_voidInit(&config_input_pin_pull_up ,
				                           Pb1_PORT                 ,
									       Pb1_PIN                  ) ;
                       #elif Pb1_CONNECTION == INTERNAL_PULL_DOWN
		                     MGPIO_voidInit(&config_input_pin_pull_down ,
						                     Pb1_PORT                   ,
											 Pb1_PIN                    ) ;
                       #else
                             #error "select correct option of Pb1_CONNECTION"
                       #endif
					   break ;
					   
					   /** make direction of Pb2 is input pull up*/
		case Pb2_ID :
                       #if Pb1_CONNECTION == INTERNAL_PULL_UP
                           MGPIO_voidInit(&config_input_pin_pull_up ,
                                           Pb2_PORT                 ,
                       				       Pb2_PIN                  ) ;
                       #elif Pb1_CONNECTION == INTERNAL_PULL_DOWN
                             MGPIO_voidInit(&config_input_pin_pull_down ,
                       	                     Pb2_PORT                   ,
                       						 Pb2_PIN                    ) ;
                       #else
                             #error "select correct option of Pb1_CONNECTION"
                       #endif
					   break ;
					   
					   /** make direction of Pb3 is input pull up*/
		case Pb3_ID :
                       #if Pb1_CONNECTION == INTERNAL_PULL_UP
                           MGPIO_voidInit(&config_input_pin_pull_up ,
                                           Pb3_PORT                 ,
                       				       Pb3_PIN                  ) ;
                       #elif Pb1_CONNECTION == INTERNAL_PULL_DOWN
                             #define NOT_PRESSED 0
                             #define PRESSED     1
                             MGPIO_voidInit(&config_input_pin_pull_down ,
                       	                     Pb3_PORT                   ,
                       						 Pb3_PIN                    ) ;
                       #else
                             #error "select correct option of Pb1_CONNECTION"
                       #endif
                       					   break ;

		default     :  /** Error */
		               break ;
	}
}

u8 HPushBotton_u8PbStatus (u8 A_u8PbID)
{
	u8 L_u8PbStatus = NOT_PRESSED ;
	switch (A_u8PbID)
	{                  /**check Pb1 is pressed or not*/
		case Pb1_ID :  if (MGPIO_voidGetPinValue (Pb1_PORT , Pb1_PIN) == PRESSED)
		                {
							/**delay 20ms to detect bouncing*/
			                ARM_DELAY (DELAY_FOR_DEPOUNCING) ;
							
							/**check Pb1 is still pressed or not after debouncing*/
							if (MGPIO_voidGetPinValue (Pb1_PORT , Pb1_PIN) == PRESSED)
							{
								L_u8PbStatus = PRESSED ;
							}
		                }
					   break ;
					   
					   /**check Pb2 is pressed or not*/
		case Pb2_ID :  if (MGPIO_voidGetPinValue (Pb2_PORT , Pb2_PIN) == PRESSED)
		                {
							/**delay 20ms to detect bouncing*/
		                	ARM_DELAY (DELAY_FOR_DEPOUNCING) ;
							
							/**check Pb2 is still pressed or not after debouncing*/
							if (MGPIO_voidGetPinValue (Pb2_PORT , Pb2_PIN) == PRESSED)
							{
								L_u8PbStatus = PRESSED ;
							}
		                }
					   break ;
					   
					   /**check Pb3 is pressed or not*/
		case Pb3_ID :  if (MGPIO_voidGetPinValue (Pb3_PORT , Pb3_PIN) == PRESSED)
		                {
							/**delay 20ms to detect bouncing*/
			                ARM_DELAY (DELAY_FOR_DEPOUNCING) ;
							
							/**check Pb3 is still pressed or not after debouncing*/
							if (MGPIO_voidGetPinValue (Pb3_PORT , Pb3_PIN) == PRESSED)
							{
								L_u8PbStatus = PRESSED ;
							}
		                }
					   break ;
		default     :  /** Error */
		               break ;
	}
	/**delay 20ms to detect bouncing*/
	ARM_DELAY (DELAY_FOR_DEPOUNCING) ;
	return L_u8PbStatus ;
}
