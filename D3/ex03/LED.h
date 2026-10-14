#include <avr/io.h>

#ifndef LED_H  
#define LED_H

#define UART_BAUDRATE 115200

#define init_RGB()\
DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6)

#endif