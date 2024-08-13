/*
 * sci.h
 *
 *  Created on: Jul 31, 2024
 *      Author: RayFan
 */

#ifndef INCLUDE_SCI_H_
#define INCLUDE_SCI_H_
#include "DSP28x_Project.h"

void Init_Sci(void);

void TS_DspDrv_SciTransChar(char p_u8Char);


void TS_DspDrv_SciTransCharArray(char *p_u8Char);

void Send_1Byte_Data(char data);
void Send_1Byte_Data16(Uint16 data);

void Send_2Byte_Data(Uint16 data);

void Send_MultiByte_Data(char *DataArray, int length);
void Send_MultiByte_Data16_(Uint16 *DataArray, int length);

char RxReader1Byte();


void RxReader16Byte();

void write_Array(int length);

void Clear_FIFO(int length);
#endif /* INCLUDE_SCI_H_ */
