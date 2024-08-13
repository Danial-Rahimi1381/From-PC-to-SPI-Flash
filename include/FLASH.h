/*
 * FLASH.h
 *
 *  Created on: May 13, 2024
 *      Author: Danial
 */

#ifndef INCLUDE_FLASH_H_
#define INCLUDE_FLASH_H_

#include "DSP28x_Project.h"
#include "SPI.h"

#define WREN        0x06  //Write Enable
#define WRDI        0x04  //Write disable
#define WRSR        0x01  //Write status register
#define RDID        0x9F  //Read identific-ation
#define RDSR        0x05  //Read status register
#define READ        0x03  //Read Data
#define FAST_READ   0x0B  //FAST READ DATA
#define RDSFDP      0x5A //Read SFDP
#define RES         0xAB // Read electronic ID
#define REMS        0x90 // Read electronic manufacturer
#define DREAD       0x3B //Output Mode command
#define SE          0x20 //Sectroc Erase
#define BE          0xD8 //Block Erase
#define CE          0xC7 //Chip Erase
#define PP          0x02 //Page Program
#define RDSCUR      0x2B //Read security
#define WRSCUR      0x2F //Write security register
#define ENSO        0xB1 //Enter secured OTP
#define EXSO        0xC1 //Exit secured OTP
#define DP          0xB9  //Deep power down
#define RDP         0xAB  // Release from deep power down
//---------------------------------------------------
#define WIP          0// Write in progress bit
#define WEL          1// Write Enable  lath
#define BP           2// level of protected block
#define BP1          3// level of protected block
#define BP2          4// level of protected block
#define BP3          5// level of protected block
#define SRWD         7// Status register Write protect
//---------------------------------------------------

struct Address_Flash
{
    Uint16 Block;
    unsigned int Sector : 4; // 4-bit field for Sector
    unsigned int Page   : 4;   // 4-bit field for Page
    Uint16 Byte;

};



Uint16         SendCommand(Uint16 Data);
unsigned char  Read_Status_Register();
void    checkAddress();
void    Read_Data_Bytes(Uint32 StartAddress, Uint16 *ReciveData, Uint32 length);
void    Sector_Erase(Uint32 StartAddress);
void    Block_Erase(Uint32 StartAddress);
void    Chip_Erase();
void    Write_Enable();
void    Write_Disable();
void    Write_Status_Register();
void    Flash_Write_PP(Uint32 StartAddress, Uint16* DataWrite);
void    Flash_Write_PP_B(Uint32 StartAddress, Uint16* DataWrite,int length);
void    split_address_to_bytes(Uint32 address, Uint16 *byte1, Uint16 *byte2, Uint16 *byte3);

void    error();

#endif
