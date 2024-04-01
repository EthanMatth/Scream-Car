#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC.h"



ISR(ADC_vect)
{
    conversion_done = 1;
}


void ADC_init()
{
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, Set clk/128
    ADMUX = (1 << REFS0); // Reverence voltage internal VCC
}

void ADC_start()
{
    ADCSRA |= (1 << ADSC); // Starts ADC
}

uint16_t ADC_analogRead()
{
    conversion_done = 0;
    ADC_start();

    while(!conversion_done); // Wait for conversion to complete

    // For some reason can't use registers directly
    adcl = ADCL;
    adch = ADCH;

    return ((adch << 8) | (adcl));
    
}