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

void stampaCentrato(const char *testo); /* centra una stringa quando viene stampata sul terminale. */
void stampaASinistra(const char *testo) ; /* Centra una stringa quando stampata sul terminale. */
void mostraMenu(); /* Stampa a video il menù di partenza */
void spostaCursore(int x, int y);
void collezionaInput(int *input); /* recupera un input da terminale inserito dall'utente */

int main() 
{
  int scelta;
  mostraMenu();
  collezionaInput(&scelta);
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
  int spazi;           /* rappresenta le coordinate dove deve essere stampata "testo" */
  
  /* calcolo la lunghezza di dimStringa */
  dimStringa = strlen(testo);

  /* Calcolo il numero di spazi da inserire per spostare il testo a sinistra (Sottraendo 5, la 
  stringa viene spostata verso sinistra di 5 posizioni rispetto al margine destro) */
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

  /* Stampo effettivamente "testo" */
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
  system("clear || cls");
  printf("\n");
  stampaCentrato(" ");
  stampaCentrato(" __           _       _           ");
  stampaCentrato("/ _\\_   _  __| | ___ | | ___   _  ");
  stampaCentrato("\\ \\| | | |/ _` |/ _ \\| |/ / | | | ");
  stampaCentrato("_\\ \\ |_| | (_| | (_) |   <| |_| | ");
  stampaCentrato("\\__/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_| ");
  printf("\n\n");
  stampaCentrato("+---------------------------------------+");
  stampaCentrato("|                 ||                    |");
  stampaCentrato("|  Le Modalita':  ||                    |");
  stampaCentrato("|                 ||  Digita il numero  |");
  stampaCentrato("|-----------------||   per scegliere    |");
  stampaCentrato("|                 ||   la Modalita' e   |");
  stampaCentrato("|  1) Tutorial    ||  inizia a giocare! |");
  stampaCentrato("|  2) Facile      ||                    |");
  stampaCentrato("|  3) Media       ||                    |");
  stampaCentrato("|  4) Difficile   ||                    |");
  stampaCentrato("|  5) ESTREMA     ||                    |");
  stampaCentrato("|                 ||                    |");
  stampaCentrato("+---------------------------------------+");
  //stampaASinistra("Premi CNTRL + C per terminare il gioco")
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
void collezionaInput(int *input) {
  int resta = 1; /* variabile booleana che serve per capire fin quando dobbiamo restare nel ciclo */
  while(resta == 1) 
  {
    spostaCursore(1, 66);
    printf(">>");
    spostaCursore(1, 69);

    /* si legge un intero dalla tastiera ma se l'utente inserisce un valore non compreso tra 1 e 5 oppure 
    un valore non numero, allora viene stampato un messaggio di errore e viene richiesto l'input*/
    while((scanf("%d", input) != 1) || (*input < 1 || *input > 5))
    {

      /* Se l'input non è un numero, questo ciclo elimina tutti i caratteri rimasti nel buffer 
      fino al \n (nuova riga), evitando errori nelle successive letture. */
      while(getchar() != '\n');

      /* spostiamo il cursore in basso per poter stampare il messaggio di errore */
      spostaCursore(20, 35);
      printf("\033[31m Digita un numero compreso tra 1 e 5 e riprova. \033[0m");
      
      /* rispostiamo il cursore nella tabella del menù */
      spostaCursore(1, 69);
    }
    resta = 0;
    printf("\n\n\n\n");
  }
  printf("esce");
}
