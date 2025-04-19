#include "interfaccia_util.h"
#include "menustatistiche.h"
#include <stdio.h>
#include <stdlib.h>


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


statisticheGiocatore giocatore;

void stampareMenuStatistiche(){
  system("clear || cls");
  stampaCentrato("            _       _   _     _   _     _              ");
  stampaCentrato(" ___    ___| |_ ___| |_|_|___| |_|_|___| |_ ___    ___ ");
  stampaCentrato("|___|  |_ -|  _| .'|  _| |_ -|  _| |  _|   | -_|  |___|");
  stampaCentrato("       |___|_| |__,|_| |_|___|_| |_|___|_|_|___|       ");
  
  printf("\n\n\n");
  caricaStatistiche(&giocatore, "database/statisticheGiocatore.txt");
  stampaStatisticheGiocatore(&giocatore);
}

void caricaStatistiche(statisticheGiocatore *giocatore, const char *filename) {
    FILE *file = fopen(filename, "r");

    fscanf(file, "Partite_Giocate_Totali: %d\n", &giocatore->partiteGiocateTotali);
    fscanf(file, "Partite_Giocate_Facile: %d\n", &giocatore->partiteGiocateFacile);
    fscanf(file, "Partite_Giocate_Media: %d\n", &giocatore->partiteGiocateMedia);
    fscanf(file, "Partite_Giocate_Difficile: %d\n", &giocatore->partiteGiocateDifficile);
    fscanf(file, "Partite_Vinte_Totali: %d\n", &giocatore->partiteVinteTotali);
    fscanf(file, "Partite_Vinte_Facile: %d\n", &giocatore->partiteVinteFacile);
    fscanf(file, "Partite_Vinte_Media: %d\n", &giocatore->partiteVinteMedia);
    fscanf(file, "Partite_Vinte_Difficile: %d\n", &giocatore->partiteVinteDifficile);

    fclose(file);
}

void stampaStatisticheGiocatore(statisticheGiocatore *giocatore) {
    printf("PARTITE GIOCATE TOTALI: %d\n", leggerePartiteGiocateTotali(giocatore));
    printf("   - Facile           : %d\n", leggerePartiteGiocateFacile(giocatore));
    printf("   - Media            : %d\n", leggerePartiteGiocateMedia(giocatore));
    printf("   - Difficile        : %d\n", leggerePartiteGiocateDifficile(giocatore));
    printf("\n");
    printf("PARTITE VINTE TOTALI: %d\n", leggerePartiteVinteTotali(giocatore));
    printf("   - Facile           : %d\n", leggerePartiteVinteFacile(giocatore));
    printf("   - Media            : %d\n", leggerePartiteVinteMedia (giocatore));
    printf("   - Difficile        : %d\n", leggerePartiteVinteDifficile(giocatore));
}

