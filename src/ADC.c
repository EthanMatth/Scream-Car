#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC.h"

volatile static uint8_t conversion_done = 0;

ISR(ADC_vect)
{
    conversion_done = 1;
}


void ADC_init()
{
    
}

void ADC_start()
{
    
}

uint16_t ADC_analogRead()
{
    
    
}