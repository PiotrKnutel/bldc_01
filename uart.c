 /******************************************************************************
 * File: uart.c
 * 
 * Funkcje i zmienne do komunikacji przez UART 1, w celu debugowania.
 * Zawiera fragmenty od Mateusza Kaminskiego (mkam@linux.pl).
 ******************************************************************************/

#include "p32mk1024mcf064.h"
#include "uart.h"

///*
// * Inicjalizacja UART 1, do debugowania.
// */
//
//void uart_init()
//{
//    //int pbClk;
//    int SYS_FREQ = 120000000; // 120 MHz
//    
//    /* UART 1 */
//    //U1RXR = 0b1010;         // powiazanie UART1 RX z pinem G8 (RPG8)
//    //RPG6R = 0b00001;        // powiazanie UART1 TX z pinem G6 (U1TX)
//    
//    //pbClk = SYS_FREQ / 2;
//
//    U1MODE = 0;                         // Set UARTx off prior to setting it up
//    U1MODEbits.CLKSEL = 0b01;               // wybor zrodla zegara, 01 = SYSCLK;
//    U1MODEbits.BRGH = 0;                // High Baud Rate Enable bit. 0 = Standard Speed Mode - 16x baud clock enables
//    U1BRG = (SYS_FREQ / (16*115200))-1;   // Baud Rate (datasheet)
//    U1STA = 0;                          // Disable the TX and RX pins, clear all flags
//    U1STAbits.UTXEN = 1;                // UARTx transmitter is enabled
//    U1STAbits.URXEN = 1;                // UARTx receiver is enabled
//    U1MODEbits.PDSEL = 0;               // Parity and Data Selection bits. 0 = 8-bit data, no parity
//    U1MODEbits.STSEL = 0;               // Stop Selection bit. 0 = 1 Stop bit
//    //U1MODEbits.ON = 1;                  // Turn on the UARTx peripheral
//}
//
///*
// * Redefinicja funkcji z 'stdio.h'. Umozliwia wysylanie tekstu przez UART1 za
// * pomoca funkcji 'printf()'.
// */
//void _mon_putc (char c)
//{
//   while (U1STAbits.UTXBF);
//   U1TXREG = c;
//}

