#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << DDB1);
    PRR &= ~(1 << PRTIM1);
    // 1. Configuration of the PB1 pin in exit mode.
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS12); 
    /* 
     2. Configuration in comparaison mode of the COM1A) pin (Compare Match Output Mode)
     The COM1A0 put at 1 with the WGM11/ WGM12 /WMG13 at one will trigger the fast pmw mode
     with a 256 prescaler
     */
    ICR1 = 62499;
    OCR1A = 6250;
    /*3. Definition of the max value of the timer.
     For an 16 MHz clock and a prescaler of 256.
     We have : OCR1A=16 000 000 /( prescaler = 256 * 2 - 1) = 31249  
     wich generate a signal of 1 seconds (at 1 Hz Frequency).
    */ 
    while (1)
    {
    }
}
