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
#include "current_values_definitions.h"
#include "uart.h"

#include <stdio.h>      // tymczasowo dla printf()
#include <xc.h>         // tymczasowo dla _CP0_SET_COUNT()

#define EXIT_SUCCESS         0

volatile unsigned int current_specified;
volatile unsigned int licznik;


void delay_us(unsigned int us){
    us *= (120000000 / 1000000) / 2;
    _CP0_SET_COUNT(0);
    while (us > _CP0_GET_COUNT());
}
void delay_ms(unsigned int ms){
    delay_us(ms * 1000);
}


int main() {
    licznik = 0;
    
    WDTCONbits.ON = 0; // wyl. watchdog timer, mozna uzywac tego bitu jesli FWDTEN = 0
    
    interrupt_on();             // Wl. obslugi przerwan przez PIC32.
    pins_config();              // Konfiguracja pinów wej./wyj.
    bridge_idle_state();        // Stan jalowy wszyskich 3 faz silnika.
    //uart_init();                // Konfiguracja UART 1, do debugowania.
    adc_config();               // Konfiguracja ADC0-ADC5.
    
    buck_converter_config();    // Konfiguracja peryferiów (w tym PWM) do
                                // sterowania przetwornica buck Vbat/Vbldc.
    
    buck_converter_init();      // Inicjalizacja pracy przetwornicy Vbat/Vbldc.
    
    adc_start_TMR1();   // Wlaczenie TMR1 do taktowania ADC, a w konsewkencji
                        // przerwan do regulatora I.
    
    current_specified = I_1A;
    
    while(1)
    {
        for (int i=0; i<5; i++)
        {
            asm volatile ("nop");
        }
        if (current_specified == 87 && PORTGbits.RG6 == 0) 
        {
            LATGbits.LATG6 = 1;
        } 
        else if (current_specified == 434 && PORTGbits.RG6 == 1) 
        {
            LATGbits.LATG6 = 0;
        } 
        else 
        {
            asm volatile ("nop");
        }
    }
    return (EXIT_SUCCESS);
}
