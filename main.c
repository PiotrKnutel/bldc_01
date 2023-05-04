/******************************************************************************* 
 * File: main.c
 * 
 * Ogolny opis projektu znajduja sie w pliku 'README.txt'.
 * 
 * Plik zawiera glowna funkcje sterownika BLDC. Funkcja 'main' realizuje:
 *   - wywolanie funkcji inicjalizujacych peryferia mikrokontrolera: 
 *     GPIO                 - piny wejscia i wyjscia
 *     ADC                  - rownolegle dzialajace ADC0-ADC5
 *     Motor Control PWM    - sygnal PWM do sterowania przetwornica Vbat/Vbldc
 *      
 ******************************************************************************/ 

#include "p32mk1024mcf064.h"
#include "pragma_config.h"
#include "pins_config_main.h"
#include "adc_main.h"
#include "buck_converter_main.h"
#include "bridge_main.h"

#include "bridge_int.h"  // TYLKO PRZY TESTACH! tymczasowo dla 'bridge_set_state()'
#include "buck_converter_int.h" // TYLKO PRZY TESTACH! tymczasowo dla 'buck_converter_set_pwm()'

#define EXIT_SUCCESS         0

int main() {
    
    INTCONbits.MVEC= 1;
    PRISS= 0x76543211;
    asm volatile("ei");
    
    pins_config();
    
    // Stan jalowy wszyskich 3 faz silnika po uruchomieniu programu 
    bridge_idle_state();
    
    adc_config();
    
    bridge_set_state(6);
    
    buck_converter_config();
    buck_converter_init();
    buck_converter_set_pwm(5); // od 5 do 204, czyli 2%..85% z 240
    
    // Wlaczenie TMR1 do taktowania ADC, a w konsewkencji przerwan do regulatora I.
    adc_start_TMR1();
    
    while(1)
    {

    }
    return (EXIT_SUCCESS);
}
