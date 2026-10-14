
#include <avr/io.h>

#ifndef TIMER0_H  
#define TIMER0_H

#define F_CPU 16000000UL 

#define Ft_CalTop0(time_seconds, prescaler) (uint8_t)(((F_CPU * (time_seconds)) / (prescaler)) - 1)

typedef enum{
    PRESCALER0_NONE = 0,
    PRESCALER0_1    = (1 << CS00),
    PRESCALER0_8    = (1 << CS01),
    PRESCALER0_64   = (1 << CS01) | (1 << CS00),
    PRESCALER0_256  = (1 << CS02),
    PRESCALER0_1024 = (1 << CS02) | (1 << CS00)
} Prescaler0_t;


#define initiate_CTC_OCRA(Top, Prescaler) \
    do { \
        TCCR0A = (1 << COM0A0) | (1 << WGM01); \
        OCR0A  = (uint8_t)(Top); \
        TCCR0B = (Prescaler); \
    } while(0)


#define initiate_FastPWM_OCRA(Top, Pourcentage, Prescaler) \
    do { \
        TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1 << WGM00); \
        TCCR0B = (1 << WGM02)  | (Prescaler); \
        OCR0A  = (uint8_t)(Top); \
        OCR0B  = (uint8_t)Pourcentage; \
    } while(0)

#define initiate_FastPWM_Dual_Timer0(Prescaler) \
    do { \
        TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00); \
        TCCR0B = (Prescaler); \
    } while(0)

#endif
