#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << DDB1);
    PRR &= ~(1 << PRTIM1);
    // 1. Configuration of the PB1 pin in exit mode.
    /* 
     2. Configuration in comparaison mode of the COM1A) pin (Compare Match Output Mode)
     The COM1A0 put at 1, the TCCR1A configure the pin OC1A to change states when the time is
     reached
     */
    TCCR1A = (1 << COM1A0);
    /* 
     3. Definition of the max value of the timer.
     For an 16 MHz clock and a prescaler of 256.
     We have : OCR1A=16 000 000 /( prescaler = 256 * 2 - 1) = 31249  
     wich generate a signal of 1 seconds (at 1 Hz Frequency).
     */
    OCR1A = 31249;
    /* 
    4. Configuration of CTC mode and Prescaler
    - WGM12 = 1 : Activate the mode CTC (Clear Timer on Compare Match) 
    - CS12 = 1 and  (CS10 and CS11 == 0) set the horloge with 256 prescaler 
    */
    TCCR1B = (1 << WGM12) | (1 << CS12);
    while (1)
    {
    }
}

