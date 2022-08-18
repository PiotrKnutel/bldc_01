/* Pisane w oparciu o not? i instrukcj? referencyjn? (sekcja 22) */

#include <xc.h>
#include "adc.h"
#include <stdio.h>
#include <stdlib.h>

void ADC_init() {
    /* ADC 1 */
    /* Procedura z noty, pocz?wszy od str. 371 */
    ADC1CFG = DEVADC1;
    ADCCON1bits.AICPMPEN = 0;   // bo Vdd =< 2.5V
    CFGCONbits.IOANCPEN = 0;    // bo Vdd =< 2.5V
    ADCCON1bits.ON = 0;         // wy?. ADC
    /* Pozosta?? bity ADCCON1 nie zmieniane */

    ADCCON2bits.CVDCPL = 0b111; // Kondensator CVD = 17.5pF
    ADCCON2bits.SAMC = 0x3FF;   // (wa?ne) 1025*Tad, dla Shared_ADC
    ADCCON2bits.BGVRIEN = 0;    // brak generowania przerwa?, gdy BGVRRDY=1
    ADCCON2bits.REFFLTIEN =0;   // brak generowania przerwa?, gdy REFFLT=1
    ADCCON2bits.EOSIEN = 0;     // brak generowania przerwa?, gdy EOSRDY=1
    ADCCON2bits.ADCEIOVR = 0;   // generowanie przerwa? jest kontrolowane przez ADCEIEN 1 i 2
    //ADCCON2bits.ECRIEN = 1;     // mo?liwe uruchomienie ADC z zewn?trznego modu?u, np. PTG (Peripherial Trigger Generator)
    ADCCON2bits.ADCEIS = 0b000; // Wczesne przewanie Shared_ADC jest generowane 1 takt zegara ADC przed ko?cem konwersji
    ADCCON2bits.ADCDIV = 0x7F;  // (wa?ne) Tad=254*Tq, taktowanie dla Shared_ADC=taktowanie_ADC/254

    ADCANCONbits.ANEN0 = 0;
    ADCANCONbits.ANEN1 = 0;
    ADCANCONbits.ANEN2 = 0;
    ADCANCONbits.ANEN3 = 0;
    ADCANCONbits.ANEN4 = 0;
    ADCANCONbits.ANEN5 = 0;
    ADCANCONbits.ANEN7 = 0;

    ADCCON3bits.DIGEN0 = 0;
    ADCCON3bits.DIGEN1 = 0;
    ADCCON3bits.DIGEN2 = 0;
    ADCCON3bits.DIGEN3 = 0;
    ADCCON3bits.DIGEN4 = 0;
    ADCCON3bits.DIGEN5 = 0;
    ADCCON3bits.DIGEN7 = 0;

    ADCCON3bits.ADCSEL = 0;         // (wa?ne) ?r�d?o takowania ADC (Tclk): 0=PBCLK, 3=SystemClock
    ADCCON3bits.CONCLKDIV = 0x00;   // (wa?ne) Tq=Tclk, dzielnik takowania
    ADCCON3bits.VREFSEL = 0;        // (wa?ne) wyb�r wej. dla Vref, 0=[AVdd i AVss]
    /* pozosta?e bity ADCCON3 nie zmieniane */

    ADC1TIMEbits.ADCEIS = 0;        // Wczesne przewanie ADC 1 jest generowane 1 takt zegara ADC przed ko?cem konwersji, je?li ADCEIS=8 to 8 cykli...
    ADC1TIMEbits.SELRES = 0b11;     // rozdzielczo?? 12 bit�w
    //ADC1TIMEbits.DMAEN = 0;         // DMA 0=wy?.
    ADC1TIMEbits.ADCDIV = 1;        // (wa?ne) Tad=2*Tq, dzielnik taktowania ADC
    ADC1TIMEbits.SAMC = 0x3FF;      // (wa?ne) czas pr�bkowania, 0x3FF = 1025*Tad

}