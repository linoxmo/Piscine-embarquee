
#include <avr/io.h>

#ifndef TIMER2_H  
#define TIMER2_H

#define F_CPU 16000000UL 

#define Ft_CalTop0(time_seconds, prescaler) (uint8_t)(((F_CPU * (time_seconds)) / (prescaler)) - 1)

typedef enum{
    PRESCALER2_NONE = 0,
    PRESCALER2_1    = (1 << CS20),
    PRESCALER2_8    = (1 << CS21),
    PRESCALER2_64   = (1 << CS21) | (1 << CS20),
    PRESCALER2_256  = (1 << CS22),
    PRESCALER2_1024 = (1 << CS22) | (1 << CS20)
} Prescaler2_t;


#define initiate_CTC_OCRA_2(Top, Prescaler) \
    do { \
        TCCR2A = (1 << COM2A0) | (1 << WGM21); \
        OCR2A  = (uint8_t)(Top); \
        TCCR2B = (Prescaler); \
    } while(0)


#define initiate_FastPWM_OCRA_2(Top, Pourcentage, Prescaler) \
    do { \
        TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20); \
        TCCR2B = (1 << WGM22)  | (Prescaler); \
        OCR2A  = (uint8_t)(Top); \
        OCR2B  = (uint8_t)Pourcentage; \
    } while(0)

#define initiate_FastPWM8_Timer2(Prescaler) \
    do { \
        TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20); \
        TCCR2B = (Prescaler); \
    } while(0)

#endif

