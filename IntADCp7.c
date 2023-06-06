/******************************************************************************* 
 * File: IntADCp7.h
 * 
 * Funkcja 'IntADCp7()' do obsluga przerwania 'ADC Update Ready After Suspend',
 * o wektorze '_ADC_URDY_VECTOR', wywolywanego po zakonczonej konwersji ADC.
 * Funkcja przerwania realizuje glowne zadania sterownika BLDC, w tym: 
 *   - odczyt wartosci zmierzonych przez ADC;
 *   - wywolanie funkcji regulatora pradu;
 *   - ustawienie wypelnienia sygnalu PWM sterujacego przetwornica Vbat/Vbldc;
 *   - wywolanie funkcji do komutacji silnika.
 ******************************************************************************/     

#include "p32mk1024mcf064.h"
#include "adc_int.h"
#include "bridge_int.h"
#include "buck_converter_int.h"
#include "current_controller.h"
#include "current_values_definitions.h"
#include "uart.h"

unsigned int ADC_res[6];        // Tablica na wyniki ADC0-ADC5.
unsigned int current;           // Przepisana z wyników ADC wartosc pradu. 
extern volatile unsigned int current_specified; // Prad zadany,
                                                // bez uwzglednienia offsetu.
unsigned int next_pwm;          // Nowe wypelnienie syg. PWM sterujacego
                                // przetwornica buck Vbat/Vbldc.

extern volatile unsigned int licznik;  // TYLKO DO TESTOW! okresowa zamana stanu
extern volatile int flag_uart_tx;

void __attribute__((vector(_ADC_DATA0_VECTOR), interrupt(IPL7SRS), nomips16)) 
IntADCp7 ()
{
    ADCDATA0;                   // Odczyt rejestru z wynikami ADC0, konieczny
                                // do poprawnego wyl. flagi przerwania.
    IFS3bits.AD1D0IF= 0;        // Czyszczenie flagi przerwania 'ADC Data 0'.
    IFS2bits.AD1IF= 0;          // Czyszczenie flagi przerwania 'ADC global'.
    
    /* DO TESTOW! Zmiana stanu na pinie G8 z f przerwania. */
    if (LATGbits.LATG8 == 0)
        LATGbits.LATG8 = 1;
    else
        LATGbits.LATG8 = 0;
    
    adc_read(&ADC_res[0], &ADC_res[1], &ADC_res[2], &ADC_res[3], &ADC_res[4],
            &ADC_res[5]);
    current = ADC_res[2];
    current_controller(current_specified, current, &next_pwm);
    buck_converter_set_pwm(next_pwm);
    
    /* DO TESTOW! Okresowa zmiana pradu zadanego. */
    licznik++;
    if (licznik >= 10000)
    {
        licznik = 0;
        flag_uart_tx = 1;
        if (current_specified == I_5A) 
        {
            current_specified = I_1A;
        } 
        else 
        {
            current_specified = I_5A;
        }
    }
}