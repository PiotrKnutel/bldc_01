/*******************************************************************************
 * File: interrupt_on.c
 * 
 * Funkcja do wlaczenia obslugi przerwan przez PIC32MK.
 ******************************************************************************/

#include "interrupt_on.h"
#include "p32mk1024mcf064.h"

/*
 * Wlaczenie obslugi przerwan. 
 */
void interrupt_on()
{
    INTCONbits.MVEC= 1;
    PRISS= 0x76543211;
    asm volatile("ei");
}