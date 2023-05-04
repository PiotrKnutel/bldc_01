/******************************************************************************* 
 * File: adc_main.h
 * 
 * Funkcje i zmienne dotyczace ADC, udostepnione do 'main.c'.  
 ******************************************************************************/

/*
 * Konfiguracja ADC0-ADC5, dzialajacych rownoczesnie, wyzwalanych TMR1
 * z f = 10 kHz. Po zakonczeniu konwersji przez ADC, wyzwalane jest przerwanie
 * z wektorem '_ADC_URDY_VECTOR', obslugiwane przez funkcje 'IntADCp7()',
 * znajdujaca sie w pliku 'IntADCp7.c'. W 'adc_init()' TRM1 jest konfigurowany,
 * ale nie jest uruchamiany. Rozdzielczosc wszystkich uzytych ADC to 12 bitow.  
 */
void adc_config(void);

/*
 * Uruchomienie Timera 1 (TRM1) wyzwalajacego cyklicznie przetwarzanie
 * ADC0-ADC5.
 */
void adc_start_TMR1(void);
