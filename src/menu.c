#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "homepage.h"

typedef enum {
  LARGHEZZA_TERMINALE = 120,
  ALTEZZA_TERMINALE = 80
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


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *  FUNZIONE: stampareMenuPrincipale()                                  *
 *  DESCRIZIONE: Mostra il menù iniziale del gioco          *
 *                                                          *
 *  ARGOMENTI: //                                           *
 *                                                          *
 *  RITORNO: //                                             *
 *                                                          *
 *  MODIFICHE:                                              *
 *  2025/03/26 - Prima versione                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */

void stampareMenuPrincipale() 
{
  system("clear || cls");
  printf("\n");
  stampaCentrato(" __           _       _           ");
  stampaCentrato("/ _\\_   _  __| | ___ | | ___   _  ");
  stampaCentrato("\\ \\| | | |/ _` |/ _ \\| |/ / | | | ");
  stampaCentrato("_\\ \\ |_| | (_| | (_) |   <| |_| | ");
  stampaCentrato("\\__/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_| ");
  printf("\n\n");
  spostaCursore(9, 56);
  printf("- MENU -");
  spostaCursore(11, 50);
  printf("[1] Nuova Partita");
  spostaCursore(12, 50);
  printf("[2] Carica Partita");
  spostaCursore(13, 50);
  printf("[3] Statistiche");
  spostaCursore(14, 50);
  printf("\033[31m[4] Esci \033[0m");
  spostaCursore(16, 48);
  printf("Inserisci una scelta (1 - 4)");
}

void stampareMenuStatistiche(){
  system("clear || cls");
  printf("ciao sono nel menu Statistiche");
}

void stampareMenuCaricaPartita(){
  system("clear || cls");
  printf("ciao sono nel menu CaricaPartita");
}

void stampareMenuDifficolta(){
  system("clear || cls");
  printf("ciao sono nel menu Difficolta");
}

