/*******************************************************************************
 * File: pins_config.c
 * 
 * Funkcja dotyczaca konfiguracji pinów wejscia/wyjscia.
 * Konfiguracja obejmuje:
 *   - ustawienie wszystkich pinów jako wej./wyj. cyfrowe;
 *   - ustawienie pinów powiazancyh z ADC jako wej. analogowe;
 *   - ustawienie pinów: magistral komunikacyjnych (CAN1, CAN2), sygnalów
 *     sterujacych przetwornica buck Vbat/Vbldc (PWM, SKIP) i syg. sterujacych
 *     mostkiem MOSFET odpowiednio jako wejscia lub wyjscia;
 *   - ustawienie poczatkowego stanu logicznego wyjscia SKIP = 0.
 ******************************************************************************/

#include "p32mk1024mcf064.h"
#include "pins_config_main.h"
#include "pins_config_buck_conv.h"

/*
 * Konfiguracja wejsc i wyjsc mikrokontrolera. 
 */
void pins_config()
{
    /* Ustawienie wszystkich portów jako wej./wyj. cyfrowe. */
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELE = 0;
    ANSELG = 0;
    
    /* Ustawienie wejsc ADC jako wejscia analogowe. */
    ANSELAbits.ANSA1  = 1;  // A1 jako wej. analogowe (VBAT_ADC)
    ANSELBbits.ANSB0  = 1;  // B0 jako wej. analogowe (Current_Sense_ADC)
    ANSELAbits.ANSA8  = 1;  // A8 jako wej. analogowe (Wsens_ADC)
    ANSELCbits.ANSC1  = 1;  // C1 jako wej. analogowe (Usens_ADC)
    ANSELAbits.ANSA4  = 1;  // A4 jako wej. analogowe (Vsens_ADC)
    ANSELBbits.ANSB7  = 1;  // B7 jako wej. analogowe (VBLDCsens_ADC)
    
    /* Konfiguracja wej. i wyj. CAN1 */
    TRISGbits.TRISG6  = 1;  // wej. C1RX_1
    TRISGbits.TRISG8  = 0;  // wyj. C1TX_1
    
    /* Konfiguracja wej. i wyj. CAN2 */
    TRISAbits.TRISA7  = 1;  // wej. C2RX_2
    TRISBbits.TRISB15 = 0;  // wyj. C2TX_2
    
    /* Konfiguracja wyj. sygnalow do przetwornicy buck Vbat/Vbldc. */
    TRISBbits.TRISB13 = 0;  // wyj. SKIP
    PIN_SKIP = 0;           // stan poczatkowy wyj. SKIP
    TRISAbits.TRISA10 = 1;  // PWM (NIE WOLNO OUTPUT!!! Przypis 1 str. 44-22)
    
    /* Konfiguracja wej. do sprawdzania przetwornicy 5VDC/5VDC. */
    //TRISBbits.TRISB12 = 1;  // wej. ISO_CHECK_V_BLDC (nie uzywane)
    
    /* Konfiguracja wyjsc do sterowania mostkiem MOSFET 3-fazowym. */
    TRISFbits.TRISF0  = 0;  // wyj. ISO_U_PMOS_H
    TRISBbits.TRISB10 = 0;  // wyj. ISO_V_PMOS_H
    TRISBbits.TRISB11 = 0;  // wyj. ISO_W_PMOS_H
    TRISCbits.TRISC8  = 0;  // wyj. U_NMOS_L
    TRISCbits.TRISC6  = 0;  // wyj. V_NMOS_L
    TRISCbits.TRISC7  = 0;  // wyj. W_NMOS_L
}
