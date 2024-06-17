/*
 * Memory_Flash_private.h
 *
 *  Created on: May 15, 2024
 *      Author: Mohammed Ramadan
 */

#ifndef MCAL_MEMORY_FLASH_MEMORY_FLASH_PRIVATE_H_
#define MCAL_MEMORY_FLASH_MEMORY_FLASH_PRIVATE_H_

#define START_OF_SECTOR_0    0x08000000
#define START_OF_SECTOR_1    0x08004000
#define START_OF_SECTOR_2    0x08008000
#define START_OF_SECTOR_3    0x0800C000
#define START_OF_SECTOR_4    0x08010000
#define START_OF_SECTOR_5    0x08020000
#define START_OF_SECTOR_6    0x08040000
#define START_OF_SECTOR_7    0x08060000

#define END_OF_SECTOR_0    0x08003FFF
#define END_OF_SECTOR_1    0x08007FFF
#define END_OF_SECTOR_2    0x0800BFFF
#define END_OF_SECTOR_3    0x0800FFFF
#define END_OF_SECTOR_4    0x0801FFFF
#define END_OF_SECTOR_5    0x0803FFFF
#define END_OF_SECTOR_6    0x0805FFFF
#define END_OF_SECTOR_7    0x0807FFFF

/*******************************************************/
/*      Flash access control register (FLASH_ACR)      */
/*******************************************************/
#define ACR_LATENCY0     0
#define ACR_LATENCY1     1
#define ACR_LATENCY2     2
#define ACR_LATENCY3     3
#define ACR_PRFTEN       8
#define ACR_ICEN         9
#define ACR_DCEN         10
#define ACR_ICRST        11
#define ACR_DCRST        12
/*******************************************************/
/*      Flash key register (FLASH_KEYR)                */
/*******************************************************/
#define KEY1  0x45670123
#define KEY2  0xCDEF89AB
/*******************************************************/
/*      Flash option key register (FLASH_OPTKEYR)      */
/*******************************************************/
#define OPTKEY1  0x08192A3B
#define OPTKEY2  0x4C5D6E7F
/*******************************************************/
/*      Flash status register (FLASH_SR)               */
/*******************************************************/
#define SR_EOP      0
#define SR_OPERR    1
#define SR_WRPERR   4
#define SR_PGAERR   5
#define SR_PGPERR   6
#define SR_PGSERR   7
#define SR_RDERR    8
#define SR_BSY      16
/*******************************************************/
/*      Flash control register (FLASH_CR)              */
/*******************************************************/
#define CR_PG       0
#define CR_SER      1
#define CR_MER      2
#define CR_SNB0     3
#define CR_SNB1     4
#define CR_SNB2     5
#define CR_SNB3     6
#define CR_PSIZE0   8
#define CR_PSIZE1   9
#define CR_STRT     16
#define CR_EOPIE    24
#define CR_ERRIE    25
#define CR_LOCK     31
/*******************************************************/
/*      Flash option control register (FLASH_OPTCR)    */
/*******************************************************/
#define OPTCR_LOCK        0
#define OPTCR_STRT        1
#define OPTCR_BOR_LEV0    2
#define OPTCR_BOR_LEV1    3
#define OPTCR_WDG_SW      5
#define OPTCR_nRST_STDBY  6
#define OPTCR_nRST_STOP   7
#define OPTCR_RDP0        8
#define OPTCR_RDP1        9
#define OPTCR_RDP2        10
#define OPTCR_RDP3        11
#define OPTCR_RDP4        12
#define OPTCR_RDP5        13
#define OPTCR_RDP6        14
#define OPTCR_RDP7        15
#define OPTCR_nWRP2       18
#define OPTCR_nWRP3       19
#define OPTCR_nWRP4       20
#define OPTCR_nWRP5       21
#define OPTCR_nWRP0       22
#define OPTCR_nWRP1       23
#define OPTCR_SPRMOD      31


#endif /* MCAL_MEMORY_FLASH_MEMORY_FLASH_PRIVATE_H_ */
