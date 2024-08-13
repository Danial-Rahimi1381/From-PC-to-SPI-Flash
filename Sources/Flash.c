/*
 * Flash.c
 *
 *  Created on: Jul 31, 2024
 *      Author: Danial-Rahimi
 */


#include "FLASH.h"
static Uint16 Address[3];

void Write_Enable()
{
    CS_Low;
        SPI_WriteReg(WREN);
        DELAY_US(10);
    CS_High;
}

void Write_Disable()
{
    CS_Low;
        SPI_WriteReg(WRDI);
    CS_High;
}

void Chip_Erase()
{
    Write_Enable();
    CS_Low;
    SPI_WriteReg(CE);
    CS_High;
}
void Sector_Erase(Uint32 StartAddress)
{
    Write_Enable();
    split_address_to_bytes(StartAddress,&Address[0],&Address[1],&Address[2]);

    CS_Low;
    SPI_WriteReg(SE);
    DELAY_US(20);

    SPI_WriteReg(Address[0]);
    DELAY_US(20);

    SPI_WriteReg(Address[1]);//Byte1 Address;
    DELAY_US(20);

    SPI_WriteReg(Address[2]);//Byte2 Address;
    CS_High;
//tSE Sector Erase Cycle Time 40 200 ms

}
/*void Block_Erase(struct Address_Flash StartAddress)
{
    Write_Enable();
    checkAddress(StartAddress);
    unsigned char combined = (StartAddress.sector << 4) | (StartAddress.page & 0x0F);
    split_address_to_bytes(StartAddress,&Address[0],&Address[1],&Address[2]);
    CS_Low;

    SPI_WriteReg(BE);
    DELAY_US(20);
    SPI_WriteReg(StartAddress.Block);
    DELAY_US(20);
    SPI_WriteReg(combined);//Byte1 Address;
    DELAY_US(20);
    SPI_WriteReg(StartAddress.Byte);//Byte2 Address;
    CS_High;
}*/
/*



void Write_Security_Register()
{

}

void Dual_Output_Read_Mode_Sequence()
{

}
*/
void Write_Status_Register(Uint16 Status)
{
    Write_Enable();
    CS_Low;
    SPI_WriteReg(WRSR);
    DELAY_US(10);
    SPI_WriteReg(Status);
CS_High;

}
void Flash_Write_PP(Uint32 StartAddress, Uint16* DataWrite)
{
    Write_Enable();
    CS_Low;
        split_address_to_bytes(StartAddress,&Address[0],&Address[1],&Address[2]);
        SPI_WriteReg(PP);
        DELAY_US(20);
        SPI_WriteReg(Address[0]);
        DELAY_US(20);

        SPI_WriteReg(Address[1]);//Byte1 Address;
        DELAY_US(20);

        SPI_WriteReg(Address[2]);//Byte2 Address;
        DELAY_US(20);
        //***************//
        SPI_WriteReg(0x01);
        DELAY_US(20);

        SPI_WriteReg(0x04);
        DELAY_US(20);

        SPI_WriteReg(0x02);
        DELAY_US(20);
        //**************//
   CS_High;

}

void Read_Data_Bytes(Uint32 StartAddress, Uint16 *ReciveData, Uint32 length)
{
    int i ;

    CS_Low;
    split_address_to_bytes(StartAddress,&Address[0],&Address[1],&Address[2]);

    SPI_WriteReg(READ);
    DELAY_US(20);

    SPI_WriteReg(Address[0]);//Byte1 Address;
    DELAY_US(20);

    SPI_WriteReg(Address[1]);//Byte2 Address;
    DELAY_US(20);

    SPI_WriteReg(Address[2]);//Byte3 Address;
    DELAY_US(20);

    for(i = 0 ; i < length ; i++)
    {
        ReciveData[i] = SPI_ReadReg();
        DELAY_US(20);
    }
  CS_High;

}

void Read_Higher_Speed(Uint32 StartAddress, Uint16 *ReciveData, Uint16 length)
{

    CS_Low;
    split_address_to_bytes(StartAddress,&Address[0],&Address[1],&Address[2]);
    SPI_WriteReg(READ);
    DELAY_US(20);
    SPI_WriteReg(Address[0]);//Byte1 Address;
    DELAY_US(20);
    SPI_WriteReg(Address[1]);//Byte2 Address;
    DELAY_US(20);
    SPI_WriteReg(Address[2]);//Byte3 Address;
    DELAY_US(20);
    SPI_WriteReg(0xFF); //Dummy
    ReciveData[0] = SPI_ReadReg();
    DELAY_US(20);
    ReciveData[1] = SPI_ReadReg();
    DELAY_US(20);
    CS_High;

}

void Flash_Write_PP_B(Uint32 StartAddress, Uint16* DataWrite,int length)
{
    int i;
    Write_Enable();
    CS_Low;
        split_address_to_bytes(StartAddress,&Address[0],&Address[1],&Address[2]);

        SPI_WriteReg(PP);
        DELAY_US(20);

        SPI_WriteReg(Address[0]); // Block Address _Range 0 to 64hex
        DELAY_US(20);

        SPI_WriteReg(Address[1]); // Sector Address_Range 0 to 16 hex
        DELAY_US(20);

        SPI_WriteReg(Address[2]); // Page Address Range 0 to 256 Decimal
        DELAY_US(20);

        //***************//
        for(i = 0; i < length ; i++)
        {
           SPI_WriteReg(DataWrite[i]);
           DELAY_US(20);
        }
        //**************//
   CS_High;

}


unsigned char Read_Status_Register()
{
    unsigned char recive;
    CS_Low;
       SPI_WriteReg(0x05);
       recive = SPI_ReadReg();
      DELAY_US(20);
       CS_High;
       return recive ;

}

void split_address_to_bytes(Uint32 address, Uint16 *byte1, Uint16 *byte2, Uint16 *byte3) {
    *byte1 = (address >> 16) & 0xFF;  // Extract the second most significant byte
    *byte2 = (address >> 8) & 0xFF;   // Extract the next byte
    *byte3 = address & 0xFF;          // Extract the least significant byte
}


void checkAddress(struct Address_Flash StartAddress)
{
    if(StartAddress.Block > 0x40) error();
    if(StartAddress.Sector >  0x0F) error();
    if(StartAddress.Page > 0x0F) error();
    if(StartAddress.Byte > 0xFF) error();
}

void error()
{

}
/*
void Read Identification()
{

}


void Read_Security_Register()
{

}

void Read_Electronic_Manufacturer_DeviceID()
{

}*/
