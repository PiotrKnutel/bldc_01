/* PWM dla przetwornicy buck step-down CSD95377Q4M.
 * Realizowany poprzez blok Motor Control PWM (MCPWM). Nota "Section 44". */

#include "pwm.h"

void pwm_config()
{
    PTCONbits.PTEN = 0; //wylaczenie modu?u PWM
    
    PMD4bits.PWM1MD = 1;
    PMD4bits.PWM2MD = 1;
    PMD4bits.PWM3MD = 1;
    PMD4bits.PWM5MD = 1;
    PMD4bits.PWM6MD = 1;
    PMD4bits.PWM7MD = 1;
    PMD4bits.PWM8MD = 1;
    PMD4bits.PWM9MD = 1;
    PMD4bits.PWM10MD = 1;
    PMD4bits.PWM11MD = 1;
    PMD4bits.PWM12MD = 1;
    
    PTCONbits.PCLKDIV = 0b000; // prescaler pierwszy, 0 to 1/FSYSCLK
    
    // gdy ITB=1 to zamiast PTPER jest u?ywane PHASE.
    //PTPER = 0x00F0;     // min. to 0x0008; 0x00F0=240; wzor 4 na str. 44-10.
    PWMCON4bits.MTBS = 0; //wybor zrodla zegara, 0 to Primary master time base
    
    PWMCON4bits.ITB = 1; // Independent Time Base Mode
    PWMCON4bits.DTC = 0b0010; //Dead time function is disabled
    IOCON4bits.PENH = 1; // modul PWM kontroluje pin PWM4H
    IOCON4bits.PENL = 1; // GPIO kontroluje pin PWM4L
    IOCON4bits.PMOD = 0b0011; // PWM4L utrzywywane w stanie '0' (ale raczej nie potrzebne gdy PENL=0)
    IOCON4bits.FLTMOD = 0b0011;   // wyl. wej. fault
    
    PHASE4 = 0x00F0;
    PDC4 = 0x0078; // PWM Genertaor Duty Cycle 0x0078=120 (po?owa 240)
    
    PTCONbits.PTEN = 1;
}
