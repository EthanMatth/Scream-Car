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

  uint16_t value0;
  uint16_t value1;

  while(1)
  {
    
    value0 = ADC_analogRead(A0);
    value1 = ADC_analogRead(A1);
    
    serial_print("Value 0: ");
    serial_int(value0);
    serial_print(" Value 1: ");
    serial_int(value1);
    serial_send('\n');
    _delay_ms(100);
  }

  return 0;
}