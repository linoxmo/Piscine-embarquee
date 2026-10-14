#include <avr/io.h>

#ifndef LED_H  
#define LED_H

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color_t;

#define init_RGB()\
DDRD |= (1 << DDD3) | (1 << DDD5) | (1 << DDD6)

#endif