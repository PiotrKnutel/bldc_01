/* 
 * File:   main.c
 * Author: Piotr Knutel pk1@linux.pl 156476@stud.prz.edu.pl
 *
 * Created on 1 sierpnia 2022, 14:38
 */

#include "p32mk1024mcf064.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "pragma_config.h"
#include "delay.h"
#include "uart.h"
#include "adc.h"
#include "pwm.h"
#include "bridge.h"
#include "current.h"

typedef unsigned char uchar_t;
unsigned int Adcresult[100];
unsigned int AdcresultCurrent[100];
unsigned int AdcresultW[100];
unsigned int AdcresultV[100];
unsigned int AdcresultU[100];
unsigned int AdcresultVbldc[100];
unsigned int ADC_res[6]; // kolejnosc: [Vbat, Current, W, V, U, Vbldc]

unsigned int current;           // prad zmierzony
unsigned int current_specified; //zadany prad
unsigned int next_PWM;          // wartosc PWM do ustawienia

static int stan = 0;

void komutacja()
{
    //stan = ((!stan) ? 2 : 0);
    //if (stan==0) stan=2; else stan=0;
    stan++;
    if (stan==7)
        stan=1;
    test_faz(stan);
}

void __attribute__((vector(_ADC_URDY_VECTOR), interrupt(IPL7SRS), nomips16)) 
adc_update_ready_after_suspend_handler()
{
	IFS3bits.AD1RSIF = 0;	// Clear interrupt flag
    //IFS3bits.AD1D0IF= 0;
    ADC_meas(&ADC_res[0], &ADC_res[1], &ADC_res[2], &ADC_res[3], &ADC_res[4], &ADC_res[5]);
    current = ADC_res[1]; // wyluskanie
    current_specified = 2500; // tymaczaowo tutaj ustalane
    next_PWM = current_controller(current, current_specified);
    pwm_set(next_PWM);
}


void __attribute__((vector(_TIMER_3_VECTOR), interrupt(ipl3soft), nomips16)) 
timer3_handler()
{
	IFS0bits.T3IF = 0;	// Clear interrupt flag for timer 3
    //komutacja();
    if(LATAbits.LATA10 == 0){
        LATAbits.LATA10 = 1;
    }else
          LATAbits.LATA10 = 0;
}

void timer3_interrupt_init(int frequency)
{
    T3CON = 0x0;                // Disable timer 3 when setting it up
    TMR3 = 0;                   // Set timer 3 counter to 0
    // do komutacji trzeba jeszcze podzielic przez /12
    PR3 = 600;

    T3CONbits.TCKPS = 0b001;    // Pre-scale of 2
    T3CONbits.TCS = 0;          // Internal clock
 	IEC0bits.T3IE = 0;          // Disable Timer 3 Interrupt
 	IFS0bits.T3IF = 0;          // Clear interrupt flag for timer 3
    IPC3bits.T3IP = 3;          // Interrupt priority 3
    IPC3bits.T3IS = 1;          // Sub-priority 1
////    IEC0bits.T3IE = 1;          // Enable Timer 3 
 	T3CONbits.ON = 1;           // Module is enabled
}


