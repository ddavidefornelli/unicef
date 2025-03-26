/*
Autori:
Fornelli Davide
Antoniciello Giuliano

Data di inizio di scrittura del file: 
26/03/2025

Nome del file:
Home Page sudoku

Scopo di ogni funzione presente:
stampaCentrato() -> funzione utilizzata per centrare sul terminale il menù di partenza;
mostraMenu() -> funzione utilizzata per stampare a video il menù di partenza;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LARGHEZZA 120 /* serve per rappresentare la larghezza del terminale */

int main();
void stampaCentrato(const char *testo); /* funzione per centrare sul terminale una stringa. Si passa come paramentro la stringa da centrare */
void mostraMenu(); /* funzione per stampare a video il menù di partenza */


int main() {
  mostraMenu();
  getchar();
  return 0;
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
*                                                          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
void stampaCentrato(const char *testo) 
{
  /* Definisco ed inizializzo la variabile */
  // int spazi = (LARGHEZZA - len) / 2;
  int spaziDaInserire = 0; /* contatore per il ciclo */
  int dimStringa = strlen(testo); /* calcolo la lunghezza di dimStringa */

  /* serve per centrare la stringa quando è stampato a video (il valore di "spazi" è adattato alle dimensioni di LARGHEZZA) */
  int spazi = (LARGHEZZA - dimStringa) / 2;

  /* Se "testo" è più lunga della larghezza del terminale, evito spazi negativi */
  if (spazi < 0)
  {
    spazi = 0;
  }
  
  /* Stampo tanti spazi vuoti quanto basta per centrare "testo" */
  while(spaziDaInserire < spazi)
  {
    printf(" ");
    spaziDaInserire++;
  }
  printf("%s\n", testo);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*  FUNZIONE: mostraMenu()                                  *
*  DESCRIZIONE: Mostra il menù iniziale del gioco          *
*                                                          *
*  ARGOMENTI: //                                           *
*                                                          *
*  RITORNO: //                                             *
*                                                          *
*  MODIFICHE:                                              *
*  2025/03/26 - Prima versione                             *
*                                                          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
void mostraMenu() 
{
  //int sceltaUtente;
  printf("\n");
  stampaCentrato(" ");
  stampaCentrato(" __           _       _           ");
  stampaCentrato("/ _\\_   _  __| | ___ | | ___   _  ");
  stampaCentrato("\\ \\| | | |/ _` |/ _ \\| |/ / | | | ");
  stampaCentrato("_\\ \\ |_| | (_| | (_) |   <| |_| | ");
  stampaCentrato("\\__/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_| ");
  printf("\n\n");
  
  stampaCentrato("digita un numero per selezionare la modalita' di gioco e premi invio per confermare:");
  printf("\n");
  
  stampaCentrato("1) Tutorial  ");
  stampaCentrato("2) Facile    ");
  stampaCentrato("3) Media     ");
  stampaCentrato("4) Difficile ");
  //scanf("%d", &sceltaUtente);
  //printf("%d", sceltaUtente);
}