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
    
    while(1)
    {

    }
    return (EXIT_SUCCESS);
}
