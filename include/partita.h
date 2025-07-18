#ifndef PARTITA_H
#define PARTITA_H

#include <stdio.h>
#include "../include/tipiDiDato.h"
 
// Costanti
#define RIGA_INPUT_RIGA 13
#define RIGA_INPUT_COLONNA 16
#define RIGA_INPUT_VALORE 19
#define RIGA_INPUT 28
#define COLONNA_INPUT 67
#define FALSO 0
#define VERO 1
#define RIGA_ERRORE 22
#define COLONNA_ERRORE 27

// Funzioni principali del gioco
void avviarePartita(const char *nomePartita, Impostazioni impostazioni);
void avviarePartitaContinuata(Partita *partita);

// Funzioni di visualizzazione
void mostraSchermo(int dimensione);
void stampareTitoloPartita(void);
void stampareVittoria(void);
void stampareTabellaInput(void);
void disegnareCornice(void);

// Funzioni di gestione griglia e stampa
void stampareGrigliaPartita(Partita *partita);
void stampareIntestazioneColonne(int dimensione, int numeroSottoquadrato);
void stampareLineaOrizzontale(int dimensione, int numeroSottoquadrato);
void stampareRigheGriglia(Griglia griglia);
void stampareRigaGriglia(Griglia griglia, int riga);

// Funzioni di utilità per dimensioni e difficoltà
void convertireDimensione(int *dimensione);
int calcolareSottoquadrato(int dimensione);
int calcolareCelleDaRimuovere(Impostazioni *impostazioni);

// Funzioni di generazione e riempimento Sudoku
void generareSudoku(Partita *partita);
int riempireGriglia(Griglia *griglia);
void rimuovereNumeri(Griglia *griglia, Impostazioni *impostazioni);
int trovareCellaVuota(Griglia *griglia);

// Funzioni di validazione
int verificareValidita(Griglia *griglia, int riga, int colonna, int numero);
int verificareRiga(Griglia *griglia, int riga, int numero);
int verificareColonna(Griglia *griglia, int colonna, int numero);
int verificareSottoquadrato(Griglia *griglia, int riga, int colonna, int numero);

// Funzioni di input
int collezionareInput(Griglia *griglia, int *input, int rigaTerminale);

// Funzioni di controllo stato partita
int controllareGrigliaPiena(Griglia griglia);
int controllareSalvataggio(Partita partita, int *input);

#endif // PARTITA_H



