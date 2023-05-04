/* File: bridge.c
 * 
 * Funkcje i zmienne do sterowania mostkiem trójfazowym silnika.
 */

#include "p32mk1024mcf064.h"
#include "bridge_main.h"
#include "bridge_int.h"

/* Definicje rejestrów powizanych ze stanami logicznymi pinów sterujacych
 * moskiem 3-fazowym silnika. */
#define PIN_U_PMOS      LATFbits.LATF0
#define PIN_V_PMOS      LATBbits.LATB10
#define PIN_W_PMOS      LATBbits.LATB11
#define PIN_U_NMOS      LATCbits.LATC8
#define PIN_V_NMOS      LATCbits.LATC6
#define PIN_W_NMOS      LATCbits.LATC7

/*
 * Wylaczenie górnych i dolnych MOSFETów wszystkich trzech faz mostka.
 * Stan jalowy silnika.
 */
void bridge_idle_state()
{
    /* Górne MOSFET-P, pomiedzy Vbldc i wyjsciami na silnik. */
    PIN_U_PMOS = 1; 
    PIN_V_PMOS = 1;
    PIN_W_PMOS = 1;

    /* Dolne MOSFET-N, pomiedzy GND i wyjsciami na silnik. */
    PIN_U_NMOS = 0;
    PIN_V_NMOS = 0;
    PIN_W_NMOS = 0;
}

/*
 * Ustawianie MOSFETów mostka (stanów komutacji) wedlug podanego nr stanu.
 * Dla MOSFETów typu P stan '1' wyl. tranzystor, a '0' wl.
 * Dla MOSFETów typu N jest odwrotnie. 
 */
void bridge_set_state(int state) {
    switch (state) {
        case 0:
            PIN_U_PMOS = 1; 
            PIN_V_PMOS = 1;
            PIN_W_PMOS = 1;
            PIN_U_NMOS = 0;
            PIN_V_NMOS = 0;
            PIN_W_NMOS = 0;
            break;
        case 1:
            PIN_U_PMOS = 0; 
            PIN_V_PMOS = 1;
            PIN_W_PMOS = 1;
            PIN_U_NMOS = 0;
            PIN_V_NMOS = 1;
            PIN_W_NMOS = 0;
            break;
        case 2:
            PIN_U_PMOS = 0; 
            PIN_V_PMOS = 1;
            PIN_W_PMOS = 1;
            PIN_U_NMOS = 0;
            PIN_V_NMOS = 0;
            PIN_W_NMOS = 1;
            break;
        case 3:
            PIN_U_PMOS = 1; 
            PIN_V_PMOS = 0;
            PIN_W_PMOS = 1;
            PIN_U_NMOS = 0;
            PIN_V_NMOS = 0;
            PIN_W_NMOS = 1;
            break;
        case 4:
            PIN_U_PMOS = 1; 
            PIN_V_PMOS = 0;
            PIN_W_PMOS = 1;
            PIN_U_NMOS = 1;
            PIN_V_NMOS = 0;
            PIN_W_NMOS = 0;
            break;
        case 5:
            PIN_U_PMOS = 1; 
            PIN_V_PMOS = 1;
            PIN_W_PMOS = 0;
            PIN_U_NMOS = 1;
            PIN_V_NMOS = 0;
            PIN_W_NMOS = 0;
            break;
        case 6:
            PIN_U_PMOS = 1; 
            PIN_V_PMOS = 1;
            PIN_W_PMOS = 0;
            PIN_U_NMOS = 0;
            PIN_V_NMOS = 1;
            PIN_W_NMOS = 0;
            break;
        default:
            /* Stan jalowy */
            PIN_U_PMOS = 1; 
            PIN_V_PMOS = 1;
            PIN_W_PMOS = 1;
            PIN_U_NMOS = 0;
            PIN_V_NMOS = 0;
            PIN_W_NMOS = 0;
            break;         
    }
}
