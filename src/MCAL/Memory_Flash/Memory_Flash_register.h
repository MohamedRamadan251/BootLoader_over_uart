/*
 * Memory_Flash_register.h
 *
 *  Created on: May 15, 2024
 *      Author: Mohammed Ramadan
 */

#ifndef MCAL_MEMORY_FLASH_MEMORY_FLASH_REGISTER_H_
#define MCAL_MEMORY_FLASH_MEMORY_FLASH_REGISTER_H_

/*define base address of Flash Memory Interface (FMI)*/
#define FMI_BASE_ADDRESS   0x40023C00

/*registers of FMIx*/
typedef struct
{
	volatile u32 ACR     ;
    volatile u32 KEYR    ;
    volatile u32 OPTKEYR ;
    volatile u32 SR      ;
    volatile u32 CR      ;
    volatile u32 OPTCR   ;
}FMI_MemoryMapType;

/*define FMI*/
#define FMI ((volatile FMI_MemoryMapType *)(FMI_BASE_ADDRESS))



#endif /* MCAL_MEMORY_FLASH_MEMORY_FLASH_REGISTER_H_ */
