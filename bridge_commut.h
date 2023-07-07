/*******************************************************************************
 * File: bridge_commut.h
 * 
 * Funkcja dotyczaca sterowania mostkiem 3-fazowym MOSFET, udostepniona
 * do 'commutation.c'.
 ******************************************************************************/

/* Stan wysokiej impedancji wszyskich trzech faz mostka MOSFET.
 * Mozliwosc uzycia jako argumentu funkcji 'bridge_set_state()'. */
#define BRIDGE_IDLE_STATE_HIGH_Z    0

/*
 * Ustawianie MOSFETów mostka (stanów komutacji) wedlug podanego nr stanu.
 * INPUT:
 *   state          - Stan zalaczenia tranzystorów. Dozwolone wartosci 0..6.
 *                    0 to stan jalowy, wszystkie MOSFETy sa wylaczone.
 */
void bridge_set_state(int state);
