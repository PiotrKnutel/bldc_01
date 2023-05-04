/*******************************************************************************
 * File: buck_converter_main.h
 * 
 * Funkcje i zmienne dotyczace sterowania przetwornica buck step-down 
 * CSD95377Q4M Vbat/Vbldc, udostepnione do 'main.c'.
 ******************************************************************************/

/*
 * Konfiguracacja peryferiow, w tym 'Motor Control PWM 4', do sterowania
 * przetwornica buck step-down Vbat/Vbldc.
 * Konfiguracja pinów:
 *   pin 63 - PB13 output - sygnal SKIP do wyboru trybu pracy przetwornicy;
 *   pin 64 - PWM4H (Motor Control PWM) - sygnal PWM do sterowania napieciem
 *            wyjsciowym przetwornicy.
 * W wyniku tej funcji, przetwornica nie zostanie uruchomiona! W celu
 * uruchomienia przetwornicy nalezy wywolac jeszcze 'buck_converter_init()'.      
 */
void buck_converter_config();

/*
 * Inicjalizacja przetwornicy buck Vbat/Vbldc.
 * Ta funkcja wymaga wczesniejszego wywolania 'buck_converter_config()'.
 * Wartosc wspólczynnika wypelnienia sygnalu PWM sterujacego przetwornica,
 * ktora jest ustawiana w tej funkcji, to minimalna wartosc dopuszczalna,
 * wynoszaca 5/240 = ~2%.
 */
void buck_converter_init();
