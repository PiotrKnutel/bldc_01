Projekt jest czescia pracy magisterskiej.

Tytul pracy mgr:
"Sterowanie bezsensorycznym silnikiem BLDC"

Autor:
Piotr Knutel piknut@linux.pl 156476@stud.prz.edu.pl
Kolo Naukowe Elektronikow, Politechnika Rzeszowska im. I. Lukasiewicza, 2023

Promotor:
dr Miroslaw Sobaszek

Program dla mikrokontrolera:
PIC32MK1024MCF064

O projekcie: 
Program jest dedykowany dla sterownika trojfazowego, bezsensorowego silnika
bezszczotkowego. Sterownik zostal oparty o mikrokontroler PIC32MK.
Nazwa ukladu, widniejaca na PCB wyprodukowanej w 2023 roku, to 'BLDC driver'.
Autorzy PCB: Maciej Galda (2021), Piotr Knutel (2023).
Glowne funkcje programu: 'main()' oraz 'IntADCp7()'. Funkcja 'IntADCp7()' 
obsluguje przerwanie wywolywane po zakonczeniu konwersji ADC. Funkce znajduja
sie w plikach 'main.c' i 'IntADCp7.c'.

Lista plikow zrodlowych:
    main.c
    IntADCp7.c
    adc.c
    current_control.c
    
Lista plikow naglowkowych:
    p32mk1024mcf064.h
    pragma_config.h
    adc_main.h
    adc_int.h
    current_control.h
