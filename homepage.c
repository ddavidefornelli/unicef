/*
Autori:
Fornelli Davide
Antoniciello Giuliano

Data di inizio di scrittura del file: 
26/03/2025 MODIFICALA FALLA PIU TARDI

Nome del file:
Home Page sudoku

Scopo di ogni funzione presente:
stampaCentrato() -> funzione utilizzata per posizionare al centro del terminale il menù di partenza;
stampaASinistra() -> funzione utilizzata per posizionare al lato sinistro del terminale una stringa quando viene stampata.
mostraMenu() -> funzione utilizzata per stampare a video il menù di partenza;

Modifiche apportate:
Nel giorno 27/03/2025, Fornelli Davide e Antonciello Giuliano, hanno inserito la funzioni stampaASinistra() e modificato layout e interfaccia
la modifica è stata effettuata per permettere una comprensione più chiara del menù di gioco  MODIFICALA FALLA PIU TARDI
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGHEZZA (120) /* rappresenta la larghezza del terminale */
#define GRIGIO ("\033[37m") /* rappresenta la larghezza del terminale */
#define RESET ("\033[0m") /* rappresenta la larghezza del terminale */
#define MOVE_CURSOR(row, col) printf("\033[%d;%dH", row, col)

int main();
void stampaCentrato(const char *testo); /* centra una stringa quando viene stampata sul terminale. */
void stampaASinistra(const char *testo) ; /* Centra una stringa quando stampata sul terminale. */
void mostraMenu(); /* Stampa a video il menù di partenza */


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
  /* Definisco ed inizializzo le variabili */
  int spaziDaInserire = 0; /* contatore per il ciclo */
  int dimStringa; /* calcolo la lunghezza di dimStringa */
  int spazi; /* rappresenta le coordinate dove deve essere stampata "testo" */
  dimStringa = strlen(testo);
  spazi = (LARGHEZZA - dimStringa) / 2;
  
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

void stampaASinistra(const char *testo) 
{
  /* Definisco ed inizializzo le variabili */
  int spaziDaInserire; /* contatore per il ciclo */
  int dimStringa; 
  int spazi; /* rappresenta le coordinate dove deve essere stampata "testo" */
  dimStringa = strlen(testo); /* calcolo la lunghezza di dimStringa */
  spazi = (LARGHEZZA - dimStringa) - 5;
  
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
  int scelta;
  printf("\n");
  stampaCentrato(" ");
  stampaCentrato(" __           _       _           ");
  stampaCentrato("/ _\\_   _  __| | ___ | | ___   _  ");
  stampaCentrato("\\ \\| | | |/ _` |/ _ \\| |/ / | | | ");
  stampaCentrato("_\\ \\ |_| | (_| | (_) |   <| |_| | ");
  stampaCentrato("\\__/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_| ");
  printf("\n\n");
  stampaCentrato("+---------------------------------+");
  stampaCentrato("|                ||               |");
  stampaCentrato("| Le Modalita':  ||               |");
  stampaCentrato("|                ||               |");
  stampaCentrato("+----------------||   Modalita'   |");
  stampaCentrato("|                ||  Selezionata  |");
  stampaCentrato("| 1) Tutorial    ||               |");
  stampaCentrato("| 2) Facile      ||               |");
  stampaCentrato("| 3) Media       ||               |");
  stampaCentrato("| 4) Difficile   ||               |");
  stampaCentrato("|                ||               |");
  stampaCentrato("+---------------------------------+");

  printf("\n");

  stampaCentrato("Digita il numero per scegliere la Modalita");
  stampaCentrato("  premi invio per iniziare a giocare!");

  printf("\n\n\n\n\n");
  stampaASinistra("Digita FINE per terminare il gioco");

  MOVE_CURSOR(16, 66);
   
  // Chiede l'input
  printf(">> ");  
  scanf("%d", &scelta);
}

