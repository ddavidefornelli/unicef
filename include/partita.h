#ifndef PARTITA_H
#define PARTITA_H

#include "tipiDiDato.h"

// Costanti per le posizioni dell'interfaccia
#define INPUT_RIGA_NUMERO_RIGA     13
#define INPUT_RIGA_NUMERO_COLONNA  16
#define INPUT_RIGA_NUMERO_VALORE   19
#define INPUT_RIGA_BASE            28
#define INPUT_COLONNA_BASE         68
#define ERRORE_MESSAGGIO_RIGA      22
#define ERRORE_MESSAGGIO_COLONNA   27

// Costanti logiche
#define FALSO 0
#define VERO  1

// Costanti per le dimensioni del Sudoku
#define DIMENSIONE_PICCOLA  4
#define DIMENSIONE_MEDIA    9
#define DIMENSIONE_GRANDE   16

// Costanti per il numero di celle da rimuovere per difficoltà
#define CELLE_RIMUOVERE_FACILE_4x4   6
#define CELLE_RIMUOVERE_FACILE_9x9   40
#define CELLE_RIMUOVERE_FACILE_16x16 150

// Dichiarazioni delle funzioni
void loopPartita(int codiceDifficolta, int codiceDimensione);
void stampareTitoloPartita(void);
void stampareSchermataDiVittoria(void);
void stampareInterfacciaInput(void);
void convertiDifficoltaEDimensione(int *puntatoreDifficolta, int *puntatoreDimensione);
void rimuovereNumeriDallaGriglia(Griglia *puntatoreGriglia, int dimensioneGriglia, int livelloDifficolta);
int verificareValiditaMossa(Griglia *puntatoreGriglia, int dimensioneGriglia, 
                           int rigaTarghet, int colonnaTarghet, int numeroInserito);
int riempireCompletamenteLaGriglia(Griglia *puntatoreGriglia, int dimensioneGriglia);
void generareSudoku(Partita *puntatorePartita, int dimensioneGriglia, int livelloDifficolta);
void stampareGrigliaPartita(Partita *puntatorePartita);
int raccogliereDatiRiga(Griglia *puntatoreGriglia, int *puntatoreInputRiga);
int raccogliereDatiColonna(Griglia *puntatoreGriglia, int *puntatoreInputColonna);
int raccogliereDatiValore(Griglia *puntatoreGriglia, int *puntatoreInputValore);
int controllareSeLaGrigliaECompleta(Griglia grigliaCorrente);

#endif
