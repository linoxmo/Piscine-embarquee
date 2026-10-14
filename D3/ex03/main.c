#include <util/delay.h>
#include "Timer0.h"
#include "Timer2.h"
#include "UART.h"
#include "LED.h"
#include "Tools.h"

void init_setup(void) {
    uint16_t ubrr_value = (F_CPU / 8UL / UART_BAUDRATE - 1);
    init_RGB();
    uart_init_Double_speed(ubrr_value);
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    OCR0B = r;  
    OCR0A = g;  
    OCR2B = b;  
}

void parsing(void) {
    int i = 0;
    char color[8]; // 7 caractères + le '\0'

    // 1. Lecture des 7 caractères (#RRGGBB)
    while (i < 7) {
        char c = uart_rx();
        uart_tx(c); // Écho

        if (i == 0) {
            if (c != '#') {
                uart_printstr("\n\rYou should begin with a # as the format asked it \n\r");
                return; // Sort de la fonction en cas d'erreur
            }
        } else {
            // Accepte les chiffres et les lettres (majuscules et minuscules)
            if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) {
                color[i] = c;
            } else {
                uart_printstr("\n\rCharacter should be in Hexa 0-F \n\r");
                return;
            }
        }
        i++;
    }
    color[7] = '\0'; // Fin de chaîne

    // 2. Extraction des valeurs RGB
    uint8_t tab[3];
    char temp[3];
    temp[2] = '\0'; // Le dernier caractère sera toujours '\0'

    // Extraction du Rouge (caractères 1 et 2)
    temp[0] = color[1];
    temp[1] = color[2];
    tab[0] = (uint8_t)htoi(temp);

    // Extraction du Vert (caractères 3 et 4)
    temp[0] = color[3];
    temp[1] = color[4];
    tab[1] = (uint8_t)htoi(temp);

    // Extraction du Bleu (caractères 5 et 6)
    temp[0] = color[5];
    temp[1] = color[6];
    tab[2] = (uint8_t)htoi(temp);

    uart_printstr("\n\r"); // Petite nouvelle ligne propre après la saisie
    set_rgb(tab[0], tab[1], tab[2]);
}

int main(void) {
    init_setup();
    
    while (1) {
        uart_printstr("Please enter a color in #RRGGBB format: ");
        parsing();
        _delay_ms(20);
    }
    
    return 0;
}