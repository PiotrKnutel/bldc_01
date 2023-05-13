/******************************************************************************* 
 * File: main.c
 * 
 * Ogolny opis projektu znajduja sie w pliku 'README.txt'.
 * 
 * Plik zawiera glowna funkcje sterownika BLDC. Funkcja 'main' zawiera wywolania
 * funkcji do konfiguracji i inicjalizacji peryferiów mikrokontrolera i rozruchu
 * przetwornicy buck Vbat/Vbldc.
 ******************************************************************************/ 

#include "p32mk1024mcf064.h"
#include "pragma_config.h"
#include "pins_config_main.h"
#include "adc_main.h"
#include "buck_converter_main.h"
#include "bridge_main.h"
#include "interrupt_on.h"

#define EXIT_SUCCESS         0

unsigned int current_specified;

// DO TESTOW

//#define MY_SYS_FREQ     120000000
#define I_1A    87
#define I_2A    174
#define I_3A    261
#define I_4A    347
#define I_5A    434

unsigned int licznik;

/*void __attribute__((vector(_TIMER_3_VECTOR), interrupt(IPL6SRS), nomips16)) 
timer3_handler()
{
	IFS0bits.T3IF = 0;	// Clear interrupt flag for timer 3

}

void timer3_interrupt_init()
{
    T3CON = 0x0;                // Disable timer 3 when setting it up
    TMR3 = 0;                   // Set timer 3 counter to 0
    PR3 = 234000;

    T3CONbits.TCKPS = 0b111;    // Pre-scale of 256
    T3CONbits.TCS = 0;          // Internal clock
 	IEC0bits.T3IE = 0;          // Disable Timer 3 Interrupt
 	IFS0bits.T3IF = 0;          // Clear interrupt flag for timer 3
    IPC3bits.T3IP = 6;          // Interrupt priority 6
    IPC3bits.T3IS = 1;          // Sub-priority 1
    IEC0bits.T3IE = 1;          // Enable Timer 3 Interrupt

 	T3CONbits.ON = 1;           // Module is enabled
}*/
// KONIEC


int main() {
    
    interrupt_on();             // Wl. obslugi przerwan przez PIC32.
    pins_config();              // Konfiguracja pinów wej./wyj.
    bridge_idle_state();        // Stan jalowy wszyskich 3 faz silnika.
    adc_config();               // Konfiguracja ADC0-ADC5.
    
    buck_converter_config();    // Konfiguracja peryferiów (w tym PWM) do
                                // sterowania przetwornica buck Vbat/Vbldc.
    
    buck_converter_init();      // Inicjalizacja pracy przetwornicy Vbat/Vbldc.
    
    adc_start_TMR1();   // Wlaczenie TMR1 do taktowania ADC, a w konsewkencji
                        // przerwan do regulatora I.
    
    //timer3_interrupt_init();
    current_specified = I_1A;
    licznik = 0;
    while(1)
    {
            

            
    }
    return (EXIT_SUCCESS);
}
