#ifndef ADC_H_
#define ADC_H_

void ADC_init(); // Initializes ADC with right justification, 1.1V reference, and interrupt enabled
uint16_t ADC_analogRead();
void ADC_start();


#endif /* ADC_H_ */