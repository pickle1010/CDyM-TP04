/*
 * RGB.h
 *
 * Created: 24/7/2024 03:00:00
 * Author : Estanislao Carrer, Fernando Ramirez, Lisandro Martinez
 */ 

#ifndef RGB_H
#define RGB_H

#include <avr/io.h>
#include <avr/interrupt.h>

// Definiciones de pines y puertos
#define PWM_PIN_R 5			// Pin de salida de la señal PWM para el color ROJO
#define PWM_PIN_G 2			// Pin de salida de la señal PWM para el color VERDE
#define PWM_PIN_B 1			// Pin de salida de la señal PWM para el color AZUL
#define PWM_PORT PORTB		// Puerto de las señales PWM

// Declaraciones de funciones
void RGB_Init(uint8_t , uint8_t , uint8_t);
void RGB_SetValues(uint8_t , uint8_t , uint8_t);

#endif // RGB_H