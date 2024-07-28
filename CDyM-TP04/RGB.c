/*
 * RGB.c
 *
 * Created: 24/7/2024 03:00:00
 * Author : Estanislao Carrer, Fernando Ramirez, Lisandro Martinez
 */ 

#include "RGB.h"

#define PWM_SOFT_OFF		PWM_PORT &= ~(1 << PWM_PIN_R)		// Pone el pin del color ROJO en bajo
#define PWM_SOFT_ON			PWM_PORT |= (1 << PWM_PIN_R)		// Pone el pin del color ROJO en alto

/*********************************************************
	Esta funcion inicializa el TIMER 0 para generar una
	señal PWM por SOFTWARE para el color ROJO y el 
	TIMER 1 para generar dos señales PWM por HARDWARE 
	para los colores VERDE y AZUL. Todas ellas son de 
	976.6 Hz (aprox.) y utilizan el modo invertido.
	
	Para inicializar las mismas, la funcion recibe por 
	parametros los valores de los registros de comparacion
	para los cuales cada señal invierte su estado.
*********************************************************/
void RGB_Init(uint8_t initR, uint8_t initG, uint8_t initB)
{
	*(&PWM_PORT - 1) |= (1<<PWM_PIN_R) | (1<<PWM_PIN_G) | (1<<PWM_PIN_B);	//	Establecer el pin de cada color como salida
	RGB_SetValues(initR, initG, initB);
	
	PWM_SOFT_OFF;	// Inicializar el pin del color ROJO en bajo
	
	//	Configurar TIMER 1 para generar PWM invertido por hardware
	TCCR1A |= (1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0);	//	PWM invertido
	TCCR1A |= (1<<WGM10) | (1<<WGM12);					//	Modo de operación FAST-PWM 8-bit
	TCCR1B |= (1<<CS11) | (1<<CS10);					//	Establecer prescaler de 64
	
	//	Configurar TIMER 0 para generar PWM invertido por software
	TCCR0A = 0;								//	Modo de operacion NORMAL
	TCCR0B = (1 << CS01) | (1 << CS00);		//	Establecer prescaler de 64
	TIMSK0 = (1 << OCIE0A) | (1 << TOIE0);
}

/********************************************************************
	Esta funcion recibe por parametros y establece los valores de los
	registros de comparacion para cada señal.
********************************************************************/
void RGB_SetValues(uint8_t red, uint8_t green, uint8_t blue)
{
	OCR0A = red;
	OCR1B = green;
	OCR1A = blue;
}

/**********************************************************************
	Esta interrupcion pone el pin de la señal PWM generada por software
	en alto cuando el contador del TIMER 0 alcanza el valor de OCR0A.
**********************************************************************/
ISR(TIMER0_COMPA_vect)
{
	PWM_SOFT_ON;
}

/**********************************************************************
	Esta interrupcion pone el pin de la señal PWM generada por software
	en bajo cuando el contador del TIMER 0 alcanza el OVERFLOW.
**********************************************************************/
ISR(TIMER0_OVF_vect)
{
	PWM_SOFT_OFF;
}