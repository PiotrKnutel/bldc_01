/* Od Mateusza Kami?skiego mkam@linux.pl */

#include "uart.h"

#ifndef SYS_FREQ
#define SYS_FREQ 120000000  // 120 MHz
#endif

void UART_Init(){
    int pbClk;
    
    pbClk = SYS_FREQ / 2;

    U1MODE = 0;                         // Set UART 5 off prior to setting it up
    U1MODEbits.BRGH = 0;                // High Baud Rate Enable bit. 0 = Standard Speed Mode - 16x baud clock enables
    U1BRG = pbClk / (16 * 38400) - 1;   // Baud Rate (datasheet)
    U1STA = 0;                          // Disable the TX and RX pins, clear all flags
    U1STAbits.UTXEN = 1;                // UARTx transmitter is enabled
    U1STAbits.URXEN = 1;                // UARTx receiver is enabled
    U1MODEbits.PDSEL = 0;               // Parity and Data Selection bits. 0 = 8-bit data, no parity
    U1MODEbits.STSEL = 0;               // Stop Selection bit. 0 = 1 Stop bit
    U1MODEbits.ON = 1;                  // Turn on the UART 5 peripheral
}

void _mon_putc (char c){
   while (U1STAbits.UTXBF);
   U1TXREG = c;
}
