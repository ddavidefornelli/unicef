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

void stampaCentrato(const char *testo); /* centra una stringa quando viene stampata sul terminale. */
void stampaASinistra(const char *testo) ; /* Centra una stringa quando stampata sul terminale. */
void mostraMenu(); /* Stampa a video il menù di partenza */
void spostaCursore(int x, int y);
void collezionaInput(const char *testo, int *input); /* recupera un input da terminale inserito dall'utente */

int main() 
{
  int scelta;
  mostraMenu();
  collezionaInput("Digita il numero per scegliere la Modalita e premi invio:", &scelta);
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
  int spazi; /* rappresenta le coordinate dove deve essere stampata "testo" */
  dimStringa = strlen(testo); /* calcolo la lunghezza di dimStringa */
  spazi = (LARGHEZZA - dimStringa) - 5;
  
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
  printf("\n");
  stampaCentrato(" ");
  stampaCentrato(" __           _       _           ");
  stampaCentrato("/ _\\_   _  __| | ___ | | ___   _  ");
  stampaCentrato("\\ \\| | | |/ _` |/ _ \\| |/ / | | | ");
  stampaCentrato("_\\ \\ |_| | (_| | (_) |   <| |_| | ");
  stampaCentrato("\\__/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_| ");
  printf("\n\n");
  stampaCentrato("+----------------------------------+");
  stampaCentrato("|                ||                |");
  stampaCentrato("| Le Modalita':  ||                |");
  stampaCentrato("|                ||                |");
  stampaCentrato("+----------------||                |");
  stampaCentrato("|                ||   Digita il    |");
  stampaCentrato("| 1) Tutorial    ||  numero della  |");
  stampaCentrato("| 2) Facile      ||    modalita'   |");
  stampaCentrato("| 3) Media       ||     scelta     |");
  stampaCentrato("| 4) Difficile   ||                |");
  stampaCentrato("| 5) ESTREMA     ||                |");
  stampaCentrato("|                ||                |");
  stampaCentrato("|                ||                |");
  stampaCentrato("+----------------------------------+");
  printf("\n\n");

  //spostaCursore(16, 66);
}

void spostaCursore(int x, int y)
{
  printf("\033[%d;%dH", x, y);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
*  FUNZIONE: collezionaInput()                             *
*  DESCRIZIONE: richiede un qualsiasi input con la stampa  *
*               di un  testo, come la richiesta.           *
*                                                          *
*  ARGOMENTI:                                              *
*  const char *testo: richiesta da fare all'utente         *
*  *int scelta: variabile dedicata all'input da terminale  *
*                                                          *
*  RITORNO: //                                             *
*                                                          *
*  MODIFICHE:                                              *
*  2025/03/26 - Prima versione  MODIFICA DATA              *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
void collezionaInput(const char *testo, int *input){  
  printf("Digita il numero per scegliere la Modalita e premi invio:");  
  printf("\n >> ");  
  scanf("%d", input);
}
