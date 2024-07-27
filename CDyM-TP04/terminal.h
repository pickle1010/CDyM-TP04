/*
 * terminal.h
 *
 * Created: 25/7/2024 20:00:00
 * Author : Estanislao Carrer, Fernando Ramirez, Lisandro Martinez
 */ 

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "serialPort.h"		//	Para comunicacion serie por UART

#define BAUD_RATE (0x67)	//	0x67=103 configura BAUD_RATE=9600@16MHz

void TERMINAL_Init();
void TERMINAL_EnqueueMessage(const char* message);

#endif