 /******************************************************************************
 * File: uart.c
 * 
 * Funkcje i zmienne do komunikacji przez UART 1, w celu debugowania.
 * Zawiera fragmenty od Mateusza Kaminskiego (mkam@linux.pl).
 ******************************************************************************/

#include "p32mk1024mcf064.h"
#include "uart.h"

const unsigned int MAX_TX_DATA_LENGTH = 9;  // MAX= 9, sprawdz. eksperymentalnie 
unsigned int j;
volatile char rx_buff[RX_BUFF_LEN];
volatile int rx_buff_counter;
volatile int flag_uart_rx;

void __attribute__((vector(_UART1_RX_VECTOR), interrupt(IPL6SRS), nomips16)) 
UART1_RX_interrupt ()
{
    IFS1bits.U1RXIF = 0;
    IFS1bits.U1TXIF = 0;
    //uart5_write_text("a");
    while (U1STAbits.URXDA)
    {
        //uart5_write_text("1");
        if (rx_buff_counter > RX_BUFF_LEN-1)
            rx_buff_counter = 0;
        rx_buff[rx_buff_counter] = U1RXREG;
        rx_buff_counter++;
    }
    flag_uart_rx = 1;
    IFS1bits.U1RXIF = 0;
    IFS1bits.U1TXIF = 0;
}

/*
 * Inicjalizacja UART 1, do debugowania.
 */

void uart_init()
{
    int SYS_FREQ = 120000000; // 120 MHz
    
    rx_buff_counter = 0;
    flag_uart_rx = 0;
    
    //U1RXR = 0b1010;         // powiazanie UART1 RX z pinem G8 (RPG8)
    RPG6R = 0b00001;        // powiazanie UART1 TX z pinem G6 (U1TX)
    
    U1MODE = 0;                         // Set UARTx off prior to setting it up
    U1MODEbits.CLKSEL = 0b00;           // wybor zrodla zegara, 01 = SYSCLK;
    U1MODEbits.BRGH = 1;                // High Baud Rate Enable bit. 0 = Standard Speed Mode - 16x baud clock enables
    U1BRG = (60000000 / (4*115200))-1; // Baud Rate (datasheet)
    U1STA = 0;                          // Disable the TX and RX pins, clear all flags
    U1STAbits.UTXEN = 1;                // UARTx transmitter is enabled
    U1STAbits.URXEN = 0;                // UARTx receiver is enabled
    U1MODEbits.PDSEL = 0;               // Parity and Data Selection bits. 0 = 8-bit data, no parity
    U1MODEbits.STSEL = 0;               // Stop Selection bit. 0 = 1 Stop bit
    
    /* Przerwania od odbioru */
    IEC1bits.U1RXIE = 0;
    IPC9bits.U1RXIP = 6;
    IPC9bits.U1RXIS = 1;
    
    U1STAbits.URXISEL = 0b00; // przerwanie gdy odebrano co najmnie 1B
    
    IFS1bits.U1RXIF = 0;
    IEC1bits.U1RXIE = 0;
    
    U1MODEbits.ON = 1;                  // Turn on the UARTx peripheral
}

/*
 * Redefinicja funkcji z 'stdio.h'. Umozliwia wysylanie tekstu przez UART1 za
 * pomoca funkcji 'printf()'.
 */
//void _mon_putc (char c)
//{
//   while (U1STAbits.UTXBF);
//   U1TXREG = c;
//}

void uart_write_char(char c)
{
   while (U1STAbits.UTXBF);
   U1TXREG = c;
}

void uart_write_text(const char *tx_data)
{
    int j = 0;
    while (tx_data[j] != '\0')
    {
        if (j > MAX_TX_DATA_LENGTH - 1)
        {
            break;
        }
        uart_write_char(tx_data[j]);
        j++;
    }
}


//unsigned int uart_read_char(void) {
//    while (!U1STAbits.URXDA); //wait rx data available
//    
//    if(U1STAbits.OERR)
//    {
//        U1STAbits.OERR = 0; //clear overrun error manually
//    }
//    
//    return U1RXREG;
//}