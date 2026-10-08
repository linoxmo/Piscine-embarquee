#include <avr/io.h>


int main(void)
{
    DDRB |= (1 << DDB0);
    // Configuration in exit mode (1) of Port B's pin 0 
    PORTB |= (1 << PORTB0);
    // Turn on port 0 in  mode 1 (5 v) 
}