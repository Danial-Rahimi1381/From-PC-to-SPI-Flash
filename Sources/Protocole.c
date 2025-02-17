/*
 * Protocole.c
 *
 *  Created on: Jul 29, 2024
 *      Author: RayFan
 */
#include "Protocole.h"
#include "sci.h"
#include "CRC.h"
/***   Define   ***/
#define                 DATA_LENGTH                     672
Uint16              status = 0;
Uint16              Flag_Erase =0;
Uint32              erase_timer_count =0;
/***   Variable   Serial  ***/
int         counter_line                                            = 0;
int         counter_Footer                                          = 0;
int         counter_Headers                                         = 0;
int         head_Recive                                             = 0;
int         Data_index                                              = 0;
int         offset                                                  = 0;
int         Flag_Write_Flash                                        = 0;
int         Flag_Read_Flash                                         = 0;

//**************************/

/******* Variable SPI     ****/

/*-----------------------------    Write    -----------------------------*/
Uint32       Address                                                = 0x000000;
Uint16       Buffer[DATA_LENGTH]                                    = {0};
static char writeStep                                               = 0;
static Uint32 currentAddress                                        = 0;
static Uint16* currentData                                          = 0;
static Uint32 remainingLength                                       = 0;
static Uint32 bytesWrittenInCurrentStep                             = 0;

/*-----------------------------    Read    -----------------------------*/
static Uint32           currentReadAddress                          = 0;
static Uint16*          currentReadBuffer                           = 0;
static Uint32           remainingReadLength                         = 0;
static Uint32           bytesReadInCurrentStep                      = 0;
/*---------------------------------------------------------------------*/


/***      Struct       ***/
// Initialize a global protocol frame
ProtocolFrame frame = {
    .Headers        =  {0xAA, 0xAA, 0xAA, 0xBB, 0xBB, 0xBB, 0xCC, 0xCC, 0xCC, 0xDD, 0xDD, 0xDD, 0xEE},
    .Footer         =  {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x12, 0x13, 0x14, 0x15, 0x16},
    .Data           =  {0},
    .Status         =    0,
    .Line           =    0,
    .CRC            =    0
};

//***********************       Function Serial   ***************************************//
/*************************************/
/*        Function Serial            */
/*************************************/
/*void Send_Header
 *void Send_Footer
 *void Send_CommandLine
 *void RxReader
 *void Send_CRC
 **************************************/

 void Send_Header(char status,char Line,char Line2)
 {
  switch(counter_Headers)
  {
  case 0 :
      //Headers
      Send_MultiByte_Data(frame.Headers,11);
      counter_Headers++;
      break;
  case 1 :
      Send_MultiByte_Data(&frame.Headers[11],2);
      //Status
      frame.Status  = status;
      Send_1Byte_Data(frame.Status);
      //Line
      frame.Line    = Line;
      frame.Line2   = Line2;
      Send_2Byte_Data(frame.Line);
      Send_2Byte_Data(frame.Line2);
      counter_Headers++;
      break;
  }
  if(counter_Headers == 2)counter_Headers = 0;

 }
 void Send_Footer()
 {
     //Footer
     switch(counter_Footer)
     {
     case 0:     Send_MultiByte_Data(frame.Footer,11); counter_Footer++; break;
     case 1:     Send_MultiByte_Data(&frame.Footer[11],3);  counter_Footer++; break;
     }
     if(counter_Footer == 2)counter_Footer = 0;

     //CRC
//     frame.CRC = Make_andGive_CRC();
  //   Send_2Byte_Data(frame.CRC);
 }


 void Send_CommandLine(int line,int line2)
 {
         switch(counter_line)
         {
             case 0 :
                     Send_Header(1,line,line2);
                     counter_line++;
                     break;
             case 1 :
                     Send_Header(1,line,line2);
                     counter_line++;
                     break;
             case 2 :
                     Send_Footer();
                     counter_line++;
                     break;
             case 3 :
                     Send_Footer();
                     counter_line++;
                     break;
         }
         if(counter_line == 4)  counter_line = 0;
 }

 /***   Function Recive   ***/

void RxReader()
{

     int i;
     head_Recive = SciaRegs.SCIFFRX.bit.RXFFST;
     if(head_Recive > 0)
     {
         for(i = head_Recive; i > 0 ; i--)
         {
             Uint16 receivedData = SciaRegs.SCIRXBUF.all;
             Buffer[Data_index] = receivedData;
             if(Data_index > 15  && Data_index <= 655)
                     frame.Data[Data_index - 16] = receivedData;
             if(Data_index == 656) frame.CRC = CRC16_Modbus(frame.Data,640);
             Data_index++;
         }
     }
}


void Send_CRC(Uint16 *Buf)
{

        Uint16 Value_CRC = CRC16_Modbus(Buf, 640);
        frame.crc1 = (char)(Value_CRC & 0x00FF);
        frame.crc2 = (char)((Value_CRC >> 8) & 0x00FF);
        Send_1Byte_Data(frame.crc1);
        Send_1Byte_Data(frame.crc2);

}

//***********************       Function Write & Read   ***************************************//
/*************************************/
/*        Function SPI               */
/*************************************/
/*void Write_In_Flash_Init
 *void Write_In_Flash
 *void Read_From_Flash_Init
 *void Read_From_Flash
 *void
 **************************************/

