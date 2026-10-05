#include <avr/io.h>


int main(void)
{
    DDRB |= (1 << DDB0);
    /* Configuration en mode SORTIE ( 1 en binaire ) du port 0  
    Peux etre appele PB0
    */
    PORTB |= (1 << PORTB0);
    /* Allumage du port 0 en  mode 1 (5 v)
    */
}