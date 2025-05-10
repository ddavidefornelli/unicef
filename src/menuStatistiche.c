#include "interfaccia_util.h"
#include "homepage.h"
#include "menuStatistiche.h"
#include <stdio.h>
#include <stdlib.h>

#define INPUT_RIGA 23
#define INPUT_COLONNA 30

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

void stampareTitoloStatistiche(){
  stampareCentrato("            _       _   _     _   _     _              ");
  stampareCentrato(" ___    ___| |_ ___| |_|_|___| |_|_|___| |_ ___    ___ ");
  stampareCentrato("|___|  |_ -|  _| .'|  _| |_ -|  _| |  _|   | -_|  |___|");
  stampareCentrato("       |___|_| |__,|_| |_|___|_| |_|___|_|_|___|       ");
  printf("\n\n\n");
}

void stampareMenuStatistiche(){
  int input;
  pulireSchermo();
  stampareTitoloStatistiche();
  caricaStatistiche(&giocatore, "database/statisticheGiocatore.txt");
  stampareStatisticheGiocatore(&giocatore);
  tornareHomepage(&input, INPUT_RIGA, INPUT_COLONNA);
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

void stampareStatisticheGiocatore(statisticheGiocatore *giocatore) {
    printf("PARTITE_GIOCATE_TOTALI: %d\n", leggerePartiteGiocateTotali(giocatore));
    printf("   - Facile           : %d\n", leggerePartiteGiocateFacile(giocatore));
    printf("   - Media            : %d\n", leggerePartiteGiocateMedia(giocatore));
    printf("   - Difficile        : %d\n", leggerePartiteGiocateDifficile(giocatore));
    printf("\n");
    printf("PARTITE VINTE TOTALI: %d\n", leggerePartiteVinteTotali(giocatore));
    printf("   - Facile           : %d\n", leggerePartiteVinteFacile(giocatore));
    printf("   - Media            : %d\n", leggerePartiteVinteMedia (giocatore));
    printf("   - Difficile        : %d\n", leggerePartiteVinteDifficile(giocatore));
    printf("\n");
    printf("W/L Ratio             : %.2f", calcolareWLRatio(giocatore));
}

float calcolareWLRatio(statisticheGiocatore *giocatore){
  float wlRatio;
  int giocate;
  int vinte;
  int perse;

  giocate = leggerePartiteGiocateTotali(giocatore);
  vinte = leggerePartiteVinteTotali(giocatore);
  perse = giocate - vinte;

  if(perse == 0){
    wlRatio = vinte;
  }
  else {
  wlRatio = (float)vinte / (float)perse;
  }

  return wlRatio;
}

void aggiornareDatabaseStatisticheGiocatore(const char *nomeFile, statisticheGiocatore *giocatore){
  FILE *file = fopen(nomeFile, "w");

    fprintf(file, "Partite_Giocate_Totali: %d\n", giocatore->partiteGiocateTotali);
    fprintf(file, "Partite_Giocate_Facile: %d\n", giocatore->partiteGiocateFacile);
    fprintf(file, "Partite_Giocate_Media: %d\n", giocatore->partiteGiocateMedia);
    fprintf(file, "Partite_Giocate_Difficile: %d\n", giocatore->partiteGiocateDifficile);
    fprintf(file, "Partite_Vinte_Totali: %d\n", giocatore->partiteVinteTotali);
    fprintf(file, "Partite_Vinte_Facile: %d\n", giocatore->partiteVinteFacile);
    fprintf(file, "Partite_Vinte_Media: %d\n", giocatore->partiteVinteMedia);
    fprintf(file, "Partite_Vinte_Difficile: %d\n", giocatore->partiteVinteDifficile);

  fclose(file);
}
