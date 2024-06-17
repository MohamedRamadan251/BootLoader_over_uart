/*
 * BootLoader_prog.c
 *
 *  Created on: May 17, 2024
 *      Author: Mohammed Ramadan
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/Memory_Flash/Memory_Flash_init.h"

#include "BootLoader_init.h"

void HBootLoader_voidInitBooting (void)
{
	MFMI_voidInit() ;
}
static u32 HBootLoader_u32ASSCIIToHex (u32 A_u32Asscii)
{
	u32 L_u32HexValue = 0 ;
	if (A_u32Asscii >= '0' && A_u32Asscii <= '9')
	{
		L_u32HexValue = A_u32Asscii - '0' ;
	}
	else if (A_u32Asscii >= 'A' && A_u32Asscii <= 'F')
	{
		L_u32HexValue = A_u32Asscii - 55 ;
	}
	return L_u32HexValue ;
}

void HBootLoader_voidParseDataAndFlash (const u8 A_Pu8Data [])
{
	u32 L_u32LowCounter  ;
	u32 L_u32HighCounter ;
    u32 L_u32Counter     ;

	u32 L_u32AddressDigit0  ;
	u32 L_u32AddressDigit1  ;
	u32 L_u32AddressDigit2  ;
	u32 L_u32AddressDigit3  ;
	u32 L_u32Address        ;

	u32 L_u32DataDigit0     ;
	u32 L_u32DataDigit1     ;
	u32 L_u32DataDigit2     ;
	u32 L_u32DataDigit3     ;
    u32 R_u32Buffer [100]   ;

	/*parsing counter from hex record*/
	L_u32HighCounter = HBootLoader_u32ASSCIIToHex (A_Pu8Data [1]) ;
	L_u32LowCounter = HBootLoader_u32ASSCIIToHex (A_Pu8Data [2]) ;
	L_u32Counter = (L_u32HighCounter << 4) | L_u32LowCounter ;

	/*parsing address from hex record*/
	L_u32AddressDigit0 = HBootLoader_u32ASSCIIToHex (A_Pu8Data [3]) ;
	L_u32AddressDigit1 = HBootLoader_u32ASSCIIToHex (A_Pu8Data [4]) ;
	L_u32AddressDigit2 = HBootLoader_u32ASSCIIToHex (A_Pu8Data [5]) ;
	L_u32AddressDigit3 = HBootLoader_u32ASSCIIToHex (A_Pu8Data [6]) ;
	L_u32Address = 0x8000000 | (L_u32AddressDigit0 << 12) |
			                   (L_u32AddressDigit1 << 8)  |
							   (L_u32AddressDigit2 << 4)  |
							   (L_u32AddressDigit3 << 0)  ;

	/*parsing data from hex record*/
	for (u32 L_u32Iterator = 0 ; L_u32Iterator < L_u32Counter/2 ; L_u32Iterator ++)
	{
		L_u32DataDigit0 = HBootLoader_u32ASSCIIToHex (A_Pu8Data [(L_u32Iterator * 4 ) + 9 ]) ;
		L_u32DataDigit1 = HBootLoader_u32ASSCIIToHex (A_Pu8Data [(L_u32Iterator * 4 ) + 10]) ;
		L_u32DataDigit2 = HBootLoader_u32ASSCIIToHex (A_Pu8Data [(L_u32Iterator * 4 ) + 11]) ;
		L_u32DataDigit3 = HBootLoader_u32ASSCIIToHex (A_Pu8Data [(L_u32Iterator * 4 ) + 12]) ;
		R_u32Buffer [L_u32Iterator] =(L_u32DataDigit2 << 12) |
				                     (L_u32DataDigit3 << 8)  |
				                     (L_u32DataDigit0 << 4)  |
				                     (L_u32DataDigit1 << 0)  ;
	}

	MFMI_voidFlashWrite(L_u32Address ,
			PROGRAM_SIZE_2_BYTES     ,
			R_u32Buffer              ,
			L_u32Counter/2     )     ;
}

