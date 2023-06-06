/*******************************************************************************
 * File: uart.h
 * 
 * Funkcja dotyczaca konfiguracji magistrali UART 1, udostepniona
 * do 'main.c'.
 ******************************************************************************/

/*
 * Inicjalizacja UART 1, do debugowania.
 */
void uart_init ();

/*
 * Redefinicja funkcji z 'stdio.h'. Umozliwia wysylanie tekstu przez UART1 za
 * pomoca funkcji 'printf()'.
 */
void _mon_putc (char);
