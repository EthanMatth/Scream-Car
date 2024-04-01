#ifndef ADC_H_
#define ADC_H_

volatile static uint8_t conversion_done = 0;

unsigned char adcl;
unsigned char adch;

void ADC_init(); // Initializes ADC with right justification, 1.1V reference, and interrupt enabled
uint16_t ADC_analogRead();
void ADC_start();


#endif /* ADC_H_ */