/******************************************************************************* 
 * File: current_controller.c
 * 
 * Funkcje i zmienne do realizacji regulatora pradu silnika BLDC, jako
 * regulatora calkujacego.
 ******************************************************************************/ 

#include "current_controller.h" 

    int current_diff;                       // uchyb regulacji
    int I_out;                              // wyjscie calki
    static int previos_I_out = 0;           // poprzednie wyj. calki
    unsigned int result;                    // obliczone wypelnienie PWM, wynik
    const int CURRENT_OFFSET = 2048;        // offset pomiaru pradu 1.65 V
    const unsigned int Ki = 4;              // wzm. na wyj. calki = 1/(2^Ki)
    const unsigned int MAX_REF_CURRENT = 2047;  // max dozwolony prad zadany
    const unsigned int PWM_MIN = 5;         // min dozwol. wypel. PWM  2% z 240
                                            // przy f = 500 kHz, min Ton=40 ns
    const unsigned int PWM_MAX = 204;       // max dozwol. wypel. PWM 85% z 240

void current_controller(unsigned int current_ref, unsigned int current_meas,
        unsigned int* pwm_to_set)
{
    // zabezpieczenie przed podaniem za duzej wartosci docelowego pradu
    if (current_ref > MAX_REF_CURRENT)
        current_ref = MAX_REF_CURRENT;
    
    // uchyb regulacji
    current_diff = CURRENT_OFFSET + (int)current_ref - (int)current_meas;
    
    // calka
    I_out = current_diff + previos_I_out;
    
    // ACC
    if (I_out > 4095)
        I_out = 4095;
    if (I_out < -4096)
        I_out = -4096;
    
    // zachowanie I_out dla nastepnej iteracji
    previos_I_out = I_out;
    
    if (I_out >= 0)
        result = (unsigned int)I_out >> Ki;
    else
        result = 0;
    
    // zabezpieczenie przed niedozowlonymi wartosciami PWM 
    if (result > PWM_MAX)
        result = PWM_MAX;
    if (result < PWM_MIN)
        result = PWM_MIN;
    
    // Aby poprawnie konwerowac int do unsigned int, pwm_to_set_i > 0.
    // Zapewniane to jest przez warunek powyzej.
    *pwm_to_set = result;
}
