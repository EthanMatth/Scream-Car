#ifndef SERIAL_H_
#define SERIAL_H_

void serial_init();
void serial_send(unsigned char c);
void serial_print(char str[]);
void serial_int(uint16_t n);

#endif /* SERIAL_H_ */