#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << DDB1);
    PRR &= ~(1 << PRTIM1);
   
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13); 

    ICR1 = 62499;
    OCR1A = 6250 ; 

    TCCR1B |= (1 << CS12);

    while (1)
    {
    }
}
