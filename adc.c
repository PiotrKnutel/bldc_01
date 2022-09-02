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
    ADC2CFG = DEVADC2;
    
    /* Konfiguracja ADCCON 1 */
    ADCCON1 = 0;                    // bez funkcji z tego rejestru, w tym bit ON=1 (ADC wy?)
    
    ADCCON1bits.AICPMPEN = 0;       // bo Vdd >= 2.5V
    CFGCONbits.IOANCPEN = 0;        // bo Vdd >= 2.5V
    
    /* Konfiguracja ADCCON2 */
    ADCCON2 = 0;                    // nie potrzenbna w przypadku u?ywania tylko wej?? klasy 1 (dedykowanych ADC)
    
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
    //ADC1TIMEbits.SELRES = 3;        // rozdzielczosc 3=12 bitów
    //ADC1TIMEbits.DMAEN = 0;         // DMA 0=wy?. (tego nie rozpozanawa? kompliator)
    ADC1TIMEbits.ADCDIV = 1;        // 1=Tad=2*Tq, dzielnik taktowania ADC
    ADC1TIMEbits.SAMC = 5;          // czas próbkowania, 0x3FF=1025*Tad, 5=5*Tad
    
    /* Ustawienie pinów jako wej?? do konkretnych ADC */
    ADCTRGMODEbits.SH1ALT = 0;      // jesli 0 to AN1 jest wej ADC 1 (VBAT_ADC), te bity umo?liwiaj? po??czenie innego pinu z ADC1 
    ADCTRGMODEbits.SH1ALT = 0;      // AN2 (pin B0) to wej ADC 2 (Current_SEnse_ADC)
    
    /* Wybór trybu wej ADC */
    ADCIMCON1bits.DIFF1 = 0;        // je?li 0 to AN1 u?ywa trybu Single-ended
    ADCIMCON1bits.SIGN1 = 0;        // je?li 0 to AN1 u?ywa trybu unsigned data
    ADCIMCON1bits.DIFF2 = 0;
    ADCIMCON1bits.SIGN2 = 0;
    
    /* Konfiguracja ADCGIRQENx */
    ADCGIRQEN1 = 0;                 // 0 = wyl. przerwania gdy gotowe przetwarzane danych
    ADCGIRQEN2 = 0;
    
    /* Konfiguracja ADCCSSx */
    ADCCSS1 = 0;                    // 0 bo nie u?ywane skanowanie, je?li u?ywane to trzeba wybra? wej?cia 
    ADCCSS2 = 0;            

    /* Konfiguracja ADCCMPCONx */
    ADCCMPCON1 = 0;                 // 0 = nie u?ywane cyfrowe komparatory   
    ADCCMPCON2 = 0; 
    ADCCMPCON3 = 0; 
    ADCCMPCON4 = 0;
    
    /* Konfiguracja ADCFLTRx */
    ADCFLTR1 = 0;                   // 0 = nie u?ywane filtrowanie poprzez nadpróbowanie
    ADCFLTR2 = 0;
    ADCFLTR3 = 0;
    ADCFLTR4 = 0;
    
    /* Ustawienie zródla wyzwalania (trigger) */
    ADCTRGSNSbits.LVL1 = 0;         // 0 = ADC1 wyzwalany zboczem
    ADCTRGSNSbits.LVL2 = 0;
    ADCTRG1bits.TRGSRC1 = 1;        // wybór ?ród?a wyzwalania (trigger) dla AN1, 
        /* 0=brak wyzwalania, 0b10000=koniec okresu OC1, 1=zbocze z software'u */
        /* dla ADC Klasy 1 trigger powoduje przerwanie próbkowania i rozpocz?cie konwersji */
    ADCTRG1bits.TRGSRC2 = 1;
    
    /* Wczesne przerwania */
    ADCEIEN1 = 0;                   // 0 = brak wczesnych przertwa?
    ADCEIEN2 = 0;
    
    /* W??CZENIE ADC */
    ADCCON1bits.ON = 1;
    
    /* Czekanie na stabilno?? napi?cia ref. */
    while (!ADCCON2bits.BGVRRDY);
    while (ADCCON2bits.REFFLT);
    
    /* Wl?czenie taktownia obwodów analogowych */
    ADCANCONbits.ANEN1 = 1;
    ADCANCONbits.ANEN2 = 1;
    
    /* Czekanie na gotowo?? ADC */
    while (!ADCANCONbits.WKRDY1);
    while (!ADCANCONbits.WKRDY2);
    
    /* Wl?czenie modu?u ADC */
    ADCCON3bits.DIGEN1 = 1;
    ADCCON3bits.DIGEN2 = 1;
}
    
void ADC_meas(unsigned int *out_result_Vbat, unsigned int *out_result_Current) {
    
    /* Wyzwolenie konwersji */
    ADCCON3bits.GSWTRG = 1;
    
    /* ADC 1 (Vbat) */
    while (ADCDSTAT1bits.ARDY1 == 0); // Czekanie, az konwersja bedzie ukonczona
    (*out_result_Vbat) = ADCDATA1;       // pobranie wyniku
    
    /* ADC 2 (Current_Sense) */
    while (ADCDSTAT1bits.ARDY2 == 0);
    (*out_result_Current) = ADCDATA2; 
}   
