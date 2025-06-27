/*
AUTORI: Davide Fornelli

DATA INIZIO: 27/05/2025

NOME FILE: interfaccia_util.c

Scopo delle funzioni presenti:
stampaASinistra() -> funzione utilizzata per centrare a sinistra sul terminale;
stampaCentrato() -> funzione utilizzata per centrare sul terminale il menù di partenza;
mostraMenu() -> funzione utilizzata per stampare a video il menù di partenza;
collezionaInput() -> funzione utilizzata per collezionare l' input dell utente;
spostareCursore() -> funzione utilizzata per spostare la posizione del cursore nel terminale;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "homepage.h"

typedef enum {
  LARGHEZZA_TERMINALE = 80,
  ALTEZZA_TERMINALE = 25
} terminale;

void spostareCursore(int x, int y)
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
 *  RITORNO: Terminale aggiornato                           *
 *                                                          *
 *  MODIFICHE:                                              *
 *  2025/03/26 - Prima versione                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
void stampareCentrato(const char *testo) 
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


/*******************************************************
reimpostareZonaInput                             *
*                                                      *
* DESCRIZIONE: Ripulisce e reimposta la zona di input  *
*              nella posizione specificata sullo       *
*              schermo. Mostra il prompt ">> " e       *
*              cancella eventuali caratteri residui.   *
*                                                      *
* ARGOMENTI:                                           *
* posRiga: riga dello schermo dove posizionare il      *
*          cursore per l'input                         *
* posColonna: colonna dello schermo dove posizionare   *
*              il cursore per l'input                  *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*                                                      *
* MODIFICHE:                                           *
* 2025/06/23 - Prima versione                          *
*******************************************************/
void reimpostareZonaInput(int posRiga, int posColonna){
    spostareCursore(posRiga, posColonna);
    printf(">> ");
    printf("%-8s", "");
    spostareCursore(posRiga, posColonna + 3);
}

void pulireBuffer(){
      while(getchar() != '\n'); // pulisce il buffer
}


/*******************************************************
* FUNZIONE: mostrareMessaggioErrore                    *
*                                                      *
* DESCRIZIONE: Mostra un messaggio di errore colorato  *
*              in rosso in una posizione specifica     *
*              dello schermo. Cancella prima la riga   *
*              per evitare sovrapposizioni di testo.   *
*                                                      *
* ARGOMENTI:                                           *
* testo: stringa del messaggio da visualizzare         *
* posRiga: riga in cui mostrare il messaggio           *
* posColonna: colonna in cui mostrare il messaggio     *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*                                                      *
* MODIFICHE:                                           *
* 2025/06/23 - Prima versione                          *
*******************************************************/
void mostrareMessaggioErrore(const char *testo, int posRiga, int posColonna) {
      spostareCursore(posRiga, 0);
      printf("%-80s", "");
      spostareCursore(posRiga, posColonna);
      printf("%s %s %s",COLOR_RED, testo, COLOR_RESET);
}


/*******************************************************
* FUNZIONE: tornareHomepage                            *
*                                                      *
* DESCRIZIONE: Mostra un'opzione per tornare alla      *
*              homepage del menu principale. Attende   *
*              l'inserimento del valore "0" da parte   *
*              dell'utente, verificando che l'input    *
*              sia corretto. In caso di input errato,  *
*              mostra un messaggio d'errore e richiede *
*              nuovamente l'inserimento.               *
*                                                      *
* ARGOMENTI:                                           *
* input: puntatore a intero in cui viene memorizzato   *
*        il valore inserito dall'utente                *
* posRiga: riga in cui visualizzare il prompt          *
* posColonna: colonna in cui visualizzare il prompt    *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*                                                      *
* MODIFICHE:                                           *
* 2025/06/23 - Prima versione                          *
*******************************************************/
void tornareHomepage(int *input, int posRiga, int posColonna){
  int inMenuCorrente = 1;

  spostareCursore(posRiga - 1, posColonna);
  printf("[0] torna alla homepage");
  while(inMenuCorrente) {
    reimpostareZonaInput(posRiga, posColonna + 8);

    while(scanf("%d", input) != 1) {
        mostrareMessaggioErrore("input non valido", posRiga + 2, posColonna + 3);
        reimpostareZonaInput(posRiga, posColonna + 8);
        pulireBuffer();
    }
    if(*input != 0){
        mostrareMessaggioErrore("input non valido", posRiga + 2, posColonna + 3);
        reimpostareZonaInput(posRiga, posColonna + 8);
        pulireBuffer();
    }
    else if (*input == 0) {
      avviareMenuPrincipale();
      inMenuCorrente = 0;
    }
  }
}

void pulireSchermo(){
  system("clear || cls");
}
