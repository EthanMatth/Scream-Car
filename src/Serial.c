/*
 * CFile1.c
 *
 * Created: 3/16/2024 9:23:16 PM
 *  Author: ethan
 */ 
#include <avr/io.h>
#include "Serial.h"

void serial_init()
{
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0L = 103;
}

void serial_send(unsigned char c)
{
	while(!(UCSR0A & (1 << UDRE0))) {}
	UDR0 = c;
}

void serial_print(char str[])
{
	char i = 0;
	while(str[i])
	{
		serial_send(str[i++]);
	}
}

void serial_int(uint16_t n)
{
	if(n == 0) 
	{ 
		serial_send('0');
		return;
	}
	char buffer[10];
	int length = 0;
	while(n)
	{
		buffer[length++] = '0' + (n % 10);
		n /= 10;
	}
	length--;
	for(;length >= 0; length--)
	{
		serial_send(buffer[length]);
	}
}

