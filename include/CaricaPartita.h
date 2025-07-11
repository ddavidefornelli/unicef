#ifndef CARICAPARTITA_H 
#define CARICAPARTITA_H

#include "../include/funzioniUtilita.h"
#include "../include/tipiDiDato.h"

void avviareMenuCaricaPartita();
void stampareTitoloCaricaPartita();

void salvarePartitaCorrente(Partita *partita);
void salvarePartita(Partita *partita, const char *percorso);
void salvareValoriGriglia(FILE *file, Partita *partita, int dimensione);
void caricarePartita(Partita *partita, const char *percorso);
void caricareValoriGriglia(FILE *file, Partita *partita, int dimensione);
void liberarePartite(char *nomiPartite[], int partiteDaLiberare);
const char *trovareFile(char *nomiPartite[], int numeroPartite, const char *input);
void estrapolareNomeDaFile(const char *nomeFile, char *nome);

#endif

