/******************************************************************************* 
 * File: pragma_config.h
 * 
 * Plik zawiera dyrektywy #pragma wykorzystane do konfiguracji mikrokontrolera
 * PIC32MK1024MCF064, w tym do konfiguracji taktowania rdzenia i magistral.
 *   - Zrodlo taktowania: zewnetrzny generator POSC 10 MHz
 *   - Taktowanie magistarli SYSCLK: 120 MHz
 *   - Taktowanie magistarli PBCLKx: 60 MHz
 ******************************************************************************/

#pragma config ICESEL = ICS_PGx1

// Device Config Bits in  DEVCFG1:	
#pragma config FNOSC =      SPLL
#pragma config FSOSCEN =	ON
#pragma config POSCMOD =	EC
#pragma config OSCIOFNC =	OFF
	
// Device Config Bits in  DEVCFG2:	
#pragma config FPLLICLK =	PLL_POSC
#pragma config FPLLIDIV =	DIV_1
#pragma config FPLLMULT =	MUL_48
#pragma config FPLLODIV =	DIV_4
#pragma config FPLLRNG =	RANGE_5_10_MHZ
#pragma config UPLLEN =     OFF
//#pragma config UPLLFSEL =	FREQ_12MHZ

#pragma config FDMTEN = OFF
#pragma config WDTSPGM = STOP
#pragma config DMTCNT = DMT31
//#pragma config FSOSCEN = OFF
//#pragma config FUSBIDIO = OFF
//#pragma config FMIIEN = OFF //RMII OFF
//#pragma config IOL1WAY = OFF
//#pragma config FCKSM = CSECME
#pragma config JTAGEN = OFF
