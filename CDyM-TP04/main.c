/*
 * CDyM-TP04.c
 *
 * Created: 22/7/2024 20:06:53
 * Author : Estanislao Carrer, Fernando Ramirez, Lisandro Martinez
 */ 

#include "main.h"
#include "serialPort.h" //Comunicacion serie por UART

void MAIN_init(void);

#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz
volatile uint8_t RX_Buffer = 0;
volatile uint8_t red_on = 0;
volatile uint8_t green_on = 1;
volatile uint8_t blue_on = 0;

int main(void)
{
    /* Replace with your application code */
	MAIN_init();
	
    while (1) 
    {
		PORTB = (red_on << PORTB5) | (green_on << PORTB2) | (blue_on << PORTB1);
    }
}

void MAIN_init(){
	SerialPort_Init(BR9600); 			// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_RX_Enable();				// Activo el Receptor del Puerto Serie
	SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion
	
	// Configurar salidas para los pines del LED RGB
	DDRB = (1 << PORTB5) | (1 << PORTB2) | (1 << PORTB1);
	PORTB = (red_on << PORTB5) | (green_on << PORTB2) | (blue_on << PORTB1);
	
	sei();
}

// Rutina de Servicio de Interrupción de Byte Recibido
ISR(USART_RX_vect)
{
	RX_Buffer = UDR0;
	if(RX_Buffer == 'R')
	{
		red_on = !red_on;
	}
	else if(RX_Buffer == 'G')
	{
		green_on = !green_on;
	}
	else if(RX_Buffer == 'B')
	{
		blue_on = !blue_on;
	}
}

