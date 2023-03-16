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
unsigned int AdcresultW[100];
unsigned int AdcresultV[100];
unsigned int AdcresultU[100];
unsigned int AdcresultVbldc[100];

static int stan = 0;

unsigned int ISO_check_Vbldc(unsigned int *out_check_Vbldc) 
{
    (*out_check_Vbldc)= 0;
    if (PORTBbits.RB12)
        (*out_check_Vbldc)= 1;
}


// PROWIZORYCZNY WYBOR ZASILANIA CEWEK / REZYSTOROW ODBIORNIKA
void test_faz(int stan) {
    switch (stan) {
        case 0:
            LATFbits.LATF0 = 1;     // U_PMOS
            LATBbits.LATB10 = 1;    // V_PMOS
            LATBbits.LATB11 = 1;    // W_PMOS

            LATCbits.LATC8 = 0;     // U_NMOS
            LATCbits.LATC6 = 0;     // V_NMOS
            LATCbits.LATC7 = 0;     // W_NMOS
            break;
        case 1:
            LATFbits.LATF0 = 0;     // U_PMOS
            LATBbits.LATB10 = 1;    // V_PMOS
            LATBbits.LATB11 = 1;    // W_PMOS
    
            LATCbits.LATC8 = 0;     // U_NMOS
            LATCbits.LATC6 = 1;     // V_NMOS
            LATCbits.LATC7 = 0;     // W_NMOS
            break;
        case 2:
            LATFbits.LATF0 = 0;     // U_PMOS
            LATBbits.LATB10 = 1;    // V_PMOS
            LATBbits.LATB11 = 1;    // W_PMOS
    
            LATCbits.LATC8 = 0;     // U_NMOS
            LATCbits.LATC6 = 0;     // V_NMOS
            LATCbits.LATC7 = 1;     // W_NMOS
            break;
        case 3:
            LATFbits.LATF0 = 1;     // U_PMOS
            LATBbits.LATB10 = 0;    // V_PMOS
            LATBbits.LATB11 = 1;    // W_PMOS
    
            LATCbits.LATC8 = 0;     // U_NMOS
            LATCbits.LATC6 = 0;     // V_NMOS
            LATCbits.LATC7 = 1;     // W_NMOS
            break;
        case 4:
            LATFbits.LATF0 = 1;     // U_PMOS
            LATBbits.LATB10 = 0;    // V_PMOS
            LATBbits.LATB11 = 1;    // W_PMOS
    
            LATCbits.LATC8 = 1;     // U_NMOS
            LATCbits.LATC6 = 0;     // V_NMOS
            LATCbits.LATC7 = 0;     // W_NMOS
            break;
        case 5:
            LATFbits.LATF0 = 1;     // U_PMOS
            LATBbits.LATB10 = 1;    // V_PMOS
            LATBbits.LATB11 = 0;    // W_PMOS
    
            LATCbits.LATC8 = 1;     // U_NMOS
            LATCbits.LATC6 = 0;     // V_NMOS
            LATCbits.LATC7 = 0;     // W_NMOS
            break;
        case 6:
            LATFbits.LATF0 = 1;     // U_PMOS
            LATBbits.LATB10 = 1;    // V_PMOS
            LATBbits.LATB11 = 0;    // W_PMOS
    
            LATCbits.LATC8 = 0;     // U_NMOS
            LATCbits.LATC6 = 1;     // V_NMOS
            LATCbits.LATC7 = 0;     // W_NMOS
            break;
        default:
            LATFbits.LATF0 = 1;     // U_PMOS
            LATBbits.LATB10 = 1;    // V_PMOS
            LATBbits.LATB11 = 1;    // W_PMOS
    
            LATCbits.LATC8 = 0;     // U_NMOS
            LATCbits.LATC6 = 0;     // V_NMOS
            LATCbits.LATC7 = 0;     // W_NMOS
            break;            
    }
}

void komutacja()
{
    
    //stan = ((!stan) ? 2 : 0);
    //if (stan==0) stan=2; else stan=0;
    stan++;
    if (stan==7)
        stan=1;
    test_faz(stan);
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
    IEC0bits.T3IE = 1;          // Enable Timer 3 Interrupt

    asm volatile("ei");
 	T3CONbits.ON = 1;           // Module is enabled
}

