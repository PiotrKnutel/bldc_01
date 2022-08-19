/* Pisane w oparciu o not? i instrukcj? referencyjn? (sekcja 22) */

#include <xc.h>
#include "adc.h"
#include "p32mk1024mcf064.h"
#include <stdio.h>
#include <stdlib.h>

void ADC_init() {
    /* ADC AN 1 */
    /* Procedura z noty, poczawszy od str. 371 
     * i z "reference manual" section 22 (w tym przyk??d 22-1 str. 66). */
    
    ADC1CFG = DEVADC1;
    
    /* Konfiguracja ADCCON 1 */
    ADCCON1 = 0;                    // bez funkcji z tego rejestru, w tym bit ON=1 (ADC wy?)
    
    ADCCON1bits.AICPMPEN = 0;       // bo Vdd =< 2.5V
    CFGCONbits.IOANCPEN = 0;        // bo Vdd =< 2.5V
    
    /* Inicjalizacja "warm up time" - ADCANCON */
    ADCANCON = 0;                   // w tym bity ANENx musz? by? 0
    ADCANCONbits.WKUPCLKCNT = 5;    // 5=2^5=32*Tad, po tylku taktach ADC b?dzie móg? konwertowa? 
    
    /* Ustawienie zegara - ADCCON 3 */
    ADCCON3 = 0;                    // w tym DIGENx musi by? 0
    ADCCON3bits.ADCSEL = 0;         // zródlo takowania ADC (Tclk): 0=PBCLK, 3=SystemClock
    ADCCON3bits.CONCLKDIV = 1;      // Tq=Tclk, dzielnik takowania, 1=polowa
    ADCCON3bits.VREFSEL = 0;        // wybór wej. dla Vref, 0=[AVdd i AVss]
    
    /* Ustawienie czasu próbowania i zegara konwersji - ADCxTIME */
    /* ADCx, gdzie x to nr dedykowanego ADC */
    ADC1TIMEbits.ADCEIS = 0;        // Wczesne przewanie ADC 1 jest generowane 1 takt zegara ADC przed ko?cem konwersji, je?li ADCEIS=8 to 8 cykli...
    ADC1TIMEbits.SELRES = 3;        // rozdzielczosc 3=12 bitów
    //ADC1TIMEbits.DMAEN = 0;         // DMA 0=wy?. (tego nie rozpozanawa? kompliator)
    ADC1TIMEbits.ADCDIV = 1;        // 1=Tad=2*Tq, dzielnik taktowania ADC
    ADC1TIMEbits.SAMC = 5;          // czas próbkowania, 0x3FF=1025*Tad, 5=5*Tad
    
    /* Ustawienie pinów jako wej?? do konkretnych ADC */
    ADCTRGMODEbits.SH1ALT = 0;      // jesli 0 to AN1 jest wej ADC 1 (VBAT_ADC), te bity umo?liwiaj? po??czenie innego pinu z ADC1 

    /* Wybór trybu wej ADC */
    ADCIMCON1bits.DIFF1 = 0;        // je?li 0 to AN1 u?ywa trybu Single-ended
    ADCIMCON1bits.SIGN1 = 0;        // je?li 0 to AN1 u?ywa trybu unsigned data
    
    
    
    
    
    
    ADCCON2bits.CVDCPL = 0b111; // Kondensator CVD = 17.5pF
    ADCCON2bits.SAMC = 0;   // (wa?ne) 0x3FF=1025*Tad, 0=2*Tad, dla Shared_ADC
    ADCCON2bits.BGVRIEN = 0;    // brak generowania przerwa?, gdy BGVRRDY=1
    ADCCON2bits.REFFLTIEN =0;   // brak generowania przerwa?, gdy REFFLT=1
    ADCCON2bits.EOSIEN = 0;     // brak generowania przerwa?, gdy EOSRDY=1
    ADCCON2bits.ADCEIOVR = 0;   // generowanie przerwa? jest kontrolowane przez ADCEIEN 1 i 2
    //ADCCON2bits.ECRIEN = 1;     // mo?liwe uruchomienie ADC z zewn?trznego modu?u, np. PTG (Peripherial Trigger Generator)
    ADCCON2bits.ADCEIS = 0b000; // Wczesne przewanie Shared_ADC jest generowane 1 takt zegara ADC przed ko?cem konwersji
    ADCCON2bits.ADCDIV = 0x7F;  // (wa?ne) Tad=254*Tq, taktowanie dla Shared_ADC=taktowanie_ADC/254
    
    
    ADCTRGMODEbits.STRGEN1 = 0;     // je?li 0 to nie u?ywa presynchronized triggers
    ADCTRGMODEbits.SSAMPEN1 = 0;    // je?li 0 to nie u?ywa synchronous sampling
    


    /* Rejestr ADCTRGSNS nie zmieniany. Wyszko bity 0. 
     Wej?cia analogowe reaguja na bocze narastaj?ce. */
    
    // nie wiadomo czy potrzebne 
    ADCCSS1bits.CSS1 = 1;           // wybór AN1 jako wej skanowania, pozotsa?e wej pomini?te 
    
    ADCGIRQEN1bits.AGIEN1 = 0;      // wl. przerwania je?li gotowe przetwarzane dane
    
    /* !!! Trzeba poprawi? !!! */
    ADCTRG1bits.TRGSRC1 = 1;  // wybór ?ród?a wyzwalania (trigger) AN1, 
    /* 0=brak wyzwalania, 0b10000=koniec okresu OC1, 1=software zbocze
    /* dla ADC Klasy 1 trigger powoduje przerwanie próbkowania i rozpocz?cie konwersji */
    
    /* ADCBASE to rejestr zwi?zany z przerwaniami */
    
    /* W??CZENIE ZEGARA PRZETWARZANIA */
    ADCCON1bits.ON = 1;
    
    while (ADCCON2bits.BGVRRDY==0) { }
    ADCANCONbits.ANEN1 = 1;
    while (ADCANCONbits.WKRDY1==0) { }
    ADCCON3bits.DIGEN1 = 1;
    

}   
