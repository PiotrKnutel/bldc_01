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
#include <stdio.h>

//#include <stdio.h>      // tymczasowo dla printf()
//#include <xc.h>         // tymczasowo dla _CP0_SET_COUNT()

#define EXIT_SUCCESS            0
#define TEXT_LEN                30

volatile unsigned int current_specified;
extern volatile unsigned int licznik;
extern volatile int flag_uart_tx;
extern volatile int flag_commutation_detected;
extern unsigned int colector_1;

const char msg_1A[3]    = "1 \0";
const char msg_5A[3]    = "5 \0";
const char msg_n[3]     = "n \0";
const char msg_start[10] = "\n\n\rStart.\0";
const char msg_detected[3] = "d ";
const char msg_no_detected[3] = "x ";

char text[TEXT_LEN];
extern volatile char rx_buff[RX_BUFF_LEN];
const char start_text[] = " Start \n\r\0";
extern volatile int licz_a;
extern volatile int flaga_rozruch;
extern volatile int state;

int main() {
    licznik = 0;
    flag_uart_tx = 0;
    flag_commutation_detected = 0;
    licz_a = 0;
    flaga_rozruch = 0;
    
    WDTCONbits.ON = 0; // wyl. watchdog timer, mozna uzywac tego bitu jesli FWDTEN = 0
    
    interrupt_on();             // Wl. obslugi przerwan przez PIC32.
    pins_config();              // Konfiguracja pinów wej./wyj.
    bridge_idle_state();        // Stan jalowy wszyskich 3 faz silnika.
    uart_init();                // Konfiguracja UART 1, do debugowania.
    adc_config();               // Konfiguracja ADC0-ADC5.
    
    buck_converter_config();    // Konfiguracja peryferiów (w tym PWM) do
                                // sterowania przetwornica buck Vbat/Vbldc.
    
    buck_converter_init();      // Inicjalizacja pracy przetwornicy Vbat/Vbldc.
    
    adc_start_TMR1();   // Wlaczenie TMR1 do taktowania ADC, a w konsewkencji
                        // przerwan do regulatora I.
    
    current_specified = I_1A;

    uart_write_text(msg_start);
    
    while(1)
    {
        for (int i=0; i<5; i++)
        {
            asm volatile ("nop");
        }
        
        /* Wyslanie po magistralii UART */
        if (flag_uart_tx == 1)
        {
            flag_uart_tx = 0;
            if (flag_commutation_detected == 1)
            {
                uart_write_char(0x30 + state);
            }
            else
            {
                uart_write_text(msg_no_detected);
            }
            //uart_write_char(' ');
        }
    }
    
    return (EXIT_SUCCESS);
}
