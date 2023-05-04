/******************************************************************************* 
 * File: current_controller.c
 * 
 * Funkcje i zmienne do realizacji regulatora pradu silnika BLDC, jako
 * regulatora calkujacego.
 ******************************************************************************/ 

#include "current_controller.h" 

    int current_diff;                       // uchyb regulacji
    int I_out;                              // wyj. calki
    int pwm_to_set_i;                       // obliczony wspol. wypelnienia PWM 
    static int previos_I_out = 0;           // poprzednie wyj. calki
    unsigned int Ki = 0.0001;               // wspol wzmocnienia na wyj. calki
    const int CURRENT_OFFSET = 2048;        // offset pomiaru pradu 1.65 V
    const unsigned int MAX_REF_CURRENT = 2047;  // max dozwolony pradu zadany
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
    
        // conversion range 0..4095 to -2048..2047
            // if (current_diff >= 4095)  //zawsze powinno byc <=4095 
            //      current_diff = 4095;
        //current_diff = int(current_diff) - OFFSET;
    
    // calka
    I_out = (current_diff + previos_I_out);
    
    // ACC
    if (I_out > 2047)
        I_out = 2047;
    if (I_out < -2048)
        I_out = -2048;
    
    // zachowanie I_out dla nastepnych iteracji
    previos_I_out = I_out;
    
    I_out = I_out * Ki;
    
    pwm_to_set_i = I_out;
    
    // zabezpieczenie przed niedozowlonymi wartosciami PWM 
    if (pwm_to_set_i > PWM_MIN)
        pwm_to_set_i = PWM_MAX;
    if (pwm_to_set_i < PWM_MIN)
        pwm_to_set_i = PWM_MAX;
    
    // Aby konwerowac, pwm_to_set_i > 0. Gwarantuja to 2 warunki powyzej.
    *pwm_to_set = (unsigned int)pwm_to_set_i;
}