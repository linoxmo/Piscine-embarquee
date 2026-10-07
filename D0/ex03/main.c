#include <avr/io.h>
#include <util/delay.h>



int main(void){

    DDRB |= (1 << DDB0); // Configuration en mode SORTIE (1 en binaire) du port 0  
    DDRD &= ~(1 << DDD2); // Configuration en mode Entree (0 en binaire) du port 1
    PORTD |= (1 << PORTD2); // evite l'effet pull up

    bool s = false; //
    int btn_precedent = 0; //sauvegarde l'etat precedent du bouton, 0 = pas enfonce, 1 = enfonce

    while(1)
    {   
         int btn_now = !(PIND & (1 << PIND2));

        if (btn_now && !btn_precedent) 
        {
            _delay_ms(20); //temporise d 20ms
            
            btn_precedent = 1; // btn_d'avant devient enfonce
        }

        if (!btn_now && btn_precedent) {
            _delay_ms(20); // Temporisation de 20ms
            s = !s; 
            if (s) {
                // On a détecté la fermeture et l'ouverture du BP
                PORTB |= (1 << PORTB0);
            }
            else {
                // On a détecté la fermeture et l'ouverture du BP
                PORTB &= ~(1 << PORTB0);
            }
            btn_precedent = 0; // On mémorise que le bouton est relâché
        }

    }
    return (0);
}
