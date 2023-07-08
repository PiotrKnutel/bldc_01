/*
 * File: commutation.c
 */

#include "bridge_commut.h"

/* Poziomy faz dla kolejnych stanow polozenia wirnika.
 * 
 * Nr stanu |                    |
 * (state)  |  0  1  2  3  4  5  |
 * ---------|--------------------|
 *          |    ______          |
 *          |   /      \         |
 * Faza U   |  /        \        |
 *          | /          \______ |
 *          |          ______    |
 *          |         /      \   |
 * Faza V   |        /        \  |
 *          | ______/          \ |
 *          | ___            ___ |
 *          |    \          /    |
 * Faza W   |     \        /     |
 *          |      \______/      |
 *          |                    |
 */


#define STATE_NO_DETECTED           0
#define STATE_DETECTED              1

#define STATUS_ALREADY              0
#define STATUS_NOT_READY_YET        1

#define STAT_COMMUT_DETECTED        1
#define STAT_COMMUT_NOT_DETECTED    0

#define TASK_NOT_SPECIFIED          0
#define TASK_CHECKING_STATE         1
#define TASK_CROSSING_ZERO_DET      2
#define TASK_DELAY                  3
#define TASK_COMMUTATION_NOW        4

const unsigned int V_MID                    = 2047;
const unsigned int HIGH_RANGE_DOWN_LIMIT    = 2457;     // 60% * 4095
const unsigned int LOW_RANGE_UP_LIMIT       = 1638;     // 40% * 4095
const unsigned int V_MID_UP                 = 2252;     // 55% * 4095
const unsigned int V_MID_DOWN               = 1843;     // 45% * 4095

unsigned int colector_1;
const unsigned int FULL_CONTAINER = 10000;
volatile int state;
int nr_det_1;
int nr_det_2;
int direction;
volatile int task;



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
                //!! zapomniano o i=0;
                if (i >= 3)
                {
                    flag_N_is_growing = 1;
                    i = 0;
                }
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

int detect_second_state(unsigned int adc_phase_L, unsigned int adc_phase_N,
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
                //!! zapomniano o i=0;
                if (i >= 3)
                {
                    flag_N_is_falling = 1;
                    i = 0;
                }
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


int commutation_detect(const unsigned int* ADC_V, const unsigned int* ADC_U, const unsigned int* ADC_W)
{
    unsigned int adc_phase_L;
    unsigned int adc_phase_N;
    unsigned int adc_phase_H;
    
    static int flag_detected_1_phase = 0;
    static unsigned int adc_1_colector = 0;
    int status = STAT_COMMUT_NOT_DETECTED;
    
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
            status = STAT_COMMUT_DETECTED;
            flag_detected_1_phase = 0;
            colector_1 = adc_1_colector;
            adc_1_colector = 0;
            state = 2;
        }    
    }
    
    return status; 
}


int checking_state(const int unsigned *adc_phase_L, const unsigned int *adc_phase_N,
        const unsigned int *adc_phase_H)
{
    int status = STATUS_NOT_READY_YET;
    static unsigned int previous_adc_phase_N = V_MID;
    int flag_N_should_falling = state % 2;              // state = 0..5
    static int i = 0;
    
    if (*adc_phase_H > HIGH_RANGE_DOWN_LIMIT)
    {
        if (*adc_phase_L < LOW_RANGE_UP_LIMIT)
        {
            if (flag_N_should_falling)
            {
                if (*adc_phase_N < previous_adc_phase_N)
                {
                    i++;
                    if (i >= 3)
                    {
                        status = STATUS_ALREADY;
                        i = 0;
                    }
                }
                else
                {
                    status = STATUS_NOT_READY_YET;
                    i = 0;
                }
            }
            else
            {
                if (*adc_phase_N > previous_adc_phase_N)
                {
                    i++;
                    if (i >= 3)
                    {
                        status = STATUS_ALREADY;
                        i = 0;
                    }
                }
                else
                {
                    status = STATUS_NOT_READY_YET;
                    i = 0;
                }                
            }
        }
    }
    previous_adc_phase_N = *adc_phase_N;
    
    return status;
}


int detect_crossing_zero(const unsigned int *adc_phase_N,
        unsigned int LIMIT)
{
    if (state % 2)  // dla stanow 1, 3, 5, kiedy to napiecie na fazie N opada
    {
        if (*adc_phase_N < LIMIT)
            return STATUS_ALREADY;
        else
            return STATUS_NOT_READY_YET;
    }
    else            // dla stanow 0, 2, 4, kiedy to napi?cie na fazie N rosnie
    {
        if (*adc_phase_N > LIMIT)
            return STATUS_ALREADY;
        else
            return STATUS_NOT_READY_YET;        
    }
}


