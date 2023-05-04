/*******************************************************************************
 * File: pins_config_main.h
 * 
 * Funkcja dotyczaca konfiguracji pinów wejscia/wyjscia, udostepniona
 * do 'main.c'.
 ******************************************************************************/

/*
 * Konfiguracja wejsc i wyjsc mikrokontrolera.
 * Konfiguracja obejmuje:
 *   - ustawienie wszystkich pinów jako wej./wyj. cyfrowe;
 *   - ustawienie pinów powiazancyh z ADC jako wej. analogowe;
 *   - ustawienie pinów: magistral komunikacyjnych (CAN1, CAN2), sygnalów
 *     sterujacych przetwornica buck Vbat/Vbldc (PWM, SKIP) i syg. sterujacych
 *     mostkiem MOSFET odpowiednio jako wejscia lub wyjscia;
 *   - ustawienie poczatkowego stanu logicznego wyjscia SKIP = 0.
 */
void pins_config();
