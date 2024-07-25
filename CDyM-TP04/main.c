/*
 * CDyM-TP04.c
 *
 * Created: 22/7/2024 20:06:53
 * Author : Estanislao Carrer, Fernando Ramirez, Lisandro Martinez
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void MAIN_Init(void);
void PWM_soft_Init(void);
void PWM_soft_SetDelta(uint8_t delta);

#define PWM_PIN 5			// Pin de salida de la señal PWM
#define PWM_PORT PORTB		// Puerto de la señal PWM

#define PWM_OFF			PWM_PORT &= ~(1 << PWM_PIN)				// Pone el pin de la señal en bajo
#define PWM_ON			PWM_PORT |= (1 << PWM_PIN)				// Pone el pin de la señal en alto
#define PWM_START		*(&PWM_PORT - 1) |= (1 << PWM_PIN)		// Configura el pin de la señal como salida
#define PWM_INIT_DELTA	0

int main(void)
{
    MAIN_Init();
	
    while (1) 
    {
    }
}

void MAIN_Init()
{
	DDRB = (1 << PORTB5);
	PORTB = 0;
	
	PWM_soft_Init();
	sei();
}

/****************************************************************
CONFIGURAR EL TIEMPO DE CAMBIO DENTRO DEL PERIODO DE LA SEÑAL PWM
****************************************************************/
void PWM_soft_SetDelta(uint8_t delta)
{
	OCR0A = delta;
}

/********************************************************
CONFIGURAR TIMER 0 EN MODO NORMAL CON UNA FRECUENCIA 
DE 16 MHz PARA QUE GENERE UNA INTERUPPCION CUANDO EL
CONTADOR ALCANZA EL VALOR DE OCR0A (INICIALIZADO EN 
PWM_INIT_DELTA) Y OTRA CUANDO OCURRE OVERFLOW.

ADEMAS CONFIGURA EL PIN DE LA SEÑAL PWM COMO SALIDA E
INICIALIZA EL MISMO EN ALTO PARA USAR EL PWM EN MODO
NO INVERTIDO.
********************************************************/
void PWM_soft_Init()
{
	TCCR0A = 0; // Modo normal
	TCCR0B = (1 << CS00); // Prescaler 1
	OCR0A = PWM_INIT_DELTA;
	TIMSK0 = (1 << OCIE0A) | (1 << TOIE0);
	
	PWM_START;
	PWM_ON;
}

ISR(TIMER0_COMPA_vect)
{	
	PWM_OFF;
}

ISR(TIMER0_OVF_vect)
{
	PWM_ON;
}