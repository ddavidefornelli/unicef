#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "homepage.h"

/*
stampaASinistra() -> funzione utilizzata per centrare a sinistra sul terminale;
stampaCentrato() -> funzione utilizzata per centrare sul terminale il menù di partenza;
mostraMenu() -> funzione utilizzata per stampare a video il menù di partenza;
collezionaInput() -> funzione utilizzata per collezionare l' input dell utente;
spostaCursore() -> funzione utilizzata per spostare la posizione del cursore nel terminale;
*/

typedef enum {
  LARGHEZZA_TERMINALE = 80,
  ALTEZZA_TERMINALE = 25
} terminale;

void spostaCursore(int x, int y)
{
  printf("\033[%d;%dH", x, y);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *  FUNZIONE: stampaCentrato(const char *testo)             *
 *  DESCRIZIONE: Allinea la stringa "testo"sul terminale    *
 *                                                          *
 *  ARGOMENTI:                                              *
 *  const char *testo: stringa da allineare                 *
 *                                                          *
 *  RITORNO: //                                             *
 *                                                          *
 *  MODIFICHE:                                              *
 *  2025/03/26 - Prima versione                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */

void stampaCentrato(const char *testo) 
{
  /* Definisco ed inizializzo le variabili */
  int spaziDaInserire = 0; /* contatore per il ciclo */
  int dimStringa; /* calcolo la lunghezza di dimStringa */
  int spazi; /* rappresenta le coordinate dove deve essere stampata "testo" */
  dimStringa = strlen(testo);
  spazi = (LARGHEZZA_TERMINALE - dimStringa) / 2;

  /* Se "testo" è più lunga della larghezza del terminale, evito spazi negativi */
  if (spazi < 0)
  {
    spazi = 0;
  }

  /* Stampo tanti spazi vuoti quanto basta per centrare "testo" */
  spaziDaInserire = 0;
  while(spaziDaInserire < spazi)
  {
    printf(" ");
    spaziDaInserire = spaziDaInserire + 1;
  }
  printf("%s\n", testo);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *  FUNZIONE: stampaCentrato(const char *testo)             *
 *  DESCRIZIONE: Allinea la stringa "testo" a sinistra      *
 *  nel terminale                                           *
 *                                                          *
 *  ARGOMENTI:                                              *
 *  const char *testo: stringa da allineare                 *
 *                                                          *
 *  RITORNO: //                                             *
 *                                                          *
 *  MODIFICHE:                                              *
 *  2025/03/27 - Prima versione                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */

void stampaASinistra(const char *testo) 
{
  /* Definisco ed inizializzo le variabili */
  int spaziDaInserire; /* contatore per il ciclo */
  int dimStringa; 
  int spazi;           /* rappresenta le coordinate dove deve essere stampata "testo" */

  /* calcolo la lunghezza di dimStringa */
  dimStringa = strlen(testo);

  /* Calcolo il numero di spazi da inserire per spostare il testo a sinistra (Sottraendo 5, la 
     stringa viene spostata verso sinistra di 5 posizioni rispetto al margine destro) */
  spazi = (LARGHEZZA_TERMINALE - dimStringa) - 5;

  /* Se "testo" è più lunga della larghezza del terminale, evito spazi negativi */
  if (spazi < 0)
  {
    spazi = 0;
  }

  /* Stampo tanti spazi vuoti quanto basta per spostare a sinistra il "testo" */
  spaziDaInserire = 0;
  while(spaziDaInserire < spazi)
  {
    printf(" ");
    spaziDaInserire = spaziDaInserire + 1;
  }

  /* Stampo effettivamente "testo" */
  printf("%s\n", testo);
}

void resetZonaInput(int posRiga, int posColonna){
    spostaCursore(posRiga, posColonna);
    printf(">> ");
    printf("%-10s", "");
    spostaCursore(posRiga, posColonna + 3);
}

void pulireBuffer(){
      while(getchar() != '\n'); // pulisce il buffer
}

void mostrareMessaggioErrore(const char *testo, int posRiga, int posColonna) {
      spostaCursore(posRiga, 0);
      printf("%-80s", "");
      spostaCursore(posRiga, posColonna);
      printf("%s %s %s",COLOR_RED, testo, COLOR_RESET);
}
