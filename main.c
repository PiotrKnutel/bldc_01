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
#pragma config FPLLIDIV =	DIV_5
#pragma config FPLLMULT =	MUL_1
#pragma config FPLLODIV =	DIV_2
#pragma config FPLLRNG =	RANGE_BYPASS
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
    PR2 = 0x000C;           //Wartosc przy ktorej timer sie przepelnia
    T2CONbits.TCKPS = 0;    //Prescaler 1, taktowanie uC 1Mhz, takowanie szyny PB2 500kHz, timer taktowany 500kHz
    T2CONbits.TCS = 0; 
    T2CONbits.ON = 1;       //Timer zostaje wlaczony
    
    
    OC5CONbits.OCM = 0b110; //Tryb PWM
    OC5CONbits.OCTSEL = 0;  //Timer drugi jest ?ród?em zegara dla modulu output compare
    OC5RS = 0x000B;          //Wspó?czynik wype?nienia 32767/65535 czyli oko?o 50%
    OC5CONbits.ON = 1;      //Aktywaca modulu Output Compare
    
    
    while(1)
    {
        if(TMR2==0x0001)
            LATBbits.LATB13 = 1;
        if(TMR2==0)
            LATBbits.LATB13 = 0;
    }
    return (EXIT_SUCCESS);
}




