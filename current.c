/* Regulator calkujacy pradu */

#include "current.h"

unsigned int current_controller(unsigned int meas_current, unsigned int ref_current)
{
    unsigned int pwm_now_u = PDC4;
    int pwm_now_i = 0;
    unsigned int pwm_to_set_u;
    int pwm_to_set_i;
    static int previos_I_out = 0;
    int I_out;
    int current_diff;
    unsigned int Ki = 0.0001;
    const int current_offset = 2048;    // ofset 1,65 V
    //const int OFFSET = 0x800;           // 2048
    unsigned int pwm_min = 5;           // 2% z 240
    unsigned int pwm_max = 204;         // 85% z 240
    const unsigned int MAX_REF_CURRENT = 2047;
    
    // konwersja pwm_now z unsigned int do int
    if (pwm_now_u <= (unsigned int)INT_MAX)
        pwm_now_i = (int)pwm_now_u;
    else
        pwm_now_i = INT_MAX;
    
    // zabezpieczenie przed podaniem za duzej wartosci docelowego pradu
    if (ref_current > MAX_REF_CURRENT)
        ref_current = MAX_REF_CURRENT;
    
    // uchyb regulacji
    current_diff = current_offset + (int)ref_current - (int)meas_current;
    
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
    
    pwm_to_set_i = pwm_now_i + I_out;
    
    // zabezpieczenie przed niedozowlonymi wartosciami PWM 
    if (pwm_to_set_i > pwm_max)
        pwm_to_set_i = pwm_max;
    if (pwm_to_set_i < pwm_min)
        pwm_to_set_i = pwm_min;
    
    // Aby konwerowac, pwm_to_set_i > 0. Gwarantuja to 2 warunki powyzej.
    pwm_to_set_u = (unsigned int)pwm_to_set_i; 
    
    return pwm_to_set_u;
}