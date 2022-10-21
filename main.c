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
#include "delay.h"
#include "uart.h"
#include "adc.h"
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


typedef unsigned char uchar_t;
unsigned int Adcresult[100];
unsigned int AdcresultCurrent[100];
unsigned int CheckVbldc[100];


unsigned int ISO_check_Vbldc(unsigned int *out_check_Vbldc) 
{
    (*out_check_Vbldc)= 0;
    if (PORTBbits.RB12)
        (*out_check_Vbldc)= 1;
}


int main() {
    
    static unsigned char x= 0;
    unsigned int wynik_ADC_Vbat= 0;
    unsigned int wynik_ADC_Current = 0;
    unsigned int wynik_check_Vbldc = 0;
    unsigned int flaga_skip_start = 0;
    
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELE = 0;
    ANSELG = 0;
    ANSELAbits.ANSA1 = 1;   // A1 jako wej analogowe (VBAT_ADC)
    ANSELBbits.ANSB0 = 1;   // B0 jako wej analogowe (Current_Sense_ADC) 
    
    
    RPA7Rbits.RPA7R = 0b00110; //Pin C2RX_2 skonfigurowany jako wyjscie OC5
    
    TRISGbits.TRISG6 = 0;   // pierwotnie C1RX1, aktualnie UART1 TX (niebiski)
    TRISGbits.TRISG8 = 1;   // pierwotnie C1TX1, aktulanie UART1 RX (zielony)
    TRISBbits.TRISB13 = 0;  // SKIP
    TRISAbits.TRISA7 = 0;   // OC5 (PWM), pierowtnie A10
    TRISBbits.TRISB12 = 1;  // ISO_CHECK_V_BLDC
    TRISFbits.TRISF0 = 0;   // ISO_U_PMOS_H
    TRISBbits.TRISB10 = 0;  // ISO_V_PMOS_H
    TRISBbits.TRISB11 = 0;  // ISO_W_PMOS_H
    TRISCbits.TRISC8 = 0;   // U_NMOS_L
    TRISCbits.TRISC6 = 0;   // V_NMOS_L
    TRISCbits.TRISC7 = 0;   // W_NMOS_L

    
    //LATGbits.LATG6 = 0;     
    //LATGbits.LATG8 = 1;     
    LATBbits.LATB13 = 0;    // SKIP
    //LATAbits.LATA7 = 0;   // PWM
    
    /* UART 1 */
    U1RXR = 0b1010;         // powi?zanie UART1 RX z pinem G8 (RPG8)
    RPG6R = 0b00001;        // powi?zanie UART1 TX z pinem G6 (U1TX)
    
    UART_Init();
        
    /* TIMER 2 do PWM */
    T2CONbits.ON = 0;       //W czasie konfiguracji timer musi byc wylaczony
    TMR2 = 0x0000;
    PR2 = 0x003C;           //Wartosc przy ktorej timer sie przepelnia
    T2CONbits.TCKPS = 0b001; //Prescaler 2, gen 10MHz, uC 120MHz, magistrala 60MHz, licznik 30MHz
    T2CONbits.TCS = 0; 
    T2CONbits.ON = 1;       //Timer zostaje wlaczony
    
    /* OC5 jako PWM */
    OC5CONbits.OCM = 0b110; //Tryb PWM
    OC5CONbits.OCTSEL = 0;  //Timer drugi jest ?ród?em zegara dla modulu output compare
    OC5RS = 0x001E;         //Wspólczynik wypelnienia 
    OC5CONbits.ON = 1;      //Aktywaca modulu Output Compare
    
    // FRAGMENT NIZBEDNY DO URUCHOMIENIA PRZETWORNICY PWM - POCZATEK
    
    /* SKIP=0 przez pierwsze  333 ns dzi?ania PWM, 
     * pó?niej SKIP=1, przetwornica w trybie FCCM */
    
    // W ten sposób przetwornica nie dzia?a
    //while (TMR2<=0x000A);
    //LATBbits.LATB13 = 1;
    
    // W ten sposób prztwornica dzia?a 
    while(!flaga_skip_start)
    {
        if (TMR2==0x0005) {
            flaga_skip_start = 1;
        }
        if (flaga_skip_start) {
            LATBbits.LATB13 = 1;
        }            
    }
    
    // FRAGMENT NIZBEDNY DO URUCHOMIENIA PRZETWORNICY PWM - KONIEC
    
    ADC_init();
    
    
    // TEST WYJSC DO KOMUTACJI - START
    LATFbits.LATF0 = 0;     // U_PMOS
    LATBbits.LATB10 = 1;    // V_PMOS
    LATBbits.LATB11 = 1;    // W_PMOS
    
    LATCbits.LATC8 = 0;     // U_NMOS
    LATCbits.LATC6 = 1;     // V_NMOS
    LATCbits.LATC7 = 0;     // W_NMOS
    //TEST WYJSC DO KOMUTACJI - KONIEC
    
    
    while(1)
    {
        ADC_meas(&wynik_ADC_Vbat, &wynik_ADC_Current);
//        printf("Wysylam liczbe: %d, %d, %d\n\r", x, wynik_ADC_Vbat, wynik_ADC_Current);
        Adcresult[x]= wynik_ADC_Vbat;
        AdcresultCurrent[x]= wynik_ADC_Current;
        ISO_check_Vbldc(&wynik_check_Vbldc);
        CheckVbldc[x]= wynik_check_Vbldc;
        x++;
        if(x==100)
            x= 0;
//        delay_ms(1000);
    }
    return (EXIT_SUCCESS);
}




