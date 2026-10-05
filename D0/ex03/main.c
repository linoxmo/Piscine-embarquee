#include "F_cpu.h"
#include <avr/io.h>
#include <util/delay.h>



int main(void){

    DDRB |= (1 << DDB0); // Configuration en mode SORTIE (1 en binaire) du port 0  
    DDRD &= ~(1 << DDD2); // Configuration en mode Entree (0 en binaire) du port 1
    PORTD |= (1 << PORTD2);

    int i = 0;
    int compteur  = 0;
    int btn_precedent = 0;

    while(1)
    {   
         int btn_now = !(PIND & (1 << PIND2));

        if (btn_now && !btn_precedent) 
        {
            _delay_ms(20);
            
            btn_precedent = 1;
        }

        if (!btn_now && btn_precedent) {
            _delay_ms(20); // Temporisation de 20ms
            i = i + 1; 
            if (i == 1) {
                // On a détecté la fermeture et l'ouverture du BP
                PORTB |= (1 << PORTB0);
                compteur = compteur + 1;
            }
            if (i == 2) {
                // On a détecté la fermeture et l'ouverture du BP
                PORTB &= ~(1 << PORTB0);
                compteur = compteur + 1;
                i = 0;
            }
            btn_precedent = 0; // On mémorise que le bouton est relâché
        }

    }
    return (0);
}
