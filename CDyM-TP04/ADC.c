
#include "ADC.h"

uint8_t adc_flag;	   //se utiliza para avisar en el main que el módulo terminó la conversión
volatile uint8_t data; //se utiliza para guardar los datos que arroja ADC

void ADC_Init(void){
	DDRC &=~(1<<DDC3);											// Se configura como entrada analógica el pin PC3
	DIDR0 |= (1<<ADC3D);
	
	ADCSRB = 0x00;												// Se configura el FREE RUNNING mode
	
	ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);        // ADEN=1 Activa el ADC / Preescaler -> 8, entonces ADPS1=ADPS0=1 (revisar tabla)

	ADMUX |= (1<<REFS0) | (1<<ADLAR) | (1<<MUX1) | (1<<MUX0);   //REFS1=0 & REFS0=1 -> modo ADCC en VREF / ADLAR=1 resultados a la izq (parte alta) / MUX1=MUX0=1 Se utiliza ADC3 como canal
}

void ADC_Read(void){
	ADCSRA |= (1<<ADSC);				// Se inicia la conversión
	while ((ADCSRA & (1<<ADIF))==0);	// Se espera el termino de la conversión
	
	ADCSRA |= (1<<ADIF);				// Se borra el flag
	
	data = ADCH;						// Guardo efectivamente los datos que arroja ADC (configurado para recibirlos en la parte alta)
	
	adc_flag = 1;						// Flag de término de conversión
}

void adc_setFlag(uint8_t f){
	adc_flag = f;
}

uint8_t adc_getFlag(void){
	return adc_flag;
}

uint8_t adc_getData(void){
	return data;
}

//necesitamos una interrupcion para el adc?? o eso lo controlamos afuera? 