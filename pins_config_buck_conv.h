/* 
 * Definicje dotyczace konfiguracji pin�w wejscia/wyjscia, udostepnione 
 * do 'buck_converter.c' i 'pins_config.c'. 
 */

/* Rejestr odpowiadajacy za stan logiczny pinu wyjscia, z kt�rego podawany
 * jest sygnal SKIP, do sterowania przetwornica buck Vbat/Vbldc. */
#define PIN_SKIP        LATBbits.LATB13
