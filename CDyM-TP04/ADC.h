#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/*METODOS ADC*/
void ADC_Init(void);
void ADC_Read(void);
void ADC_StartConversion(void);
void ADC_EnableInt(void);
void ADC_EnableAT(void);

/*GETTERS-SETTERS*/
uint8_t ADC_GetData(void);

#endif