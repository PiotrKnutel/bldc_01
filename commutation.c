/*
 * File: commutation.c
 */

#define STATE_NO_DETECTED       0
#define STATE_DETECTED          1

const unsigned int HIGH_RANGE_DOWN_LIMIT    = 2457;     // 60% * 4095
const unsigned int LOW_RANGE_UP_LIMIT       = 1638;     // 40% * 4095
const unsigned int V_MID_UP                 = 2252;     // 55% * 4095
const unsigned int V_MID_DOWN               = 1843;     // 45% * 4095

volatile int flag_commutation_detected;
unsigned int colector_1;
const unsigned int integral_area = 1000;
int state;
int nr_det_1;
int nr_det_2;


int detect_first_state(int unsigned adc_phase_L, unsigned int adc_phase_N,
        unsigned int adc_phase_H)
{
    static unsigned int previous_adc_phase_N = 4095;
    static int flag_N_is_growing = 0;
    static int flag_N_has_not_yet_exceeded_V_MID = 0;
    static int i = 0;
    int status = STATE_NO_DETECTED;
    
    if (adc_phase_H > HIGH_RANGE_DOWN_LIMIT)
    {
        if (adc_phase_L < LOW_RANGE_UP_LIMIT)
        {
            if (adc_phase_N > previous_adc_phase_N)
            {
                i++;
                if (i >= 3)
                    flag_N_is_growing = 1;
            }
            else
            {
                flag_N_is_growing = 0;
                i = 0;
            }
        }
    }
    previous_adc_phase_N = adc_phase_N;
    
    if (flag_N_is_growing)
    {
        if (adc_phase_N > V_MID_UP)
        {
            if (flag_N_has_not_yet_exceeded_V_MID)
            {
                flag_N_has_not_yet_exceeded_V_MID = 0;
                flag_N_is_growing = 0;
                status = STATE_DETECTED;
            }
        }
        else
        {
            flag_N_has_not_yet_exceeded_V_MID = 1;
        }
    }
    
    return status;
}

int detect_second_state(int unsigned adc_phase_L, unsigned int adc_phase_N,
        unsigned int adc_phase_H)
{
    static unsigned int previous_adc_phase_N = 0;
    static int flag_N_is_falling = 0;
    static int flag_N_has_not_yet_exceeded_V_MID = 0;
    static int i = 0;
    int status = STATE_NO_DETECTED;
    
    if (adc_phase_H > HIGH_RANGE_DOWN_LIMIT)
    {
        if (adc_phase_L < LOW_RANGE_UP_LIMIT)
        {
            if (adc_phase_N < previous_adc_phase_N)
            {
                i++;
                if (i >= 3)
                    flag_N_is_falling = 1;
            }
            else
            {
                flag_N_is_falling = 0;
                i = 0;
            }
        }
    }
    previous_adc_phase_N = adc_phase_N;
    
    if (flag_N_is_falling)
    {
        if (adc_phase_N < V_MID_DOWN)
        {
            if (flag_N_has_not_yet_exceeded_V_MID)
            {
                flag_N_has_not_yet_exceeded_V_MID = 0;
                flag_N_is_falling = 0;
                status = STATE_DETECTED;
            }
        }
        else
        {
            flag_N_has_not_yet_exceeded_V_MID = 1;
        }
    }
    
    return status;
}


void commutation_detect(unsigned int* ADC_V, unsigned int* ADC_U, unsigned int* ADC_W)
{
    unsigned int adc_phase_L;
    unsigned int adc_phase_N;
    unsigned int adc_phase_H;
    
    static int flag_detected_1_phase = 0;
    static unsigned int adc_1_colector = 0;
    
    if (!flag_detected_1_phase)
    {
        adc_phase_L = *ADC_V;
        adc_phase_N = *ADC_U;
        adc_phase_H = *ADC_W;
        nr_det_1++;
        flag_detected_1_phase = detect_first_state(adc_phase_L, adc_phase_N, adc_phase_H);
    }
    else
    {
        adc_phase_L = *ADC_V;
        adc_phase_N = *ADC_W;
        adc_phase_H = *ADC_U;
        adc_1_colector += adc_phase_N;
        nr_det_2++;
        if (detect_second_state(adc_phase_L, adc_phase_N, adc_phase_H))   // second state
        {
            flag_commutation_detected = 1;
            flag_detected_1_phase = 0;
            colector_1 = adc_1_colector;
            adc_1_colector = 0;
            state = 2;
        }    
    }
}

void set_state(int state)
{
    switch (state)
    {
        case 0:
            
            break;
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            
            break;
        default:
            
            break;
    }
}

void commutation(unsigned int* ADC_V, unsigned int* ADC_U, unsigned int* ADC_W)
{
    const unsigned int* phase_N_sequence[6] = {ADC_U, ADC_W, ADC_V, ADC_U, ADC_W, ADC_V };
    unsigned int *phase_N;
    static unsigned int summator = 0;
    
    /*phase_N = phase_N_sequence[state];
    
    summator += *phase_N;
    if (summator >= integral_area)
    {
        state = ++state;
        if(state == 7)
            state = 0;
        summator = 0;
    }
     */
}
