/*******************************************************************************
 * File: bridge_int.h
 * 
 * Funkcja dotyczaca sterowania mostkiem 3-fazowym MOSFET, udostepniona
 * do 'IntADCp7.c'.
 ******************************************************************************/

/*
 * Ustawianie MOSFETów mostka (stanów komutacji) wedlug podanego nr stanu.
 * INPUT:
 *   state          - Stan zalaczenia tranzystorów. Dozwolone wartosci 0..6.
 *                    0 to stan jalowy, wszystkie MOSFETy sa wylaczone.
 */
void bridge_set_state(int state);
