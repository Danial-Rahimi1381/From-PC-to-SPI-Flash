/*
 * Protocole.h
 *
 *  Created on: Jul 29, 2024
 *      Author: Danial-Rahimi
 */

#ifndef INCLUDE_PROTOCOLE_H_
#define INCLUDE_PROTOCOLE_H_
#include "DSP28x_Project.h"
#include "FLASH.h"
#define                         CHUNK_SIZE                  16
#define                         PAGE_SIZE                   256
#define                         ERASE_TIME_MS               200


 typedef struct {
     char    Headers[13];
     char    Footer[14];
     char    Status;
     char    Line;
     char    Line2;
     Uint16    Data[640];
     Uint16  CRC;
     char   crc1;
     char   crc2;
 } ProtocolFrame;


 extern ProtocolFrame frame;



 void Send_Header(char status,char Line,char Line2);

 void Send_Footer();

 void Send_CRC(Uint16 *Buf);

 void Send_CommandLine(int line,int line2);

 void Send_Data();

 void Send_CRC();

 void RxReader();

 void Give_Frame();

 void make_CRC(char *Data_CRC);

 void Write_In_Flash();

 void Write_In_Flash_Init(Uint32 startAddress, Uint16* data, Uint32 dataLength);

 Uint16 EraseFlashData(Uint32 *Address);

 void Read_From_Flash_Init(Uint32 startAddress, Uint16* buffer, Uint32 dataLength);

 void Read_From_Flash();

 void Send_To_Flash(int line,int line2,Uint16 *DataFlash);

 Uint16 Check_CRC(Uint16 *Buf);

 void Clear(Uint16* Ram);

 #endif /* INCLUDE_PROTOCOLE_H_ */


