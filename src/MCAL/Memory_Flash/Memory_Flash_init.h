/*
 * Memory_Flash_init.h
 *
 *  Created on: May 15, 2024
 *      Author: Mohammed Ramadan
 */

#ifndef MCAL_MEMORY_FLASH_MEMORY_FLASH_INIT_H_
#define MCAL_MEMORY_FLASH_MEMORY_FLASH_INIT_H_

#define SECTOR_0  0b0000
#define SECTOR_1  0b0001
#define SECTOR_2  0b0010
#define SECTOR_3  0b0011
#define SECTOR_4  0b0100
#define SECTOR_5  0b0101
#define SECTOR_6  0b0110
#define SECTOR_7  0b0111


#define PROGRAM_SIZE_1_BYTE    0b00  /*to write byte by byte*/
#define PROGRAM_SIZE_2_BYTES   0b01  /*to write halfword by halfword*/
#define PROGRAM_SIZE_4_BYTES   0b10  /*to write word by word*/

void MFMI_voidInit (void) ;

void MFMI_voidSectorErase (u8 A_u8SectorNo) ;

void MFMI_voidEraseApp (u8 A_u8AppStartSector , u8 A_u8AppEndSector) ;

void MFMI_voidFlashWrite (u32  A_u32StartAddress,
		                 u8   A_u8ProgramSize   ,
		                 u32* A_pu32Data        ,
						 u32  A_u32Length)      ;



#endif /* MCAL_MEMORY_FLASH_MEMORY_FLASH_INIT_H_ */
