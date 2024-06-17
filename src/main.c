


#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/Memory_Flash/Memory_Flash_init.h"
#include "MCAL/UART/UART_interface.h"
#include "HAL/BootLoader/BootLoader_init.h"
#include "HAL/BootLoader/BootLoader_öAppCode.h"
#include "HAL/LED/LED_int.h"
#include "HAL/Push_button/Pb_int.h"

extern USART_InitType MUART_Init ;
extern USART_ClockInitTypeDef MUART_clock ;

u8  G_u8Buffer [43] ;
u16 G_u8Index = 0 ;
u8 G_u8FlagForFlash = 1 ;
u32 G_u32CRC1 [300] ;
u32 G_u32CRC2 [300] ;
u16 G_u16CRCIterator ;
void HEX (void);
void HEX (void)
{
	G_u8Buffer [G_u8Index] = MUART_u8ReadDataRegister(UART1);
	if (G_u8Buffer [G_u8Index-1] == '\r'&&G_u8Buffer [G_u8Index] == '\n')
	{
		G_u8Index =  0 ;
		if (G_u8Buffer [7] == '0'&&G_u8Buffer [8] == '0')
		{
			HBootLoader_voidCalcCRCOfRecivedData(G_u8Buffer , &G_u32CRC2 [G_u16CRCIterator++]) ;
			HBootLoader_voidParseDataAndFlash(G_u8Buffer) ;
			HLED_voidLedToggle(LED1_ID) ;
		}
		else if (G_u8Buffer [7] == '0'&&G_u8Buffer [8] == '1')
		{
			G_u8FlagForFlash = 0 ;
		}
	}
	else
	{
		G_u8Index ++ ;
	}
}

void main (void)
{
	u16 size = sizeof (str) / sizeof (str [0]) ;
	u8 L_u8CRCResult = 0 ;
	u8 L_u8AppValitiy = 0 ;

	HBootLoader_voidInitBooting() ;
	MFMI_voidEraseApp(SECTOR_2 , SECTOR_7) ;

	MUART_voidInit(&MUART_Init , &MUART_clock , UART6) ;
	MUART_voidEnable (UART6) ;

	MUART_voidInit(&MUART_Init , &MUART_clock , UART1) ;
	MUART1_voidSetCallBack(HEX) ;
	MUART_RxIntSetStatus (UART1 , ENABLE) ;
	MUART_voidEnable(UART1) ;

	HLED_voidLedInitial(LED1_ID) ;
	HLED_voidLedInitial(LED2_ID) ;
	HPushBotton_voidPbIint(Pb1_ID) ;

	for (u16 i = 0 ; i < size ; i ++)
	{
		HBootLoader_voidParseCRC(str [i] , &G_u32CRC1 [i]) ;
	}

	while (G_u8FlagForFlash) ;

	L_u8CRCResult = HBootLoader_u8CheckCRC (G_u32CRC1 ,G_u32CRC2 ,size) ;
	L_u8AppValitiy = HBootLoader_u8CheckAppVaildity(0x08008000) ;

	if (L_u8CRCResult == 1 || L_u8AppValitiy == 1)
	{
		HLED_voidLedOn(LED1_ID) ;
	}
	else
	{
		HLED_voidLedOff(LED1_ID) ;
		HLED_voidLedOn(LED2_ID) ;
	}

	while (1)
	{
		if (L_u8CRCResult == 0 && L_u8AppValitiy == 0)
		{
			if (HPushBotton_u8PbStatus(Pb1_ID) == PRESSED)
			{
				HLED_voidLedOff(LED2_ID) ;
				HBootLoader_voidJumpToAddress(0x08008000) ;
			}
		}
	}
}

