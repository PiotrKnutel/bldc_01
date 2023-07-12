/*******************************************************************************
 * File: uart.h
 * 
 * Funkcja dotyczaca konfiguracji magistrali UART 1, udostepniona
 * do 'main.c'.
 ******************************************************************************/

#define RX_BUFF_LEN         5

/*
 * Inicjalizacja UART 1, do debugowania.
 */
void uart_init ();

/*
 * Redefinicja funkcji z 'stdio.h'. Umozliwia wysylanie tekstu przez UART1 za
 * pomoca funkcji 'printf()'.
 */
//void _mon_putc (char);


void uart_write_char(char c);

void uart_write_text(const char* tx_data);

unsigned int uart_read_char(void);