int main() {
    
    static unsigned char x= 0;
    unsigned int wynik_ADC_Vbat= 0;
    unsigned int wynik_ADC_Current = 0;
    unsigned int wynik_ADC_W = 0;
    unsigned int wynik_ADC_V = 0;
    unsigned int wynik_ADC_U = 0;
    unsigned int wynik_ADC_Vbldc = 0;
    
    unsigned int flaga_skip_start = 0;
    INTCONbits.MVEC= 1;
    PRISS= 0x76543211;
    asm volatile("ei");
    
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELE = 0;
    ANSELG = 0;
    
    ANSELAbits.ANSA1  = 1;  // A1 jako wej analogowe (VBAT_ADC)
    ANSELBbits.ANSB0  = 1;  // B0 jako wej analogowe (Current_Sense_ADC)
    ANSELAbits.ANSA8  = 1;  // A8 jako wej analogowe (Wsens_ADC)
    ANSELCbits.ANSC1  = 1;  // C1 jako wej analogowe (Usens_ADC)
    ANSELAbits.ANSA4  = 1;  // A4 jako wej analogowe (Vsens_ADC)
    ANSELBbits.ANSB7  = 1;  // B7 jako wej analogowe (VBLDCsens_ADC)
    
    TRISGbits.TRISG6  = 0;  // C1RX1
    TRISGbits.TRISG8  = 1;  // C1TX1
     
    TRISBbits.TRISB13 = 0;  // SKIP
    TRISAbits.TRISA10 = 1;  // PWM (NIE WOLNO OUTPUT !!! Przypis 1 str. 44-22)
    
    TRISBbits.TRISB12 = 1;  // ISO_CHECK_V_BLDC (nie uzywane)
    TRISFbits.TRISF0  = 0;  // ISO_U_PMOS_H
    TRISBbits.TRISB10 = 0;  // ISO_V_PMOS_H
    TRISBbits.TRISB11 = 0;  // ISO_W_PMOS_H
    TRISCbits.TRISC8  = 0;  // U_NMOS_L
    TRISCbits.TRISC6  = 0;  // V_NMOS_L
    TRISCbits.TRISC7  = 0;  // W_NMOS_L
    
    //LATGbits.LATG6 = 0;    // C1RX1
    //LATGbits.LATG8 = 1;    // C1TX1
    LATBbits.LATB13 = 0;    // SKIP
    
    /* UART 1 */
    //U1RXR = 0b1010;         // powi?zanie UART1 RX z pinem G8 (RPG8)
    //RPG6R = 0b00001;        // powi?zanie UART1 TX z pinem G6 (U1TX)

    //UART_Init();
    
    // STAN NEUTRALNY WSZYSTKICH FAZ - PO URUCHOMIENIU
    test_faz(0);
    
    /* TIMER 2 do PWM */
    T2CONbits.ON = 0;       //W czasie konfiguracji timer musi byc wylaczony
    TMR2 = 0x0000;
    PR2 = 0x003C;           //Wartosc przy ktorej timer sie przepelnia
    T2CONbits.TCKPS = 0b001; //Prescaler 2, gen 10MHz, uC 120MHz, magistrala 60MHz, licznik 30MHz
    T2CONbits.TCS = 0;
 
    /* OC5 jako PWM */
    /*
    OC5CONbits.OCM = 0b110; //Tryb PWM
    OC5CONbits.OCTSEL = 0;  //Timer drugi jest ?ród?em zegara dla modulu output compare
    OC5RS = 0x001E;         //Wspólczynik wypelnienia
    */
    
    pwm_config();
    
    /* Wlaczenie liczników i OC */
    T2CONbits.ON = 1;       //Timer zostaje wlaczony
    //OC5CONbits.ON = 1;      //Aktywaca modulu Output Compare
    
            
    // FRAGMENT NIZBEDNY DO URUCHOMIENIA PRZETWORNICY PWM - POCZATEK
    
    /* SKIP=0 przez pierwsze  333 ns dzi?ania PWM, 
     * pó?niej SKIP=1, przetwornica w trybie FCCM */
    
    // W ten sposób przetwornica nie dziala
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
    LATFbits.LATF0 = 1;     // U_PMOS
    LATBbits.LATB10 = 1;    // V_PMOS
    LATBbits.LATB11 = 1;    // W_PMOS
    
    LATCbits.LATC8 = 0;     // U_NMOS
    LATCbits.LATC6 = 0;     // V_NMOS
    LATCbits.LATC7 = 0;     // W_NMOS
    //TEST WYJSC DO KOMUTACJI - KONIEC
    
    //timer3_interrupt_init(10000);        //przerwanie z f = x Hz
    test_faz(6);
    
    pwm_set(5); // od 5 do 204, czyli 2%..85% z 240
    
    /*Wlaczenie TIMERA 1 */
    // Wlaczenie taktowania ADC, a w konsewkencji przerwan do regulatora I.
    T1CONbits.ON = 1;
    
    //printf("Start programu. \n");

    while(1)
    {
        /*
        ADC_meas(&wynik_ADC_Vbat, &wynik_ADC_Current, &wynik_ADC_W, &wynik_ADC_V, &wynik_ADC_U, &wynik_ADC_Vbldc);
        //printf("Wysylam liczbe: %d, %d, %d\n\r", x, wynik_ADC_Vbat, wynik_ADC_Current);
        Adcresult[x]= wynik_ADC_Vbat;
        AdcresultCurrent[x]= wynik_ADC_Current;
        AdcresultW[x]= wynik_ADC_W;
        AdcresultV[x]= wynik_ADC_V;
        AdcresultU[x]= wynik_ADC_U;
        AdcresultVbldc[x]= wynik_ADC_Vbldc;
        
        x++;
        delay_us(60);
        if(x==100)
        {
            x= 0;
        }
        */
//        delay_ms(1000);
        
        // prosty prostokat z PWM
        delay_ms(2000);
        set_pwm(120);
        delay_ms(2000);
        set_pwm(5);
       
    }
    return (EXIT_SUCCESS);
}
