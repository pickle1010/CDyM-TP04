#include "RGB.h"

/********************************************************
CONFIGURAR TIMER 0 EN MODO NORMAL CON UNA FRECUENCIA
DE 16 MHz PARA QUE GENERE UNA INTERUPPCION CUANDO EL
CONTADOR ALCANZA EL VALOR DE OCR0A (INICIALIZADO EN
init_delta) Y OTRA CUANDO OCURRE OVERFLOW.

ADEMAS CONFIGURA EL PIN DE LA SEÑAL PWM COMO SALIDA E
INICIALIZA EL MISMO EN ALTO PARA USAR EL PWM EN MODO
NO INVERTIDO.
********************************************************/
void RGB_Init(uint8_t initR, uint8_t initG, uint8_t initB)
{
	*(&PWM_PORT - 1) |= (1<<PWM_PIN_R) | (1<<PWM_PIN_G) | (1<<PWM_PIN_B);
	RGB_SetValues(initR, initG, initB);	// Inicializar los valores iniciales para cada color
	
	PWM_SOFT_ON;	// Inicializar pin de PWM por software en alto
	
	// TIMER 1
	//configuro salidas para generar PWM no invertido
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1);

	//Configurar modo de operación para generar PWM
	TCCR1A |= (1<<WGM10) | (1<<WGM12);

	//configurar el preescalador a 64
	TCCR1B |= (1<<CS11) | (1<<CS10);
	
	// Configuracion de Timer 0 para PWM por software
	TCCR0A = 0;		// Modo normal
	TCCR0B = (1 << CS01) | (1 << CS00);	// Prescaler de 64
	TIMSK0 = (1 << OCIE0A) | (1 << TOIE0);
}

/****************************************************************
CONFIGURAR EL TIEMPO DE CAMBIO DENTRO DEL PERIODO DE LA SEÑAL PWM
****************************************************************/
void RGB_SetValues(uint8_t red, uint8_t green, uint8_t blue)
{
	OCR0A = red;
	OCR1B = green;
	OCR1A = blue;
}

ISR(TIMER0_COMPA_vect)
{
	PWM_SOFT_OFF;
}

ISR(TIMER0_OVF_vect)
{
	PWM_SOFT_ON;
}