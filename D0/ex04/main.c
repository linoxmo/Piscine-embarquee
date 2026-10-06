#include "F_cpu.h"
#include <avr/io.h>
#include <util/delay.h>



int main(void){

    // Configuration en mode sortie des 4 LED
    DDRB |= (1 << DDB0) |  (1 << DDB1) | (1 << DDB2) | (1 << DDB4); // mets les pins 0,1,2,4 du Port B en sortie 

    DDRD &= ~(1 << DDD2) & ~(1 << DDD4);  // met les pins 2 et 4 du Port D en entree (en 0)
    PORTD |= (1 << PORTD2) | (1 << PORTD4); // evite l'effet pull up sur les boutons 2 et 4 

    
    int compteur  = 0;  // compteur allant de 0 a 15 pour tous les hexa
    int btn1_precedent = 0; // gestion des bouttons comme sr l'exo 3
    int btn2_precedent = 0; //gestion des boutons comme sur l'exo 3

    while(1)
    {   
        int btn1_now = !(PIND & (1 << PIND2));
        int btn2_now = !(PIND & (1 << PIND4));
        
        // Premier Bouton
        if (btn1_now && !btn1_precedent) 
        {
            _delay_ms(20);
            
            btn1_precedent = 1;
        }
        
        if (!btn1_now && btn1_precedent) 
        {    
            _delay_ms(20); 
            if (compteur < 15)
                compteur += 1;
            btn1_precedent = 0;
        }

        // Deuxieme Bouton
        if (btn2_now && !btn2_precedent) 
        {
            _delay_ms(20);
            
            btn2_precedent = 1;
        }

        if (!btn2_now && btn2_precedent) 
        {
            _delay_ms(20); 
            if (compteur > 0)
                compteur = compteur - 1;
            btn2_precedent = 0;
        }

        // Gestion de la LED 1 
        if ((compteur >> 0) & 1) {
            PORTB |= (1 << PORTB0);  // Allume PB0 si le bit 0 vaut 1
        }
        else {
            PORTB &= ~(1 << PORTB0); // Éteint PB0 si le bit 0 vaut 0
        }

        // Gestion de la LED 2
        if ((compteur >> 1) & 1) {
            PORTB |= (1 << PORTB1);  // Allume PB1 si le bit 1 vaut 1
        } else {
            PORTB &= ~(1 << PORTB1); // Éteint PB1 si le bit 1 vaut 0
        }

        // Gestion de la LED 3 
        if ((compteur >> 2) & 1) {
            PORTB |= (1 << PORTB2);  // Allume PB2 si le bit 2 vaut 1
        } else {
        PORTB &= ~(1 << PORTB2); // Éteint PB2 si le bit 2 vaut 0
        }

        // Gestion de la LED 4 (Bit 3 du com)
        if ((compteur >> 3) & 1) {
            PORTB |= (1 << PORTB4);  // Allume PB4 si le bit 3 vaut 1
        } else {
            PORTB &= ~(1 << PORTB4); // Éteint PB4 si le bit 3 vaut 0
        }
    }
    return 0;
    }