int commutation_delay(const unsigned int *adc_phase_N)
{
    static unsigned int container = 0;
    container += *adc_phase_N;
    if (container >= FULL_CONTAINER)
    {
        container = 0;
        return STATUS_ALREADY;
    }
    else
        return STATUS_NOT_READY_YET;
}

void set_state(int state)
{
    bridge_set_state(state + 1);
    /* "state + 1" poniewaz, zakres stanow dla tej funkcji obejmuje 1..6, a nie
     * 0..5. Wartosc '0' to stan wysokiej impedancji wszyskich trzech faz.
     * Zabezpieczenie przed niedozwolonymi wartosciami jest wewnatrz funkcji 
     * 'bridge_set_state()'. */
}

void commutation (const unsigned int* ADC_V, const unsigned int* ADC_U,
        const unsigned int* ADC_W)
{
    /* Tablice do posredniego wskazywania wartosci ADC faz "fizycznych"
     * (V, U, W), przez wskazniki faz "logicznych" (N, H, L).
     * Kolejnosc w tablicach odpowiada kolejnosci wystepowania stanow faz.
     * Oznaczenia: N - aktualna faza w stanie wysokiej impedancji,
     * H - faza zwarta do V_BLDC, L - faza zwarta do GND. */
    const unsigned int *phase_N_sequence[6] = 
        { ADC_U, ADC_W, ADC_V, ADC_U, ADC_W, ADC_V };
    const unsigned int *phase_H_sequence[6] = 
        { ADC_W, ADC_U, ADC_U, ADC_V, ADC_V, ADC_W };
    const unsigned int *phase_L_sequence[6] = 
        { ADC_V, ADC_V, ADC_W, ADC_W, ADC_U, ADC_U };
    
    const unsigned int *phase_N, *phase_H, *phase_L;
    
    static unsigned int previous_phase_N = V_MID;
     
    /* Wskazywanie na wyniki ADC, dla trzech faz, odpowiednio dla obecnego
     * polozenia silnika. Zmienna 'state' moze wynosic 0..5! */
    phase_N = phase_N_sequence[state];
    phase_H = phase_H_sequence[state];
    phase_L = phase_L_sequence[state];
    
    
    /* W ponizszym 'switch', wyrazenia 'break' celowo sa w warunkach, a nie
     * w ka?dym 'case', by program przechodzil do nastepnego zadania, jezeli
     * poprzednie zadanie zakonczylo sie sukcesem. 
     * Do zmiennej 'task' jest przypisywany nr aktualnie wykonywanego zadania,
     * by nastepne wywolanie tej funkcji w przerwaniu, posiadalo informacje,
     * ktore zadanie kontynuowac.
     * W ostatnim zadaniu 'TASK_COMMUTATION_NOW',zmiennej 'task' jest
     * przypisywana wartosc zadania, od ktorego ma sie rozpoczac nowy cykl.
     * Ustawiany jest te? nr nastepnego stanu i jest wywolywana funkcja do
     * komutacji, czyli przelaczenia mostka MOSFET. */
    switch (task)
    {
        case TASK_NOT_SPECIFIED:
            /* Przechodzi do nastepnego zadnia. */
            
        case TASK_CHECKING_STATE:
            /* Sprwadzenie wystapienia stanu polozenia wirnika, okreslonego
             * przez zminna 'int state'. */
            task = TASK_CHECKING_STATE;
            if (checking_state(phase_L, phase_N, phase_H) == 
                    STATUS_NOT_READY_YET)
                break;
            
        case TASK_CROSSING_ZERO_DET:
            /* Sprawdza, czy napiecie na fazie neutralnej przkroczylo V_MID.
             * Od 'state' zalezy, czy wykrywane jest przekroczenie "od gory",
             * czy "od dolu". */
            task = TASK_CROSSING_ZERO_DET; // dla przyszlego przerwania
            if (detect_crossing_zero(phase_N, V_MID) == 
                    STATUS_NOT_READY_YET)
                break;
            
        case TASK_DELAY:
            /* Opoznienie po przekroczeniu V_MID, przed komutacja. */
            task = TASK_DELAY;
            if (commutation_delay(phase_N) == STATUS_NOT_READY_YET)
                break;
            
        case TASK_COMMUTATION_NOW:
            /* Wykonanie komutacji. */
            state++;
            if(state == 6)
                state = 0;
            set_state(state);
            task = TASK_CHECKING_STATE;
            break;
    }
    
    previous_phase_N = *phase_N;    // obecne napiecie na 
}
