#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Serial.h"
#include "ADC.h"

int main()
{
  serial_init();
  ADC_init();
  sei();
  //unsigned char adcl;
  DDRC &= ~(1 << 0);

  uint16_t value;

  while(1)
  {
    
    value = ADC_analogRead();
    
    serial_int(value);
    serial_send('\n');
    _delay_ms(100);
  }

  return 0;
}