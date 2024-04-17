#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Serial.h"
#include "ADC.h"

#define numOfSensors 4

char threshold = 1;

uint16_t max[] = {0, 0, 0, 0};
uint16_t min[] = {1024, 1024, 1024, 1024};
uint16_t sample[numOfSensors];


void TimerSetup()
{
  TIMSK1 = (1 << OCIE1A);
  TCNT1 = 0;
  OCR1A = 6250 - 1;
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12);
}

int main()
{
  DDRC &= ~(0b1111 << 0); 
  
  serial_init();
  ADC_init();
  TimerSetup();

  while(1)
  {
    for(unsigned char i = 0; i < numOfSensors; i++)
    {
      
      sample[i] = ADC_analogRead(i);
      
      if(sample[i] > max[i]) max[i] = sample[i];
      if(sample[i] < min[i]) min[i] = sample[i];
    }
  
  }
}

ISR(TIMER1_COMPA_vect)
{
  for(unsigned char i = 0; i < numOfSensors; i++)
  {
    if(1)
    {
      serial_print("Level ");
      serial_int(i);
      serial_print(": ");
      serial_int(max[i] - min[i]);
      serial_send('\t');
    }
  }
  
  serial_send('\n');
  TCNT1 = 0;

  for(unsigned char i = 0; i < numOfSensors; i++)
  {
    min[i] = 1024;
    max[i] = 0;
  }
}