void HBootLoader_voidJumpToAddress (u32 A_u32AppAddress)
{
	__asm volatile ("movs  r0, %0\n" : : "r" (A_u32AppAddress));
	*((volatile u32 *)(0xE000ED08)) = A_u32AppAddress ;
	__asm volatile ("ldr  sp, [r0]\n") ;
	__asm volatile ("ldr  r0, [r0,#4]\n") ;
	__asm volatile ("bx        r0\n") ;
}

void HBootLoader_voidParseCRC (const u8 A_Pu8Data [] , u32 *A_u32CRC)
{
	u32 L_u32LowCounter  ;
	u32 L_u32HighCounter ;
	u32 L_u32Counter     ;

	u32 L_u32LowCRC  ;
	u32 L_u32HighCRC ;

	/*parsing counter from hex record*/
	L_u32HighCounter = HBootLoader_u32ASSCIIToHex (A_Pu8Data [1]) ;
	L_u32LowCounter = HBootLoader_u32ASSCIIToHex (A_Pu8Data [2]) ;
	L_u32Counter = (L_u32HighCounter << 4) | L_u32LowCounter ;

	/*parsing CRC from hex record*/
	L_u32HighCRC = HBootLoader_u32ASSCIIToHex (A_Pu8Data [(L_u32Counter*2)+9]) ;
	L_u32LowCRC = HBootLoader_u32ASSCIIToHex (A_Pu8Data [(L_u32Counter*2)+10]) ;
	*A_u32CRC = (L_u32HighCRC << 4) | L_u32LowCRC ;
}

void HBootLoader_voidCalcCRCOfRecivedData (const u8 A_Pu8Data [] , u32 *A_u32CRC)
{
	u32 L_u32LowNibble  ;
	u32 L_u32HighNibble ;
	u32 L_u32Byte = 0   ;
	u32  L_u32Indexes     ;

	u32 L_u32LowCounter  ;
	u32 L_u32HighCounter ;
	u32 L_u32Counter     ;

	/*parsing counter from hex record*/
	L_u32HighCounter = HBootLoader_u32ASSCIIToHex (A_Pu8Data [1]) ;
	L_u32LowCounter = HBootLoader_u32ASSCIIToHex (A_Pu8Data [2]) ;
	L_u32Counter = (L_u32HighCounter << 4) | L_u32LowCounter ;

	L_u32Indexes = L_u32Counter*2 + 8 ;

	for (u32 i = 1 ; i < L_u32Indexes ; i+=2)
	{
		L_u32HighNibble = HBootLoader_u32ASSCIIToHex (A_Pu8Data [i]) ;
		L_u32LowNibble = HBootLoader_u32ASSCIIToHex (A_Pu8Data [i+1]) ;
		L_u32Byte += ((L_u32HighNibble << 4) | L_u32LowNibble) ;
	}
	L_u32Byte ^= 0xff ;
	L_u32Byte ++ ;
	L_u32Byte &= 0xff ;
	*A_u32CRC = L_u32Byte ;
}

u8 HBootLoader_u8CheckCRC (const u32 A_u32CRC1 [] ,
		                   const u32 A_u32CRC2 [] ,
				    			 u32 A_u32Size)
{
	for (u32 i = 0 ; i < A_u32Size ; i ++)
	{
		if (A_u32CRC1 [i] != A_u32CRC2 [i])
		{
			return 1 ;
		}
	}
	return 0 ;
}

u8 HBootLoader_u8CheckAppVaildity (u32 A_u32Address)
{
	u32 *L_u32PApp = (u32*) A_u32Address ;
	/*check value of sp*/
	if ((L_u32PApp [0] == 0xffffffff                ) ||
	    ((L_u32PApp [0] &  0xfff00000) != 0x20000000)	)
	{
		return 1;
	}
	/*check value of reset handler*/
	if ((L_u32PApp [1] == 0xffffffff                ) ||
	    ((L_u32PApp [1] &  0x00000001) != 0x00000001)	)// for thumb bit
	{
		return 1;
	}
	return 0 ;
}
