#ifndef MENUSTATISTICHE_H 
#define MENUSTATISTICHE_H

#include "interfaccia_util.h"

typedef struct{
  int partiteGiocateTotali;
  int partiteGiocateFacile;
  int partiteGiocateMedia;
  int partiteGiocateDifficile;
  int partiteVinteTotali;
  int partiteVinteFacile;
  int partiteVinteMedia;
  int partiteVinteDifficile;
} statisticheGiocatore;

void stampareMenuStatistiche();

// Lettura statistiche
int leggerePartiteGiocateTotali(statisticheGiocatore *giocatore);
int leggerePartiteGiocateFacile(statisticheGiocatore *giocatore);
int leggerePartiteGiocateMedia(statisticheGiocatore *giocatore);
int leggerePartiteGiocateDifficile(statisticheGiocatore *giocatore);

int leggerePartiteVinteTotali(statisticheGiocatore *giocatore);
int leggerePartiteVinteFacile(statisticheGiocatore *giocatore);
int leggerePartiteVinteMedia(statisticheGiocatore *giocatore);
int leggerePartiteVinteDifficile(statisticheGiocatore *giocatore);

// Incremento statistiche
void incrementarePartiteGiocateTotali(statisticheGiocatore *giocatore);
void incrementarePartiteGiocateFacile(statisticheGiocatore *giocatore);
void incrementarePartiteGiocateMedia(statisticheGiocatore *giocatore);
void incrementarePartiteGiocateDifficile(statisticheGiocatore *giocatore);

void incrementarePartiteVinteTotali(statisticheGiocatore *giocatore);
void incrementarePartiteVinteFacile(statisticheGiocatore *giocatore);
void incrementarePartiteVinteMedia(statisticheGiocatore *giocatore);
void incrementarePartiteVinteDifficile(statisticheGiocatore *giocatore);

// Gestione file statistiche
void scriviStatisticheGiocatore(statisticheGiocatore *giocatore, const char *nomeFile);
void leggiStatisticheGiocatore(statisticheGiocatore *giocatore, const char *nomeFile);

// Stampa statistiche
void stampaStatisticheGiocatore(statisticheGiocatore *giocatore);
void caricaStatistiche(statisticheGiocatore *giocatore, const char *filename);

#endif
