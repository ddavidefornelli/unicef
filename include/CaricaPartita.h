#ifndef CARICAPARTITA_H 
#define CARICAPARTITA_H

#include "funzioni_utilita.h"
#include "tipiDiDato.h"

void stampareMenuCaricaPartita();
void stampareTitoloCaricaPartita();

void stampareZonaInput();
void salvarePartitaCorrente(Partita *partita);
int salvarePartita(Partita *partita, const char *percorso);
void salvareValoriGriglia(FILE *file, Partita *partita, int dimensione);
int caricarePartita(Partita *partita, const char *percorso);
int caricareValoriGriglia(FILE *file, Partita *partita, int dimensione);

#endif

