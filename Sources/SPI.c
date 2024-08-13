#include "SPI.h"

void SPI_GPIO()
{
    EALLOW;
     /*---------------------------------------------------- Select GPIO58 as output for DSC_CS_A */
     GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;
     GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;
     GpioCtrlRegs.GPBDIR.bit.GPIO58 = 1;
     /*------------------------------------------------------------------------------------------*/

     /*------------- Select GPIO54 as DSC_MOSI & GPIO55 as DSC_MISO & GPIO56 as DSC_SCLK for SPI */
     /* Enable internal pull-up for the selected pins
        Pull-ups can be enabled or disabled disabled by the user.
        This will enable the pullups for the specified pins.*/

     GpioCtrlRegs.GPBPUD.bit.GPIO54   = 0;       // MOSI
     GpioCtrlRegs.GPBPUD.bit.GPIO55   = 0;       // MISO
     GpioCtrlRegs.GPBPUD.bit.GPIO56   = 0;       // SCLK

     /* Set qualification for selected pins to asynch only
        Inputs are synchronized to SYSCLKOUT by default.
        This will select asynch (no qualification) for the selected pins.*/

     GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3;       // Asynch input GPIO54 (SPISIMOA)
     GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3;       // Asynch input GPIO55 (SPISOMIA)
     GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3;       // Asynch input GPIO56 (SPICLKA)

     /* Configure SPI pins using GPIO regs
        This specifies which of the possible GPIO pins will be SPI functional pins.*/
     GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1;        // Configure GPIO54 as SPISIMOA
     GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1;        // Configure GPIO55 as SPISOMIA
     GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1;        // Configure GPIO56 as SPICLKA
     /*------------------------------------------------------------------------------------------*/
     EDIS;
}


void SPI_Init()
{
    SpiaRegs.SPICCR.all = 0x0007;
    SpiaRegs.SPICTL.all = 0x000F;   //no phase delay master mode
    SpiaRegs.SPIBRR = 0x0024;  // losplck / 36  + 1 =  1mhz
    SpiaRegs.SPIPRI.bit.FREE = 1;   // Free run
    SpiaRegs.SPICCR.all= 0x0087; // Renable SPI

}

void SPI_FIFO()
{
EALLOW;
    // Initialize SPI FIFO registers
    SpiaRegs.SPIFFTX.all=0xE040;
    SpiaRegs.SPIFFRX.all=0x204f;
    SpiaRegs.SPIFFCT.all=0x0;
EDIS;
}


void SPI_WriteReg(Uint16 data)
{
     SpiaRegs.SPISTS.bit.INT_FLAG = 1;
     SpiaRegs.SPITXBUF = data << 8;
     while(!SpiaRegs.SPISTS.bit.INT_FLAG){}
     DELAY_US(10);
}

Uint16 SPI_ReadReg()
{
    Uint16 Recive;
    SPI_WriteReg(0xFF);
    Recive = (SpiaRegs.SPIRXBUF);
    return Recive;
}

