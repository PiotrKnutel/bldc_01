/******************************************************************************* 
 * File: adc_int.h
 * 
 * Funkcje i zmienne dotyczace ADC, udostepniane do IntADCp7.c 
 ******************************************************************************/

/*
 * Przypisanie wynikow pomiarow ADC0-ADC5 pod wskazane adresy.
 * W funkcji nie jest sprawdzane zakonczenie konwersji przetwornkow ADC!
 * Wszystkie uzyte ADC maja rozdzielczosc 12 bitów, wyniki maja zakres 0..4095.
 * OUTPUT: 
 *   ADC0_phase_V   - wartosc ADC0 odpowiadajaca napieciu na fazie V silnika;
 *   ADC1_phase_U   - wartosc ADC1 odpowiadajaca napieciu na fazie U silnika;
 *   ADC2_current   - wartosc ADC2 odpowiadajaca spadkowi napiecia na 
 *                    R_sens = 3 mOhm na wyjsciu przetwornicy Vbat/Vbldc,
 *                    wzmocniona x20 V/V, z offsetem 1.65V;
 *   ADC3_phase_W   - wartosc ADC3 odpowiadajaca napieciu na fazie W silnika;
 *   ADC4_Vbat      - wartosc ADC4 odpowiadajaca napieciu wejsiowemu
 *                    z akumulatorow (ok 8 V), po dzielniku 27k/(27k+75k);
 *   ADC5_Vbldc     - wartosc ADC5 odpowiadajaca nanapieciu Vbldc, po dzielniku
 *                    4k02/(10k+4k02); 
 */
void adc_read (unsigned int* ADC0_phase_V, unsigned int* ADC1_phase_U,
        unsigned int* ADC2_current, unsigned int* ADC3_phase_W,
        unsigned int* ADC4_Vbat, unsigned int* ADC5_Vbldc);
