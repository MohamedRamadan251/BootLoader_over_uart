/*
 * Memory_Flash_prog.c
 *
 *  Created on: May 15, 2024
 *      Author: Mohammed Ramadan
 */



#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../RCC/RCC_int.h"

#include "Memory_Flash_register.h"
#include "Memory_Flash_private.h"
#include "Memory_Flash_init.h"

void MFMI_voidInit (void)
{
	MRCC_voidInit ( );
	MRCC_voidEnablePerephiralClock (RCC_AHB1LPENR, RCC_EN_FLITFLPEN);
}

void MFMI_voidSectorErase (u8 A_u8SectorNo)
{
	/*wait until busy flag is cleared*/
	while (READ_BIT(FMI->SR , SR_BSY) == 1) ;
	/*unlock the flash registers*/
	if (READ_BIT(FMI->CR , CR_LOCK) == 1)
	{
		FMI->KEYR = KEY1 ;
		FMI->KEYR = KEY2 ;
	}
	/*select sector number to erase*/
	FMI->CR &= ((u32)((0b1111) << 3)) ;
	FMI->CR |= ((u32)((A_u8SectorNo) << 3)) ;
	/*select erase operation*/
	SET_BIT(FMI->CR , CR_SER) ;
	/*start erase operation*/
	SET_BIT(FMI->CR , CR_STRT) ;
	/*wait until busy flag is cleared*/
	while (READ_BIT(FMI->SR , SR_BSY) == 1) ;
	/*clear EOP flag*/
	SET_BIT(FMI->SR , SR_EOP) ;
	/*deactivate erase operation*/
	CLR_BIT(FMI->CR , CR_SER) ;
}

void MFMI_voidEraseApp (u8 A_u8AppStartSector , u8 A_u8AppEndSector)
{
	if (A_u8AppStartSector != SECTOR_0)
	{
		for (u8 L_u8Iterator = A_u8AppStartSector; L_u8Iterator <= A_u8AppEndSector ; L_u8Iterator ++)
		{
			MFMI_voidSectorErase (L_u8Iterator) ;
		}
	}
}

void MFMI_voidFlashWrite (u32  A_u32StartAddress ,
		                 u8   A_u8ProgramSize   ,
		                 u32* A_pu32Data        ,
						 u32  A_u32Length)
{
	/*wait until busy flag is cleared*/
	while (READ_BIT(FMI->SR , SR_BSY) == 1) ;
	/*unlock the flash registers*/
	if (READ_BIT(FMI->CR , CR_LOCK) == 1)
	{
		FMI->KEYR = KEY1 ;
		FMI->KEYR = KEY2 ;
	}
	/*select program size*/
	FMI->CR &= ((u32)((0b11) << 8)) ;
	FMI->CR |= ((u32)((A_u8ProgramSize) << 8)) ;
	/*select programming operation*/
	SET_BIT(FMI->CR , CR_PG) ;
	switch (A_u8ProgramSize)
	{
	case PROGRAM_SIZE_1_BYTE :
		for (u8 L_u8Iterator = 0 ; L_u8Iterator < A_u32Length ; L_u8Iterator ++)
		{
			*((volatile u8*)A_u32StartAddress) = (u8)A_pu32Data [L_u8Iterator] ;
			A_u32StartAddress ++ ;
			/*wait until busy flag is cleared*/
			while (READ_BIT(FMI->SR , SR_BSY) == 1) ;
			/*clear EOP flag*/
			SET_BIT(FMI->SR , SR_EOP) ;
		}
		break ;
	case PROGRAM_SIZE_2_BYTES :
		for (u8 L_u8Iterator = 0 ; L_u8Iterator < A_u32Length ; L_u8Iterator ++)
		{
			*((volatile u16*)A_u32StartAddress) = (u16)A_pu32Data [L_u8Iterator] ;
			A_u32StartAddress += 2 ;
			/*wait until busy flag is cleared*/
			while (READ_BIT(FMI->SR , SR_BSY) == 1) ;
			/*clear EOP flag*/
			SET_BIT(FMI->SR , SR_EOP) ;
		}
		break ;
	case PROGRAM_SIZE_4_BYTES :
		for (u8 L_u8Iterator = 0 ; L_u8Iterator < A_u32Length ; L_u8Iterator ++)
		{
			*((volatile u32*)A_u32StartAddress) = (u32)A_pu32Data [L_u8Iterator] ;
			A_u32StartAddress += 4 ;
			/*wait until busy flag is cleared*/
			while (READ_BIT(FMI->SR , SR_BSY) == 1) ;
			/*clear EOP flag*/
			SET_BIT(FMI->SR , SR_EOP) ;
		}
		break ;
	}
	/*deactivate programming operation*/
	CLR_BIT(FMI->CR , CR_PG) ;
}

