#include <avr/io.h>


int main(void)
{
    DDRB |= (1 << DDB0);
    /* Configuration en mode SORTIE ( 1 en binaire ) de la broche ) du Port B
    */
    PORTB |= (1 << PORTB0);
    /* Allumage du port 0 en  mode 1 (5 v) */
}