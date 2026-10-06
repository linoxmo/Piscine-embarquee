#include <avr/io.h>


int main(void){

    DDRB |= (1 << DDB0); // Configuration en mode SORTIE (1 en binaire) de la broche 0 du Port B
    DDRD &= ~(1 << DDD2); // Configuration en mode Entree (0 en binaire) de la broche 2 d Port D
    // On prend le chiffre 1 en binaire (00000001) et on décale le bit de 2 positions vers la gauche. On obtient le masque binaire suivant : 00000100
    PORTD |= (1 << PORTD2); // evite l'effet pull up en allumant une resistance
    // On prend le chiffre 1 en binaire (00000001) et on décale le bit de 2 positions vers la gauche. On obtient le masque binaire suivant : 00000100
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