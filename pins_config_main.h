/*******************************************************************************
 * File: pins_config_main.h
 * 
 * Funkcja dotyczaca konfiguracji pin�w wejscia/wyjscia, udostepniona
 * do 'main.c'.
 ******************************************************************************/

/*
 * Konfiguracja wejsc i wyjsc mikrokontrolera.
 * Konfiguracja obejmuje:
 *   - ustawienie wszystkich pin�w jako wej./wyj. cyfrowe;
 *   - ustawienie pin�w powiazancyh z ADC jako wej. analogowe;
 *   - ustawienie pin�w: magistral komunikacyjnych (CAN1, CAN2), sygnal�w
 *     sterujacych przetwornica buck Vbat/Vbldc (PWM, SKIP) i syg. sterujacych
 *     mostkiem MOSFET odpowiednio jako wejscia lub wyjscia;
 *   - ustawienie poczatkowego stanu logicznego wyjscia SKIP = 0.
 */
void pins_config();
