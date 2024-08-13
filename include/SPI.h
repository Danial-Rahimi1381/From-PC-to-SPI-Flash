/*
 * SPI.h
 *
 *  Created on: May 8, 2024
 *      Author: Danial
 */

#ifndef INCLUDE_SPI_H_
#define INCLUDE_SPI_H_

#include "DSP28x_Project.h"
#define SPI_MODULE           SpiaRegs       // SPI module to use (e.g., SPIA)
#define SPI_PORT             GPIOB


#define             CS_High                 GpioDataRegs.GPBSET.bit.GPIO58          = 1
#define             CS_Low                  GpioDataRegs.GPBCLEAR.bit.GPIO58        = 1
#define             ENSPI                   GpioDataRegs.GPBSET.bit.GPIO57          = 1;
#define             DISPI                   GpioDataRegs.GPBCLEAR.bit.GPIO57        = 1;

#define             CS_PIN                  GPIO_PIN_58                                // Chip Select (GPIO57/XD22)
#define             CLK_PIN                 GPIO_PIN_56                                // Serial Clock (GPIO56/SPICLKA/XD23)
#define             MOSI_PIN                GPIO_PIN_55                                // Master Out Slave In (GPIO55/SPISOMIA/XD24)
#define             MISO_PIN                GPIO_PIN_54                                // Master In Slave Out (GPIO54/SPISIMOA/XD25)

// Define SPI register addresses
#define             SPI_CONFIG_REG          SpiaRegs.SPICCR
#define             SPI_CONTROL_REG         SpiaRegs.SPICTL
#define             SPI_STATUS_REG          SpiaRegs.SPISTS
#define             SPI_BAUD_RATE_REG       SpiaRegs.SPIBRR
#define             SPI_TRANSMIT_REG        SpiaRegs.SPITXBUF
#define             SPI_RECEIVE_REG         SpiaRegs.SPIRXBUF

//------------------------

void SPI_GPIO();

void SPI_Init();

void SPI_FIFO();

//-----------------------

void SPI_WriteReg(Uint16 data);

Uint16 SPI_ReadReg();


#endif
