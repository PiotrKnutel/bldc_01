/******************************************************************************* 
 * File: IntADCp7.h
 * 
 * Funkcja 'IntADCp7()' do obsluga przerwania 'ADC Update Ready After Suspend',
 * o wektorze '_ADC_URDY_VECTOR', wywolywanego po zakonczonej konwersji ADC.
 * Funkcja przerwania realizuje glowne zadania sterownika BLDC, w tym: 
 *   - odczyt wartosci zmierzonych przez ADC;
 *   - wywolanie funkcji regulatora pradu;
 *   - ustawienie wypelnienia sygnalu PWM sterujacego przetwornica Vbat/Vbldc;
 *   - wywolanie funkcji do komutacji silnika.
 ******************************************************************************/     

#define I_1A    87
#define I_2A    174
#define I_3A    261
#define I_4A    347
#define I_5A    434
#define I_1_3A  113
#define I_4_5A  391


#include "p32mk1024mcf064.h"
#include "adc_int.h"
#include "bridge_int.h"
#include "buck_converter_int.h"
#include "current_controller.h"

unsigned int ADC_res[6];        // tablica na wyniki ADC0-ADC5
unsigned int current;           // przepisana z wyników ADC wartosc pradu 
extern unsigned int current_specified; // prad zadany, bez uwzglednienia offsetu
unsigned int next_pwm;          // nowe wypelnienie syg. PWM sterujacego przetwornica buck Vbat/Vbldc

extern unsigned int licznik;

void __attribute__((vector(_ADC_EARLY_VECTOR), interrupt(IPL7SRS), nomips16)) 
IntADCp7 ()
{
	IFS3bits.AD1GIF = 0;           // wyl. flagi przerwania
    IFS3bits.AD1D0IF= 0;
    adc_read(&ADC_res[0], &ADC_res[1], &ADC_res[2], &ADC_res[3], &ADC_res[4], &ADC_res[5]);
    current = ADC_res[2];
    //current_specified = 93;       // Tymczasowo tutaj ustalane! 93 =~ 1 A
    current_controller(current_specified, current, &next_pwm);
    buck_converter_set_pwm(next_pwm);
    licznik++;
    if (licznik == 40000)
    {
        licznik = 0;
        if (current_specified == I_5A)
            current_specified = I_1A;
        else
            current_specified = I_5A;
    }
}