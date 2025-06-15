#ifndef PARTITA_H 
#define PARTITA_H


#include "tipiDiDato.h"

void loopPartita(const char *nomePartita, int inputDifficolta, int inputDimensione);
void loopPartitaContinuata(Partita *partita);
int salvaPartita(Partita *partita, const char *percorso);
int caricaPartita(Partita *partita, const char *percorso);
void stampareTitoloPartita();
void convertiDifficoltaEDimensione(int *inputDifficolta, int *inputDimensione);
void rimuovereNumeri(Griglia *griglia, int dimensione, int difficolta);
int verificaValidita(Griglia *griglia, int dimensione, int riga, int colonna, int numero);
int riempireGriglia(Griglia *griglia, int dimensione);
void generareSudoku(Partita *partita, int dimensione, int difficolta);
void stampareGrigliaPartita(Partita *partita);

int collezionaRiga(Griglia *griglia, int *inputRiga);
int collezionaColonna(Griglia *griglia, int *inputColonna);
int collezionaValore(Griglia *griglia, int *inputValore);

int controllareGrigliaPiena(Griglia griglia); 
void stampareAiutiInput();
void stampareVittoria();
#endif



