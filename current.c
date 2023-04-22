/* Regulator calkujacy pradu */

#include "current.h"

unsigned int current_controller(unsigned int meas_current, unsigned int spec_current)
{
    unsigned int PWM_to_set;
    static unsigned int previos_I_out = 0;
    unsigned int I_out;
    unsigned int current_diff;
    unsigned int Ki = 0.0001;
    unsigned int x_min = 1234;
    unsigned int x_max = 2345;
    
    current_diff = spec_current - meas_current;
    I_out = (current_diff + previos_I_out)  ; // i jeszcze ACC
    I_out = previos_I_out;
    I_out = I_out * Ki;
    if (I_out > x_max)
        I_out = x_max;
    if (I_out < x_min)
        I_out = x_min;
    PWM_to_set = I_out;
    
    return PWM_to_set;
}