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
void avviarePartita(const char *nomePartita, int difficolta, int dimensione);
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
void stampareRigheGriglia(Griglia griglia, int dimensione, int numeroSottoquadrato);
void stampareRigaGriglia(Griglia griglia, int dimensione, int numeroSottoquadrato, int riga);

// Funzioni di utilità per dimensioni e difficoltà
void convertireDimensione(int *dimensione);
int calcolareSottoquadrato(int dimensione);
int calcolareCelleDaRimuovere(int difficolta);

// Funzioni di generazione e riempimento Sudoku
void generareSudoku(Partita *partita, int dimensione, int difficolta);
int riempireGriglia(Griglia *griglia, int dimensione);
void rimuovereNumeri(Griglia *griglia, int dimensione, int difficolta);
int trovareCellaVuota(Griglia *griglia, int dimensione, int *riga, int *colonna);

// Funzioni di validazione
int verificareValidita(Griglia *griglia, int dimensione, int riga, int colonna, int numero);
int verificareRiga(Griglia *griglia, int dimensione, int riga, int numero);
int verificareColonna(Griglia *griglia, int dimensione, int colonna, int numero);
int verificareSottoquadrato(Griglia *griglia, int dimensione, int riga, int colonna, int numero);

// Funzioni di input
int collezionareInput(Griglia *griglia, int *input, int rigaInput);
int collezionareRiga(Griglia *griglia, int *inputRiga);
int collezionareColonna(Griglia *griglia, int *inputColonna);
int collezionareValore(Griglia *griglia, int *inputValore);

// Funzioni di controllo stato partita
int controllareGrigliaPiena(Griglia griglia);
int controllareSalvataggio(Partita partita, int *input);

// Funzioni di salvataggio e caricamento

#endif // PARTITA_H



