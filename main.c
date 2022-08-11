/* 
 * File:   main.c
 * Author: user
 *
 * Created on 1 sierpnia 2022, 14:38
 */

#include "p32mk1024mcf064.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
/*
 * 
 */

//******************************************************************************
//* C O N F I G  C L O C K  S E C T I O N
//******************************************************************************
#pragma config ICESEL = ICS_PGx1

// Device Config Bits in  DEVCFG1:	
#pragma config FNOSC =      SPLL
#pragma config FSOSCEN =	ON
#pragma config POSCMOD =	EC
#pragma config OSCIOFNC =	OFF
	
// Device Config Bits in  DEVCFG2:	
#pragma config FPLLICLK =	PLL_POSC
#pragma config FPLLIDIV =	DIV_1
#pragma config FPLLMULT =	MUL_48
#pragma config FPLLODIV =	DIV_4
#pragma config FPLLRNG =	RANGE_5_10_MHZ
#pragma config UPLLEN =     OFF
//#pragma config UPLLFSEL =	FREQ_12MHZ


#pragma config FDMTEN = OFF
#pragma config WDTSPGM = STOP
#pragma config DMTCNT = DMT31
//#pragma config FSOSCEN = OFF
//#pragma config FUSBIDIO = OFF
//#pragma config FMIIEN = OFF //RMII OFF
//#pragma config IOL1WAY = OFF
//#pragma config FCKSM = CSECME
#pragma config JTAGEN = OFF


int main() {
    
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELE = 0;
    ANSELG = 0;
    
    
    RPA7Rbits.RPA7R = 0b00110; //Pin C2RX_2 skonfigurowany jako wyjscie OC5
    
    TRISGbits.TRISG6 = 0;
    TRISGbits.TRISG8 = 0;
    TRISBbits.TRISB13 = 0;  // SKIP
    TRISAbits.TRISA7 = 0;   // PWM // pierowtnie A10
    
    LATGbits.LATG6 = 0;     // UART RX 1
    LATGbits.LATG8 = 1;     // UART TX 1
    LATBbits.LATB13 = 0;    // SKIP
    //LATAbits.LATA7 = 0;    // PWM
    
    
    T2CONbits.ON = 0;       //W czasie konfiguracji timer musi byc wylaczony
    TMR2 = 0x0000;
    PR2 = 0x003C;           //Wartosc przy ktorej timer sie przepelnia
    T2CONbits.TCKPS = 0b001; //Prescaler 2, gen 10MHz, uC 120MHz, magistrala 60MHz, licznik 30MHz
    T2CONbits.TCS = 0; 
    T2CONbits.ON = 1;       //Timer zostaje wlaczony
    
    
    OC5CONbits.OCM = 0b110; //Tryb PWM
    OC5CONbits.OCTSEL = 0;  //Timer drugi jest ?ród?em zegara dla modulu output compare
    OC5RS = 0x001E;          //Wspólczynik wypelnienia 50%
    OC5CONbits.ON = 1;      //Aktywaca modulu Output Compare
    
    int flaga_skip_start = 0;
    
    while(1)
    {
        /* SKIP=0 przez pierwsze  333 ns dzi?ania PWM, 
         * pó?niej SKIP=1, przetwornica w trybie FCCM */
        if (TMR2==0x000A) {
            flaga_skip_start = 1;
        }
        if (flaga_skip_start) {
            LATBbits.LATB13 = 1;
        }
            
    }
    return (EXIT_SUCCESS);
}




