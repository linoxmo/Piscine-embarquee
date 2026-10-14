#include <avr/io.h>
#include <stdbool.h>       
#include "Ft_ISR.h"

#define F_CPU 16000000UL 
#define UART_BAUDRATE 115200

#define LED1 PB0
#define LED2 PB1
#define LED3 PB2

void leds_init(void) {
    // Configure les broches des 3 LEDs en SORTIE
    DDRB |= (1 << LED1) | (1 << LED2) | (1 << LED3);
    
    // Éteint toutes les LEDs au départ
    PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3));
}

void timer1_init(void) {
    // 1. Configurer le mode CTC (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // 2. Définir la vitesse de l'intervalle (OCR1A)
    // Pour une base de temps rapide et fluide (ex: 100ms par pas) :
    // Val = (16 000 000 / (1024 * 10 Hz)) - 1 = 1561
    OCR1A = 156;

    // 3. Activer l'interruption Compare Match A du Timer 1
    TIMSK1 |= (1 << OCIE1A);

    // 4. Démarrer le Timer 1 avec un Prescaler de 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
}



void uart_init(void) {
    // Calculate UBRR value based on F_CPU and UART_BAUDRATE for Double Speed Asynchronous mode
    uint16_t ubrr_value = (F_CPU / 8UL / UART_BAUDRATE - 1);
    
    // Set baud rate registers (High and Low)
    UBRR0H = (unsigned char)(ubrr_value >> 8);
    UBRR0L = (unsigned char)(ubrr_value);
    
    // Enable Double Speed mode (U2X0 = 1)
    UCSR0A |= (1 << U2X0);
    
    // Enable receiver (RX) and transmitter (TX)
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    
    // Set frame format: 8 data bits, no parity, 1 stop bit (8N1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

char uart_rx(void)
{
    // Wait for data to be received (RXC0 bit becomes 1)
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}

void uart_tx(char c) {
    // Wait for empty transmit buffer (UDRE0 bit becomes 1 when ready)
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    
    // Put data into buffer, sends the data
    UDR0 = c;
}

void uart_printstr(const char* str)
{
    // Write a full null-terminated string
    while (*str) {
        uart_tx(*str);
        str++;
    }
}

int compare_str(char *s1, char *s2)
{
    // Compare character by character until a mismatch or end of s1 string
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    // Return the difference between the first non-matching characters
    return *s1 - *s2;
}

FT_ISR(__vector_11) {
    static uint8_t etape = 0;

    // Cycle sur 10 étapes (0 à 9). Chaque étape représente 10% du cycle complet.
    // L'intervalle de 30% correspond à 3 étapes.
    if (etape == 0) {
        PORTB |= (1 << LED1);   // Allume LED 1
        PORTB &= ~((1 << LED2) | (1 << LED3));
    } 
    else if (etape == 3) {      // 30% du cycle global
        PORTB |= (1 << LED2);   // Allume LED 2
        PORTB &= ~((1 << LED1) | (1 << LED3));
    } 
    else if (etape == 6) {      // 60% du cycle global (30% après la LED 2)
        PORTB |= (1 << LED3);   // Allume LED 3
        PORTB &= ~((1 << LED1) | (1 << LED2));
    }

    etape++;
    if (etape >= 10) {          // Fin du cycle total (100%), on recommence
        etape = 0;
    }
}


int main(void) {
    // Reference variables (automatically size allocated + 1 byte for '\0')
    char username[] = "Spectre";   
    char password[] = "4242"; 
    
    // Buffers to store input credentials (size 11 allows max 10 chars + '\0')
    char ent_username[11];
    char ent_password[11];
    char c;
    bool first = true;
    uint8_t i = 0;

    uart_init(); // Initialize UART communication
    
    while(1) {
        cli(); // Disable global interrupts during login phase
        
        if (first)
        {
            uart_printstr("Enter your login:\n\r");
            first = false;
        }
        else
        {
            uart_printstr("\n\rLogin or Password incorrect:\n\r");
            uart_printstr("Enter your login:\n\r");
        }
        
        i = 0; // Reset index for username entry
        while (i < 10) { // Limit to < 10 to keep index 10 safe for '\0'
            c = uart_rx();
            
            // Handle Backspace / Delete (Mac & Linux 0x7F / PC '\b')
            if ((c == 0x7F || c == '\b') && i > 0) {
                i--;
                ent_username[i] = '\0'; // Clear deleted char from buffer
                uart_printstr("\b \b"); // Visual erase on terminal
            } 
            // Handle Enter key
            else if (c == '\r' || c == '\n') {
                break;
            }
            // Handle valid printable characters
            else if (c != 0x7F && c != '\b') {     
                ent_username[i] = c;
                uart_tx(c); // Echo back character to user
                i++;
            }
        }
        ent_username[i] = '\0'; // Properly append null terminator
        
        uart_printstr("\n\rEnter your password:\n\r");
        
        // --- PASSWORD INPUT ---
        i = 0; // Reset index for password entry
        while (i < 10) { 
            c = uart_rx();
            
            // Handle Backspace / Delete
            if ((c == 0x7F || c == '\b') && i > 0) {
                i--;
                ent_password[i] = '\0';
                uart_printstr("\b \b");
            } 
            // Handle Enter key
            else if (c == '\r' || c == '\n') {
                break;
            }
            // Handle valid printable characters
            else if (c != 0x7F && c != '\b') {     
                ent_password[i] = c;
                uart_tx('*'); // Mask password input with asterisks
                i++;
            }
        }
        ent_password[i] = '\0'; // Properly append null terminator
    
        if (compare_str(username, ent_username) == 0 && compare_str(password, ent_password) == 0)
        {
            sei(); // Re-enable global interrupts before leaving
            uart_printstr("\n\rWelcome, Master.\n\rHow should we destroy the world!\n\r");
            break; // Exit the infinite login loop
        }
    }
    cli();
    leds_init();
    timer1_init();
    sei();
    while(1) {     
    }
}