void pwm_config()
{
    PTCONbits.PTEN = 0; //wylaczenie modu?u PWM
    PTCONbits.PCLKDIV = 0b000; // prescaler pierwszy, 0 to 1/FSYSCLK
    PTPER = 0x00F0;     // min. to 0x0008; 0x00F0=240; wzor 4 na str. 44-10.
    
    PWMCON4bits.MTBS = 0; //wybor zrodla zegara, 0 to Primary master time base
    
    IOCON4bits.PENH = 1; // modul PWM kontroluje pin PWM4H
    IOCON4bits.PENL = 0; // GPIO kontroluje pin PWM4L
    IOCON4bits.PMOD = 0b11; // PWM4L utrzywywane w stanie '0' (ale raczej nie potrzebne gdy PENL=0)
    
    PDC4bits.PDC = 0x0078; // PWM Genertaor Duty Cycle 0x0078=120 (po?owa 240)
    
    PTCONbits.PTEN = 1;
}

int main() {
    
    static unsigned char x= 0;
    unsigned int wynik_ADC_Vbat= 0;
    unsigned int wynik_ADC_Current = 0;
    unsigned int wynik_check_Vbldc = 0;
    unsigned int wynik_ADC_W = 0;
    unsigned int wynik_ADC_V = 0;
    unsigned int wynik_ADC_U = 0;
    unsigned int wynik_ADC_Vbldc = 0;
    
    unsigned int flaga_skip_start = 0;
    
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELE = 0;
    ANSELG = 0;
    /*
    ANSELAbits.ANSA1 = 1;   // A1 jako wej analogowe (VBAT_ADC)
    ANSELBbits.ANSB0 = 1;   // B0 jako wej analogowe (Current_Sense_ADC)
    ANSELAbits.ANSA8 = 1;   // A8 jako wej analogowe (Wsens_ADC)
    ANSELCbits.ANSC1 = 1;   // C1 jako wej analogowe (Usens_ADC)
    ANSELAbits.ANSA4 = 1;   // A4 jako wej analogowe (Vsens_ADC)
    ANSELBbits.ANSB7 = 1;   // B7 jako wej analogowe (VBLDCsens_ADC)    
    
    RPA7Rbits.RPA7R = 0b00110; //Pin C2RX_2 skonfigurowany jako wyjscie OC5
    
    TRISGbits.TRISG6 = 0;   // pierwotnie C1RX1, aktualnie UART1 TX (niebiski)
    TRISGbits.TRISG8 = 1;   // pierwotnie C1TX1, aktulanie UART1 RX (zielony)
    */ 
    TRISBbits.TRISB13 = 0;  // SKIP
    //TRISAbits.TRISA7 = 0;  // PWM
    TRISAbits.TRISA10 = 0;  // PWM
    
    //TRISBbits.TRISB12 = 1;  // ISO_CHECK_V_BLDC
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
    LATAbits.LATA10 = 0;
    
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
    
    
    //ADC_init();
    
    // TEST WYJSC DO KOMUTACJI - START
    LATFbits.LATF0 = 1;     // U_PMOS
    LATBbits.LATB10 = 1;    // V_PMOS
    LATBbits.LATB11 = 1;    // W_PMOS
    
    LATCbits.LATC8 = 0;     // U_NMOS
    LATCbits.LATC6 = 0;     // V_NMOS
    LATCbits.LATC7 = 0;     // W_NMOS
    //TEST WYJSC DO KOMUTACJI - KONIEC
    
    //timer3_interrupt_init(10000);        //przerwanie z f = x Hz
    //test_faz(0);
    
    //printf("Start programu. \n");
    
    while(1)
    {
/*      
 *      LA
        ADC_meas(&wynik_ADC_Vbat, &wynik_ADC_Current, &wynik_ADC_W, &wynik_ADC_V, &wynik_ADC_U, &wynik_ADC_Vbldc);
        //printf("Wysylam liczbe: %d, %d, %d\n\r", x, wynik_ADC_Vbat, wynik_ADC_Current);
        Adcresult[x]= wynik_ADC_Vbat;
        AdcresultCurrent[x]= wynik_ADC_Current;
        AdcresultW[x]= wynik_ADC_W;
        AdcresultV[x]= wynik_ADC_V;
        AdcresultU[x]= wynik_ADC_U;
        AdcresultVbldc[x]= wynik_ADC_Vbldc;
        
        ISO_check_Vbldc(&wynik_check_Vbldc);
        CheckVbldc[x]= wynik_check_Vbldc;
        x++;
        delay_us(60);
        if(x==100)
        {
            x= 0;
        }
 */
//        delay_ms(1000);
    }
    return (EXIT_SUCCESS);
}
