#ifndef RGB_H
#define RGB_H

#include <avr/io.h>
#include <avr/interrupt.h>

// Definiciones de pines y puertos
#define PWM_PIN_R 5			// Pin de salida de la señal PWM
#define PWM_PIN_G 2			// Pin de salida de la señal PWM
#define PWM_PIN_B 1			// Pin de salida de la señal PWM
#define PWM_PORT PORTB		// Puerto de la señal PWM

#define PWM_SOFT_OFF		PWM_PORT &= ~(1 << PWM_PIN_R)		// Pone el pin de la señal en bajo
#define PWM_SOFT_ON			PWM_PORT |= (1 << PWM_PIN_R)		// Pone el pin de la señal en alto

// Declaraciones de funciones
void RGB_Init(uint8_t , uint8_t , uint8_t);
void RGB_SetValues(uint8_t , uint8_t , uint8_t);

#endif // RGB_H