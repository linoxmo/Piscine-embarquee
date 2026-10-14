#include <avr/io.h>
#include <util/delay.h>


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
    DDRD &= ~(1 << DDD2) & ~(1 << DDD4);  
    // Configuration of Port D's 2 and 4 pins in entree mode 
    PORTD |= (1 << PORTD2) | (1 << PORTD4); 
    // For pull up effect
    
    int compteur  = 1;  
    // hexa count between 0 and 15
    int btn1_precedent = 0; 
    int btn2_precedent = 0;
    //button gestion
    while(1)
    {
        int btn1_now = !(PIND & (1 << PIND2));
        int btn2_now = !(PIND & (1 << PIND4));
        // First Button
        if (btn1_now && !btn1_precedent) 
        {
            _delay_ms(20);
            
            btn1_precedent = 1;
        }
        
        if (!btn1_now && btn1_precedent) 
        {    
            _delay_ms(20); 
            if (compteur < 10)
                compteur += 1;
            btn1_precedent = 0;
        }

        // Second Button
        if (btn2_now && !btn2_precedent) 
        {
            _delay_ms(20);
            
            btn2_precedent = 1;
        }

        if (!btn2_now && btn2_precedent)
        {
            _delay_ms(20); 
            if (compteur > 1)
                compteur = compteur - 1;
            btn2_precedent = 0;
        }
        OCR1A = 6250 * compteur;

    }
}