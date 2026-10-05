#include <avr/io.h>


int main(void){

    DDRB |= (1 << DDB0); // Configuration en mode SORTIE (1 en binaire) du port 0  
    DDRD &= ~(1 << DDD2); // Configuration en mode Entree (0 en binaire) du port 1
    PORTD |= (1 << PORTD2);
    while(1)
    {   
        /* On utilise PINB pour lire l'etat d'un Pin*/
        if (!(PIND & (1 << PIND2))) 
        {
            PORTB |= (1 << PORTB0);
        /* Allumage du port 0 */
        }
        else
            {
            PORTB &= ~(1 << PORTB0);
            /* Eteint le port 0 */
            }
        
    }
    return (0);
}