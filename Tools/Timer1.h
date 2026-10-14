#include <avr/io.h>

#ifndef Timer1_H
#   define Timer1_H

#define F_CPU 16000000UL
#define Baudrate 115200
#define Ft_CalTop(time_ms, prescaler) (uint16_t)(((F_CPU * (time_ms)) / (prescaler))- 1)

typedef enum {
    PRESCALER1_NONE = 0, // Timer arrêté
    PRESCALER1_1    = (1 << CS10),
    PRESCALER1_8    = (1 << CS11),
    PRESCALER1_64   = (1 << CS11) | (1 << CS10),
    PRESCALER1_256  = (1 << CS12),
    PRESCALER1_1024 = (1 << CS12) | (1 << CS10)
} Prescaler1_t;

#define iniate_CTC_OCR1A(Top, Prescaler) \
do{ \
    TCCR1A = (1 << COM1A0) \
    OCR1A = TOP \
    TCCR1B = (1 << WGM12) | (Prescaler) \
} while(0)

#define iniate_FastPMW_ICR1(Top, Prescaler, Pourcentage) \
do{\
TCCR1A |= (1 << COM1A1) | (1 << WGM11)\
TCCR1B |= (1 << WGM12) | (1 << WGM13) | (Prescaler)\
ICR1 = Top\
OCR1A = Pourcentage\
}while(0)

#define initiate_FastPWM8_Timer1(Prescaler) \
    do { \
        TCCR1A = (1 << COM1A1) | (1 << WGM10); \
        TCCR1B = (1 << WGM12) | (Prescaler); \
    } while(0)

#endif
