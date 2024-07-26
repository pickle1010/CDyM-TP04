#include "ADC.h"

void ADC_Init(void)
{
	DDRC &=	~(1<<DDC3);		// Se configura como entrada analógica el pin PC3
	DIDR0 |= (1<<ADC3D);
	
	ADCSRB = 0x00;			// Se configura el FREE RUNNING mode
	
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);		// ADEN=1 Activa el ADC ; Preescaler -> 128, entonces ADPS2=ADPS1=ADPS0=1 (revisar tabla)

	ADMUX |= (1<<REFS0) | (1<<ADLAR) | (1<<MUX1) | (1<<MUX0);				//REFS1=0 & REFS0=1 -> modo AVCC en VREF / ADLAR=1 resultados a la izq (parte alta) / MUX1=MUX0=1 Se utiliza ADC3 como canal
}

// Realiza una conversion manejada por polling
void ADC_Read(void)
{
	ADC_StartConversion();
	while ((ADCSRA & (1<<ADIF))==0);	// Se espera el termino de la conversion
	
	ADCSRA |= (1<<ADIF);				// Se borra el flag para permitir una nueva conversion
}

// Inicia una nueva conversion
void ADC_StartConversion(void)
{
	ADCSRA |= (1<<ADSC);
}

// Habilita la interrupcion del ADC
void ADC_EnableInt(void)
{
	ADCSRA |= (1 << ADIE);
}

// Habilita el auto-triggering del ADC
void ADC_EnableAT(void)
{
	ADCSRA |= (1 << ADATE);
}

// Retorna los 8 bits más significativos de los datos obtenidos por el ADC
uint8_t ADC_GetData(void)
{
	return ADCH;
}
