#ifndef PARTITA_H
#define PARTITA_H

#include <stdio.h>
#include "tipiDiDato.h"

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
void loopPartita(const char *nomePartita, int difficolta, int dimensione);
void loopPartitaContinuata(Partita *partita);

// Funzioni di visualizzazione
void mostraSchermo(int dimensione);
void stampareTitoloPartita(void);
void stampareVittoria(void);
void stampareAiutiInput(void);
void disegnareCornice(void);

// Funzioni di gestione griglia e stampa
void stampareGrigliaPartita(Partita *partita);
void stampareIntestazioneColonne(int dimensione, int numeroSottoquadrato);
void stampareLineaOrizzontale(int dimensione, int numeroSottoquadrato);
void stampareRigheGriglia(Griglia griglia, int dimensione, int numeroSottoquadrato);
void stampareRigaGriglia(Griglia griglia, int dimensione, int numeroSottoquadrato, int riga);

// Funzioni di utilità per dimensioni e difficoltà
void convertiDifficoltaEDimensione(int *difficolta, int *dimensione);
int calcolaSottoquadrato(int dimensione);
int calcolaCelleRimuovere(int difficolta);

// Funzioni di generazione e riempimento Sudoku
void generareSudoku(Partita *partita, int dimensione, int difficolta);
int riempireGriglia(Griglia *griglia, int dimensione);
void rimuovereNumeri(Griglia *griglia, int dimensione, int difficolta);
int trovaCellaVuota(Griglia *griglia, int dimensione, int *riga, int *colonna);

// Funzioni di validazione
int verificaValidita(Griglia *griglia, int dimensione, int riga, int colonna, int numero);
int verificaRiga(Griglia *griglia, int dimensione, int riga, int numero);
int verificaColonna(Griglia *griglia, int dimensione, int colonna, int numero);
int verificaSottoquadrato(Griglia *griglia, int dimensione, int riga, int colonna, int numero);

// Funzioni di input
int collezionaInput(Griglia *griglia, int *input, int rigaInput);
int collezionaRiga(Griglia *griglia, int *inputRiga);
int collezionaColonna(Griglia *griglia, int *inputColonna);
int collezionaValore(Griglia *griglia, int *inputValore);

// Funzioni di controllo stato partita
int controllareGrigliaPiena(Griglia griglia);

// Funzioni di salvataggio e caricamento
void salvaPartitaCorrente(Partita *partita);
int salvaPartita(Partita *partita, const char *percorso);
void salvaValoriGriglia(FILE *file, Partita *partita, int dimensione);
int caricaPartita(Partita *partita, const char *percorso);
int caricaValoriGriglia(FILE *file, Partita *partita, int dimensione);

#endif // PARTITA_H



