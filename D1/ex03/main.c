#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB |= (1 << DDB1);
    PRR &= ~(1 << PRTIM1);
   
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13); 

    ICR1 = 62499;
    OCR1A = 6250 ; 

    TCCR1B |= (1 << CS12);

    int compteur  = 1;  // compteur allant de 0 a 15 pour tous les hexa
    int btn1_precedent = 0; // gestion des bouttons comme sr l'exo 3
    int btn2_precedent = 0;

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