/* Sterowanie mostkiem trójfazowym. */

#include "bridge.h"

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
