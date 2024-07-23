
#include <avr/io.h>
#include <avr/interrupt.h>


/*METODOS ADC*/
void ADC_Init(void);
void ADC_Read(void);

/*GETTERS-SETTERS*/

void adc_setFlag (uint8_t f);

uint8_t adc_getFlag(void);

uint8_t adc_getData(void);
