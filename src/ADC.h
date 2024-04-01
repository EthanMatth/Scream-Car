#ifndef ADC_H_
#define ADC_H_

volatile static uint8_t conversion_done = 0;

enum AnalogPin {A0, A1, A2, A3, A4, A5, A6, A7}; // Enumerated variable for analog pin to useS

unsigned char adcl;
unsigned char adch;

void ADC_init(); // Initializes ADC with right justification, 1.1V reference, and interrupt enabled
uint16_t ADC_analogRead(char pin);
void ADC_start();


#endif /* ADC_H_ */