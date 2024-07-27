/*
 * CDyM-TP04.c
 *
 * Created: 22/7/2024 20:06:53
 * Author : Estanislao Carrer, Fernando Ramirez, Lisandro Martinez
 */ 

#include "main.h"
#include "terminal.h"		//	Comunicacion con la terminal
#include "ADC.h"			//	Conversion analogica a digital del voltaje del potenciometro 
#include "RGB.h"			//	Manejo de los colores del LED RGB

void MAIN_init(void);

const char startup_msg[] =
"****   Control de un LED RGB ****\r\n"
"Desarrollado por Estanislao Carrer, Fernando Ramirez, Lisandro Martinez\r\n"
"\r\n"
"INSTRUCCIONES:\r\n"
"Para configurar la proporcion de ROJO presione 'R', 'G' para el VERDE y 'B' para el AZUL\r\n"
"Ajuste el potenciometro para obtener el valor deseado luego de seleccionar el color\r\n"
"\r\n"
"Presione 'R', 'G' o 'B' para setear algun color...\r\n\r\n";

const char* color_msg[3] = {
	(char *) "Ajustando proporcion de ROJO\r\n",
	(char *) "Ajustando proporcion de VERDE\r\n",
	(char *) "Ajustando proporcion de AZUL\r\n"
};

volatile uint8_t color_values[3] = {0, 0, 0};	// Valor de cada color {R, G, B}
volatile uint8_t color_sel = 0;					// Valor ajustado actualmente
volatile uint8_t last_char = 'R';				// Ultimo caracter presionado

int main(void)
{
	MAIN_init();
	
    while (1) 
    {	
    }
}

void MAIN_init(){
	TERMINAL_Init();
	
	// Transmitir mensaje de bienvenida
	TERMINAL_EnqueueMessage(startup_msg);
	
	// Indicar color ajustado inicialmente
	TERMINAL_EnqueueMessage(color_msg[color_sel]);
	
	// Inicializar ADC. Habilitar su interrupcion y el auto-trigger
	ADC_Init();
	ADC_EnableInt();
	ADC_EnableAT();
	
	// Poner todos los colores en su maxima proporcion
	RGB_Init(0, 0, 0);
	
	sei();
	ADC_StartConversion();
}

/***************************************************************************
	Esta interrupcion recibe el caracter presionado y establece que color se
	desea ajustar de acuerdo al mismo, ademas de mandar a imprimir el
	correspondiente aviso en la terminal.
	
	Cualquier otra caracter aparte de 'R', 'G' o 'B' no se tiene en cuenta,
	al igual que cualquier recepcion sucesiva de estos caracteres.
****************************************************************************/
ISR(USART_RX_vect)
{
	uint8_t received_char = UDR0;
	if(last_char != received_char && ((received_char == 'R') | (received_char == 'G') | (received_char == 'B')))
	{
		last_char = received_char;
		if(last_char == 'R')
		{
			color_sel = 0;
		}
		else if(last_char == 'G')
		{
			color_sel = 1;
		}
		else if(last_char == 'B')
		{
			color_sel = 2;
		}
		TERMINAL_EnqueueMessage(color_msg[color_sel]);
	}
}


/***************************************************************************
	Esta interrupcion recibe el caracter presionado y establece que color se
	desea ajustar de acuerdo al mismo, ademas de mandar a imprimir el
	correspondiente aviso en la terminal.
	
	Cualquier otra caracter aparte de 'R', 'G' o 'B' no se tiene en cuenta,
	al igual que cualquier recepcion sucesiva de estos caracteres.
****************************************************************************/
ISR(ADC_vect)
{
	color_values[color_sel] = ADC_GetData();
	RGB_SetValues(color_values[0], color_values[1], color_values[2]);
}