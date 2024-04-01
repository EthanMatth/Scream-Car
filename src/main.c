#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Serial.h"

int main()
{
  serial_init();
  //unsigned char adcl;
  DDRC &= ~(1 << 0);

  unsigned char adcl;
  unsigned char adch;

  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADMUX = (1 << REFS0);

  while(1)
  {
    ADCSRA |= (1 << ADSC);

    while((ADCSRA & (1 << ADIF)) == 0);
    ADCSRA |= (1 << ADIF);

    adcl = ADCL;
    adch = ADCH;
    
    serial_int((adch << 8) | (adcl));
    serial_send('\n');
    _delay_ms(100);
  }


  return 0;
}