void Write_In_Flash_Init(Uint32 startAddress, Uint16* data, Uint32 dataLength) {
    currentAddress = startAddress;
    currentData = data;
    remainingLength = dataLength;
    writeStep = 0;
    bytesWrittenInCurrentStep = 0;
}


void Write_In_Flash()
{

        Uint32 chunkSize = 64;
                    status = Read_Status_Register();
                    if(writeStep == 2   && bytesWrittenInCurrentStep == 128 )
                    {
                        Flag_Write_Flash = 1;
                        return;
                    }
                  if (remainingLength == 0 )
                  {
                      return;
                  }

                  if (remainingLength < chunkSize)
                  {
                      chunkSize = remainingLength;
                  }
                  status = Read_Status_Register();
                  if(!(status & (1<<0)))
                  {
                  Flash_Write_PP_B(currentAddress, currentData, chunkSize);


                      currentAddress += chunkSize;

                      currentData += chunkSize / sizeof(Uint16);

                      remainingLength -= chunkSize;

                      bytesWrittenInCurrentStep += chunkSize;
                      status = Read_Status_Register();

                      if (bytesWrittenInCurrentStep >= 256)
                      {
                          bytesWrittenInCurrentStep = 0;
                         // currentAddress += 0x000100;
                          writeStep++;
                      }
                  }


}

void Read_From_Flash_Init(Uint32 startAddress, Uint16* buffer, Uint32 dataLength) {
    currentReadAddress = startAddress;
    currentReadBuffer = buffer;
    remainingReadLength = dataLength;
    bytesReadInCurrentStep = 0;
}

void Read_From_Flash() {
                 Uint32 chunkSize = 64;

                 if(bytesReadInCurrentStep == 640 && Flag_Read_Flash == 0)
                 {
                     Flag_Read_Flash = 1;
                 }

                if (remainingReadLength == 0 && !(status & (1<<0))) {
                    return;
                }

                if (remainingReadLength < chunkSize) {
                    chunkSize = remainingReadLength;
                }
                status = Read_Status_Register();
                if(!(status & (1<<0)))
                {
                Read_Data_Bytes(currentReadAddress, currentReadBuffer, chunkSize);

                bytesReadInCurrentStep += chunkSize;

                currentReadBuffer += chunkSize / sizeof(Uint16);

                remainingReadLength -= chunkSize;

                currentReadAddress += chunkSize;
                }

}



Uint16 Check_CRC(Uint16 *Buf)
{
    Uint16 Value_CRC = CRC16_Modbus(Buf, 640);
    frame.crc1 = (char)(Value_CRC & 0x00FF);
    frame.crc2 = (char)((Value_CRC >> 8) & 0x00FF);
    if(Buffer[671] == frame.crc1  && Buffer[670] == frame.crc2)
    {
        Flag_Erase = 0;
        return 1;
    }
    else
    {
        Flag_Erase = 1;
        return 0;
    }
}
Uint16 EraseFlashData(Uint32 *Address)
{
    if (Flag_Erase == 1)
    {
        if (erase_timer_count == 0) {;
            *Address &= 0xFFFF00;
            Sector_Erase(*Address);
        }

        if (erase_timer_count < ERASE_TIME_MS) {
            erase_timer_count++;
        } else {
                Flag_Erase = 0;
                erase_timer_count = 0;
                return ((*Address >> 12) & 0xF) * 5;
            }

    } else {
        erase_timer_count = 0;
    }

    return 0;
}

void Clear(Uint16* Ram)
{
    frame.crc1                  = 0;
    frame.crc2                  = 0;
    frame.CRC                   = 0;
    Flag_Erase                  = 0;
    erase_timer_count           = 0;
    currentReadAddress          = 0;
    currentReadBuffer           = 0;
    remainingReadLength         = 0;
    bytesReadInCurrentStep      = 0;
    currentAddress              = 0;
    currentData                 = 0;
    remainingLength             = 0;
    writeStep                   = 0;
    bytesWrittenInCurrentStep   = 0;
    Data_index                  = 0;
    counter_line                = 0;
    counter_Footer              = 0;
    counter_Headers             = 0;
    Flag_Read_Flash             = 0;
    Flag_Write_Flash            = 0;
    int i ;
    for(i = 0; i < 640 ; i++)
    {
        frame.Data[i] = 0;
    }
    for(i = 0; i < 640; i++)
    {
        Ram[i] = 0;
    }
    for(i = 0; i < 672; i++)
    {
        Buffer[i] = 0;
    }
}


/*

void Send_To_Flash(int line,int line2,Uint16 *DataFlash)
{

    if(counter_line < 3)
    {
        if(counter_line == 0) counter_Headers = 0;
           Send_Header(2,line,line2);
           counter_line++;
    }
   else if(counter_line >= 3 && counter_line <= 63)
    {
           Send_MultiByte_Data16_(&DataFlash[offset2],11);
            offset2 += 11;
            counter_line++;
    }
   else if(counter_line >= 62 && counter_line <= 64)
   {
           Send_Footer();
           counter_line++;
   }
    else if(counter_line == 65)
    {
             Send_CRC(DataFlash);
             counter_line = 0;
    }

}
*/


