#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "serialPort.h"		//	Comunicacion serie por UART

#define BAUD_RATE (0x67)	//	0x67=103 configura BAUD_RATE=9600@16MHz

void TERMINAL_Init();
void TERMINAL_EnqueueMessage(const char* message);

#endif