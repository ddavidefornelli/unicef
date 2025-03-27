/*
Autori:
Fornelli Davide
Antoniciello Giuliano

Data di inizio di scrittura del file: 
26/03/2025

Nome del file:
Home Page sudoku

Scopo di ogni funzione presente:
stampaASinistra() -> funzione utilizzata per centrare a sinistra sul terminale;
stampaCentrato() -> funzione utilizzata per centrare sul terminale il menù di partenza;
mostraMenu() -> funzione utilizzata per stampare a video il menù di partenza;
collezionaInput() -> funzione utilizzata per collezionare l' input dell utente;
spostaCursore() -> funzione utilizzata per spostare la posizione del cursore nel terminale;


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGHEZZA (120) /* rappresenta la larghezza del terminale */

int main();
void stampaCentrato(const char *testo); /* Centra una stringa quando stampata nel terminale. paramentro = stringa da centrare */
void mostraMenu(); /* Stampa a video il menù di partenza */
void spostaCursore(int x, int y);
void collezionaInput();


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
* * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */

void stampaCentrato(const char *testo) 
{
  /* Definisco ed inizializzo le variabili */
  // int spazi = (LARGHEZZA - len) / 2;
  int spaziDaInserire; /* contatore per il ciclo */
  int dimStringa; /* calcolo la lunghezza di dimStringa */
  int spazi; 

  /* Se "testo" è più lunga della larghezza del terminale, evito spazi negativi */
  
  dimStringa = strlen(testo);
  spazi = (LARGHEZZA - dimStringa) / 2;

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
  // int spazi = (LARGHEZZA - len) / 2;
  int spaziDaInserire; /* contatore per il ciclo */
  int dimStringa; /* calcolo la lunghezza di dimStringa */
  int spazi; 

  /* Se "testo" è più lunga della larghezza del terminale, evito spazi negativi */
  
  dimStringa = strlen(testo);
  spazi = (LARGHEZZA - dimStringa) - 5;

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
* * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */

void mostraMenu() 
{
  int scelta;
  printf("\n");
  stampaCentrato(" ");
  stampaCentrato(" __           _       _           ");
  stampaCentrato("/ _\\_   _  __| | ___ | | ___   _  ");
  stampaCentrato("\\ \\| | | |/ _` |/ _ \\| |/ / | | | ");
  stampaCentrato("_\\ \\ |_| | (_| | (_) |   <| |_| | ");
  stampaCentrato("\\__/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_| ");
  printf("\n\n");
  stampaCentrato("+---------------------------------+") ;
  stampaCentrato("|                ||               |") ;
  stampaCentrato("| Le Modalita':  ||               |");
  stampaCentrato("|                ||               |") ;
  stampaCentrato("+----------------||   Modalita'   |") ;
  stampaCentrato("|                ||  Selezionata  |") ;
  stampaCentrato("| 1) Tutorial    ||               |");
  stampaCentrato("| 2) Facile      ||               |");
  stampaCentrato("| 3) Media       ||               |");
  stampaCentrato("| 4) Difficile   ||               |");
  stampaCentrato("|                ||               |") ;
  stampaCentrato("+---------------------------------+");

  printf("\n");

  stampaCentrato("Digita il numero per scegliere la Modalita");
  stampaCentrato("  premi invio per iniziare a giocare!");



  printf("\n\n\n\n\n");
  stampaASinistra("Digita FINE per terminare il gioco");

  spostaCursore(16, 66);
  // Chiede l'input
  collezionaInput();
}

void spostaCursore(int x, int y){
  printf("\033[%d;%dH", x, y);
}

void collezionaInput(){
  int scelta;

  printf(">> ");  
  scanf("%d", &scelta);
}
