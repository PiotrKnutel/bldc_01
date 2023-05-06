/******************************************************************************* 
 * File: current_controller.h
 *
 * Funkcje i zmienne dotyczace regulatora calkujacego pradu silnika,
 * udostepnione do 'IntADCp7.c'.
 ******************************************************************************/

/* 
 * Funkcja do realizacji regulatora calkujacego pradu silnika BLDC.
 * INPUT:
 *   current_ref    - Prad zadany. Dozwolony zakres: 0..2047. 1 Amper = 93. 
 *   current_meas   - Prad zmierzony przez ADC. Dozwolony zakres: 0..4095.
 * OUTPUT:
 *   pwm_to_set     - Wynik regulatora calkujacego. Wypelnienie sygnalu PWM
 *                    sterujacego przetwornica buck Vbat/Vbldc. Zakres: 5..204.
 *                    Wspolczynnik wpelnienia [%] = (pwm_to_set / 240) * 100%.
 */
void current_controller(unsigned int current_ref, unsigned int current_meas,
        unsigned int* pwm_to_set);
