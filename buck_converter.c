/******************************************************************************* 
 * File: buck_converter.c
 * 
 * Funkcje i zmienne dotyczce sterowania przetwornica buck step-down
 * CSD95377Q4M, ktora konwertuje napiecie Vbat na Vbldc.
 * 
 * Sterowanie jest realizowane przez blok Motor Control PWM (MCPWM).
 * Sterowanie wymaga wysylania dwóch sygnalów: 
 *   - PWM  - do wyboru napiecia wyjsciowego przetwornicy (uzyto pinu 64 PWM4H); 
 *   - SKIP - do wyboru trybu pracy przetwornicy (uzyto pinu 63 RB13). 
 * Program przygotowany w oparciu o note katalogowa PIC32MK_GP_MC i instrukcje
 * referencyjna (sekcja 44).
 ******************************************************************************/

#include "p32mk1024mcf064.h"
#include "buck_converter_main.h"
#include "buck_converter_int.h"
#include "pins_config_buck_conv.h"      // definicje nazw pinów

/*
 * Konfiguracacja peryferiow, w tym 'Motor Control PWM 4', do sterowania
 * przetwornica buck Vbat/Vbldc. Ustawienie min. dopuszcz. wypelnienia syg. PWM.  
 */
void buck_converter_config()
{
    PTCONbits.PTEN = 0; //wylaczenie modulu PWM
    
    PMD4bits.PWM1MD = 1;
    PMD4bits.PWM2MD = 1;
    PMD4bits.PWM3MD = 1;
    PMD4bits.PWM5MD = 1;
    PMD4bits.PWM6MD = 1;
    PMD4bits.PWM7MD = 1;
    PMD4bits.PWM8MD = 1;
    PMD4bits.PWM9MD = 1;
    PMD4bits.PWM10MD = 1;
    PMD4bits.PWM11MD = 1;
    PMD4bits.PWM12MD = 1;
    
    PTCONbits.PCLKDIV = 0b000; // prescaler pierwszy, 0 to 1/FSYSCLK
    
    // gdy ITB=1 to zamiast PTPER jest uzywane PHASE.
    //PTPER = 0x00F0;     // min. to 0x0008; 0x00F0=240; wzor 4 na str. 44-10.
    PWMCON4bits.MTBS = 0; //wybor zrodla zegara, 0 to Primary master time base
    
    PWMCON4bits.ITB = 1; // Independent Time Base Mode
    PWMCON4bits.DTC = 0b0010; //Dead time function is disabled
    IOCON4bits.PENH = 1; // modul PWM kontroluje pin PWM4H
    IOCON4bits.PENL = 0; // GPIO kontroluje pin PWM4L
    IOCON4bits.PMOD = 0b0011; // PWM4L utrzywywane w stanie '0' (ale raczej nie potrzebne gdy PENL=0)
    IOCON4bits.FLTMOD = 0b0011;   // wyl. wej. fault
    
    PHASE4 = 0x00F0;        // ustawienie okresu syg. PWM 0xF0 = 240 = 2 us 
    PDC4 = 5;               // ustawienie min. wartosci wypelenienia syg. PWM
}

/*
 * Inicjalizacja przetwornicy buck Vbat/Vbldc.
 */
void buck_converter_init()
{
    unsigned int flaga_skip_start = 0;
    
    PDC4 = 0x0078;          // PWM Genertaor Duty Cycle 0x0078=120 (polowa 240)
    PTCONbits.PTEN = 1;
    
    /* TIMER 2 do PWM */
    T2CONbits.ON = 0;       //W czasie konfiguracji timer musi byc wylaczony
    TMR2 = 0x0000;
    PR2 = 0x003C;           //Wartosc przy ktorej timer sie przepelnia
    T2CONbits.TCKPS = 0b001; //Prescaler 2, gen 10MHz, uC 120MHz, magistrala 60MHz, licznik 30MHz
    T2CONbits.TCS = 0;
    T2CONbits.ON = 1;       //Timer zostaje wlaczony
    
    while(!flaga_skip_start)
    {
        if (TMR2==0x0005) {
            flaga_skip_start = 1;
        }
        if (flaga_skip_start) {
            PIN_SKIP = 1;
        }            
    }
    T2CONbits.ON = 0;
}

/*
 * Zmiania wypelnienia sygnalu PWM, sterujacego przetwornica Vbat/Vbldc.
 */
void buck_converter_set_pwm(unsigned int pwm)
{
    PDC4 = pwm;
}

/*
 * Odczyt aktualnie ustawionej watosci wypelnienia PWM, sterujacego
 * przetwornica Vbat/Vbldc.
 */
unsigned int buck_converter_read_pwm_set()
{
    return PDC4;
}
