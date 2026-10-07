#include <avr/io.h>

int main()
{
    DDRB |= ( 1 << PB1);
    while(1){
        for(volatile uint32_t  i = 0; i < 225000; i++)
        ;
        PORTB ^= (1 << PB1);
        
    }
}