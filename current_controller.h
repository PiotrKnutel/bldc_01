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

/* 
 * Funkcja do realizacji regulatora calkujacego pradu silnika BLDC.
 * INPUT:
 *   current_ref    - Prad zadany. Dozwolony zakres: 0..2047. 1 Amper = 93. 
 *   current_meas   - Prad zmierzony przez ADC. Dozwolony zakres: 0..4095.
 *   pwm_upper_limit_percent - Procent dopuszczalnego maks. wypelnienia syg. PWM
 *                    struj?cego przetwornica buck Vbat/Vbldc.
 *                    Dopusczalny zakres: 2..85% 
 * OUTPUT:
 *   pwm_to_set     - Wynik regulatora calkujacego. Wypelnienie sygnalu PWM
 *                    sterujacego przetwornica buck Vbat/Vbldc. Zakres: 5..204.
 *                    Wspolczynnik wpelnienia [%] = (pwm_to_set / 240) * 100%.
 */
void current_controller_with_upper_limit(unsigned int current_ref,
        unsigned int current_meas, unsigned int* pwm_to_set,
        float pwm_upper_limit_percent);
