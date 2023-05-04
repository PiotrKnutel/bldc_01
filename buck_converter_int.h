/*******************************************************************************
 * File: buck_converter_int.h
 * 
 * Funkcje i zmienne dotyczace sterowania przetwornica buck step-down 
 * CSD95377Q4M Vbat/Vbldc, udostepnione do 'IntADCp7.c'.
 ******************************************************************************/

/*
 * Zmiania wypelnienia sygnalu PWM, sterujacego przetwornica Vbat/Vbldc.
 * INPUT:
 *   pwm            - Wypelnienie PWM. Dozwolony zakres 5..204
 *                    (przy f=500 kHz). Zakres wynika z Ton_min=40 ns i max
 *                    wspól. wyp. 85%. Pelny okres to 240 cykli.
 *                    0 = 0%, 240 = 100%.
 */
void buck_converter_set_pwm(unsigned int pwm);

/*
 * Odczyt aktualnie ustawionej watosci wypelnienia PWM, sterujacego
 * przetwornica Vbat/Vbldc. Bezposredni odczyt rejestru PDC4.
 * Wspólczynnik wypelnienia [%] = PDC4 / 240.
 * OUTPUT:
 *   returned value - Aktualnie ustawione wypelnienie PWM. Zakres 0..240. 
 *                    Zakres poprawny przy f=500 kHz: 5..204.
 */
unsigned int buck_converter_read_pwm_set(void);

// A mo?e lepiej zamaist funkcji do zapisu i odczytu rejestru PDC4, tak:
// #define BUCK_CONVERTER_PWM_DUTY     PDC4
// ???