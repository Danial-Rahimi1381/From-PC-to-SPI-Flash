/*
 * sci.c
 *
 *  Created on: Jul 31, 2024
 *      Author: RayFan
 */
#include "sci.h"

int i = 0;
int j = 0;
int s = 0;

void Init_Sci(void)
{
    // Initialize SCI-A
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;
     // Hardware settings for SCI pins
     GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 to SCIRXDA
     GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 to SCITXDA
     GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;  // Enable pull-up for GPIO28 (SCIRXDA)
     GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;  // Enable pull-up for GPIO29 (SCITXDA)
     GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
//////////////////////////////////////////////////////////////////////////
     // Configure SCI control registers
     SciaRegs.SCICCR.all = 0x0007;  // 1 stop bit, No loopback
     SciaRegs.SCICTL1.all = 0x0003; // Enable TX, RX
     SciaRegs.SCICTL2.all = 0x0003;
     SciaRegs.SCICTL2.bit.TXINTENA = 1; // Enable TX interrupt
     SciaRegs.SCICTL2.bit.RXBKINTENA = 1; // Enable RX interrupt
     SciaRegs.SCICTL1.bit.RXENA = 1;
     // Enable transmit FIFO module
     SciaRegs.SCIHBAUD = 0x0000;
     SciaRegs.SCILBAUD =0x27;// 0xE7; // 9600 baud rate
     SciaRegs.SCIFFTX.all = 0xC028;
     SciaRegs.SCIFFRX.all = 0x0028;

     //////////////////////////////////////////////////////////////////////////
     SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset
     SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
     SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
    // SciaRegs.SCICCR.bit.LOOPBKENA = 1; // Enable loopback mode
     EDIS;

}

void TS_DspDrv_SciTransChar(char p_u8Char)
{
    while(SciaRegs.SCICTL2.bit.TXRDY != 1);//Transmitter buffer register ready flag
    SciaRegs.SCICTL1.bit.TXWAKE = 1;
    SciaRegs.SCITXBUF =  p_u8Char;
    SciaRegs.SCICTL1.bit.TXWAKE = 0;

}

void TS_DspDrv_SciTransCharArray(char *p_u8Char)
{

    for(j = 0; j < 16; j++){

        SciaRegs.SCITXBUF =  p_u8Char[j];
    }
}


void Send_1Byte_Data(char data)
{
    SciaRegs.SCITXBUF = data;     // Send data from FIFO to TX buffer
}
void Send_1Byte_Data16(Uint16 data)
{
    SciaRegs.SCITXBUF = data;     // Send data from FIFO to TX buffer
}
void Send_2Byte_Data(Uint16 data)
{
    SciaRegs.SCITXBUF = data;     // Send data from FIFO to TX buffer
}


void Send_MultiByte_Data(char *DataArray, int length)
{
    int i ;
    for(i = 0; i < length;i++)
    {
        Send_1Byte_Data(DataArray[i]);
    }
}

void Send_MultiByte_Data16_(Uint16 *DataArray, int length)
{
    int i ;
    for(i = 0; i < length;i++)
    {
        Send_2Byte_Data(DataArray[i]);
    }
}
char RxReader1Byte()
{
    char receivedData = SciaRegs.SCIRXBUF.all;
    return receivedData;
}

