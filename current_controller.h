/******************************************************************************* 
 * File: current_controller.h
 *
 * Funkcje i zmienne dotyczace regulatora calkujacego pradu silnika,
 * udostepnione do 'IntADCp7.c'.
 ******************************************************************************/

/* 
 * Funkcja do realizacji regulatora calkujacego pradu silnika BLDC.
 * INPUT:
 *   current_ref    - prad zadany, dozwolone wartosci: 0..2047, 
 *   
 */
void current_controller(unsigned int current_ref, unsigned int current_meas,
        unsigned int* pwm_to_set);
