/*
 * CDyM-TP04.c
 *
 * Created: 22/7/2024 20:06:53
 * Author : Estanislao Carrer, Fernando Ramirez, Lisandro Martinez
 */ 

#include "main.h"
#include "serialPort.h"		//	Comunicacion serie por UART
#include "ADC.h"			//	Conversion analogica a digital del voltaje del potenciometro 
#include "RGB.h"			//	Manejo de los colores del LED RGB

void MAIN_init(void);

#define BR9600 (0x67)		//	0x67=103 configura BAUDRATE=9600@16MHz

char startup_msg[] =
"****   Control de un LED RGB ****\r\n"
"Desarrollado por Estanislao Carrer, Fernando Ramirez, Lisandro Martinez\r\n"
"\r\n"
"INSTRUCCIONES:\r\n"
"Para configurar la proporcion de ROJO presione 'R', 'G' para el VERDE y 'B' para el AZUL\r\n"
"Ajuste el potenciometro para obtener el valor deseado luego de seleccionar el color\r\n"
"\r\n"
"Presione 'R', 'G' o 'B' para setear algun color...\r\n\r\n";

char red_msg[] = "Ajustando proporcion de ROJO\r\n";
char green_msg[] = "Ajustando proporcion de VERDE\r\n";
char blue_msg[] = "Ajustando proporcion de AZUL\r\n";

volatile uint8_t RX_Buffer = 0;		// Almacena el caracter recibido por teclado

uint8_t color_values[3] = {0, 0, 0};
volatile uint8_t color_sel = 0;

volatile char* msg;					// Mensaje a transmitir
volatile uint16_t msg_index = 0;
volatile char* next_msg;			// Mensaje solicitado para transmitir
volatile uint8_t print_req = 0;		// Indica si hay un pedido para transmitir un mensaje
volatile uint8_t print_free = 1;	// Indica si el puerto esta libre para transmitir un mensaje (no hay un mensaje siendo transmitido)

int main(void)
{
    /* Replace with your application code */
	MAIN_init();
	
    while (1) 
    {	
		if(print_req && print_free) 
		{
			
			print_req = 0;
			print_free = 0;
			msg = next_msg;
			SerialPort_TX_Interrupt_Enable();
		}
    }
}

void MAIN_init(){
	SerialPort_Init(BR9600); 			// Inicializar formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();				// Activar el Transmisor del Puerto Serie
	SerialPort_RX_Enable();				// Activar el Receptor del Puerto Serie
	SerialPort_RX_Interrupt_Enable();	// Activar Interrupción de recepcion
	
	// Configurar mensaje de bienvenida
	next_msg = startup_msg;
	print_req = 1;
	
	ADC_Init();
	ADC_Read();
	ADC_EnableInt();
	ADC_EnableAT();
	
	uint8_t initial_value = ADC_GetData();
	color_values[0] = initial_value;
	color_values[1] = initial_value;
	color_values[2] = initial_value;
	RGB_Init(initial_value, initial_value, initial_value);
	
	sei();
	ADC_StartConversion();
}

// Rutina de Servicio de Interrupción de Byte Recibido
ISR(USART_RX_vect)
{
	RX_Buffer = UDR0;
	if(RX_Buffer == 'R')
	{
		color_sel = 0;
		next_msg = red_msg;
	}
	else if(RX_Buffer == 'G')
	{
		color_sel = 1;
		next_msg = green_msg;
	}
	else if(RX_Buffer == 'B')
	{
		color_sel = 2;
		next_msg = blue_msg;
	}
	print_req = 1;
}

ISR(USART_UDRE_vect)
{
	if(msg[msg_index] != '\0')
	{
		SerialPort_Send_Data(msg[msg_index]);
		msg_index++;
	}
	else
	{
		msg_index = 0;
		SerialPort_TX_Interrupt_Disable();
		print_free = 1;
	}
}

ISR(ADC_vect)
{
	color_values[color_sel] = ADC_GetData();
	RGB_SetValues(color_values[0], color_values[1], color_values[2]);
}