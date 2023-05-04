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

#include "adc_int.h"

void __attribute__((vector(_ADC_URDY_VECTOR), interrupt(IPL7SRS), nomips16)) 
IntADCp7 ()
{
	IFS3bits.AD1RSIF = 0;           // wyl. flagi przerwania 
    ADC_read(&ADC_res[0], &ADC_res[1], &ADC_res[2], &ADC_res[3], &ADC_res[4], &ADC_res[5]);
    current = ADC_res[1];
    current_specified = 2500; // tymaczaowo tutaj ustalane
    next_PWM = current_controller(current, current_specified);
    pwm_set(next_PWM);
}
