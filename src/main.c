#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Serial.h"
#include "ADC.h"

#define numOfSensors 4

char threshold = 100;

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

void MotorControl(unsigned char dir)
{
  serial_int(dir); // I tried to remove these print statements and it stopped working
  serial_send('\n');
  if(dir > 5) return;
  else PORTB |= (1 << dir);
}

int main()
{
  DDRC &= ~(0b1111); 
  DDRB |= (0b1111);
  
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
  PORTB = 0x00;
  char loudestSensor = -1;
  uint16_t loudest = 0;
  for(unsigned char i = 0; i < numOfSensors; i++)
  {
    uint16_t noise = max[i] - min[i];
    if(noise < threshold) continue;
    if(noise < loudest) continue;
    loudest = noise;
    loudestSensor = i;
  }

  MotorControl(loudestSensor);


 for(unsigned char i = 0; i < numOfSensors; i++)
  {
    min[i] = 1024;
    max[i] = 0;
  }

  TCNT1 = 0;
}


