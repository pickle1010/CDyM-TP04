#include "terminal.h"

static volatile const char* msg;			// Mensaje a transmitir
static volatile uint16_t msg_index = 0;
static volatile const char* next_msg;		// Mensaje encolado para ser transmitido
static volatile uint8_t requests = 0;		// Indica si hay un pedido para transmitir un mensaje
static volatile uint8_t freeTX = 1;			// Indica si el puerto esta libre para transmitir un mensaje (no hay un mensaje siendo transmitido)

void TERMINAL_Init()
{
	SerialPort_Init(BAUD_RATE); 		// Inicializar formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();				// Activar el Transmisor del Puerto Serie
	SerialPort_RX_Enable();				// Activar el Receptor del Puerto Serie
	SerialPort_RX_Interrupt_Enable();	// Activar Interrupción de recepcion
}

void TERMINAL_EnqueueMessage(const char* message)
{
	next_msg = message;
	requests = 1;
	if(freeTX)
	{
		requests = 0;
		freeTX = 0;
		msg = next_msg;
		SerialPort_TX_Interrupt_Enable();
	}
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
		if(requests)
		{
			msg = next_msg;
			requests = 0;
		}
		else
		{
			SerialPort_TX_Interrupt_Disable();
			freeTX = 1;
		}
	}
}