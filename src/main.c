#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Serial.h"
#include "ADC.h"

uint16_t max1, max2;
uint16_t min1, min2;
uint16_t sample1, sample2;
char threshold = 100;

int main()
{
  DDRC &= ~(1 << 0);  
  serial_init();
  ADC_init();

  TIMSK1 = (1 << OCIE1A);
  TCNT1 = 0;
  OCR1A = 3125 - 1;
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12);

  max1 = max2 = 0;
  min1 = min2 = 1024;

  while(1)
  {
    sample1 = ADC_analogRead(A0);
    sample2 = ADC_analogRead(A1);

    if(sample1 > 1024) continue;
    if(sample1 > max1) max1 = sample1;
    if(sample1 < min1) min1 = sample1;

    if(sample2 > 1024) continue;
    if(sample2 > max2) max2 = sample2;
    if(sample2 < min2) min2 = sample2;
  }
}

ISR(TIMER1_COMPA_vect)
{
  if((max1 - min1) > threshold)
  {
    serial_print("Level 1: ");
    serial_int(max1 - min1);
  }
  if((max2 - min2) > threshold)
  {
    serial_print(" Level 2: ");
    serial_int(max2 - min2);
  }
  serial_send('\n');
  TCNT1 = 0;

  min1 = min2 = 1024;
  max1 = max2 = 0;
}


