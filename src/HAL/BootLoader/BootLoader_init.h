/*
 * BootLoader_init.h
 *
 *  Created on: May 17, 2024
 *      Author: Mohammed Ramadan
 */

#ifndef HAL_BOOTLOADER_BOOTLOADER_INIT_H_
#define HAL_BOOTLOADER_BOOTLOADER_INIT_H_

/*steps for flashing new app
 * 1-call HBootLoader_voidInitBooting function to init FMI,RCC
 * 2-call MFMI_voidEraseApp(first sector, second sector) to erase app area
 * 3-call HBootLoader_voidParseDataAndFlash to flash your app
 */

/*steps for jumping to new app
 * 1-edit boundries of linker script of new app
 * 2-define Vector Table base offset of new app from system_stm32f4xx.c file
 * 3-call HBootLoader_voidJumpToAddress(address)
 * */
void HBootLoader_voidInitBooting (void) ;

void HBootLoader_voidParseDataAndFlash (const u8 A_Pu8Data []) ;

void HBootLoader_voidJumpToAddress (u32 A_u32Address) ;

void HBootLoader_voidParseCRC (const u8 A_Pu8Data [] , u32 *A_u32CRC) ;

void HBootLoader_voidCalcCRCOfRecivedData (const u8 A_Pu8Data [] , u32 *A_u32CRC) ;

u8 HBootLoader_u8CheckCRC (const u32 A_u32CRC1 [] ,
		                   const u32 A_u32CRC2 [] ,
				    			 u32 A_u32Size) ;

u8 HBootLoader_u8CheckAppVaildity (u32 A_u32Address) ;

#endif /* HAL_BOOTLOADER_BOOTLOADER_INIT_H_ */
