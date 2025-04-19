#include "interfaccia_util.h"
#include "menustatistiche.h"
#include <stdio.h>
#include <stdlib.h>

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

int leggerePartiteGiocateTotali(statisticheGiocatore *giocatore){
  return giocatore->partiteGiocateTotali;
}

int leggerePartiteGiocateFacile(statisticheGiocatore *giocatore){
  return giocatore->partiteGiocateFacile;
}

int leggerePartiteGiocateMedia(statisticheGiocatore *giocatore){
  return giocatore->partiteGiocateMedia;
}

int leggerePartiteGiocateDifficile(statisticheGiocatore *giocatore){
  return giocatore->partiteGiocateDifficile;
}

void incrementarePartiteGiocateTotali(statisticheGiocatore *giocatore){
  giocatore->partiteGiocateTotali = giocatore->partiteGiocateTotali + 1;
}

void incrementarePartiteGiocateFacile(statisticheGiocatore *giocatore){
  giocatore->partiteGiocateFacile = giocatore->partiteGiocateFacile + 1;
}
void incrementarePartiteGiocateMedia(statisticheGiocatore *giocatore){
  giocatore->partiteGiocateMedia = giocatore->partiteGiocateMedia + 1;
}
void incrementarePartiteGiocateDifficile(statisticheGiocatore *giocatore){
  giocatore->partiteGiocateDifficile = giocatore->partiteGiocateDifficile + 1;
}

int leggerePartiteVinteTotali(statisticheGiocatore *giocatore){
  return giocatore->partiteVinteTotali;
}

int leggerePartiteVinteFacile(statisticheGiocatore *giocatore){
  return giocatore->partiteVinteFacile;
}

int leggerePartiteVinteMedia(statisticheGiocatore *giocatore){
  return giocatore->partiteVinteMedia;
}

int leggerePartiteVinteDifficile(statisticheGiocatore *giocatore){
  return giocatore->partiteVinteDifficile;
}

void incrementarePartiteVinteTotali(statisticheGiocatore *giocatore){
  giocatore->partiteVinteTotali = giocatore->partiteVinteTotali + 1;
}

void incrementarePartiteVinteFacile(statisticheGiocatore *giocatore){
  giocatore->partiteVinteFacile = giocatore->partiteVinteFacile + 1;
}
void incrementarePartiteVinteMedia(statisticheGiocatore *giocatore){
  giocatore->partiteVinteMedia = giocatore->partiteVinteMedia + 1;
}
void incrementarePartiteVinteDifficile(statisticheGiocatore *giocatore){
  giocatore->partiteVinteDifficile = giocatore->partiteVinteDifficile + 1;
}

void stampareMenuStatistiche(){
  system("clear || cls");
  stampaCentrato("            _       _   _     _   _     _              ");
  stampaCentrato(" ___    ___| |_ ___| |_|_|___| |_|_|___| |_ ___    ___ ");
  stampaCentrato("|___|  |_ -|  _| .'|  _| |_ -|  _| |  _|   | -_|  |___|");
  stampaCentrato("       |___|_| |__,|_| |_|___|_| |_|___|_|_|___|       ");
}

