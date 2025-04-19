/*
Autori:
Fornelli Davide
Antoniciello Giuliano

Data di inizio di scrittura del file: 
26/03/2025 MODIFICALA FALLA PIU TARDI

Nome del file:
Home Page sudoku

Scopo di ogni funzione presente:
mostraMenu() -> funzione utilizzata per stampare a video il menù di partenza;

Modifiche apportate:
Nel giorno 27/03/2025, Fornelli Davide e Antonciello Giuliano, hanno inserito la funzioni stampaASinistra() e modificato layout e interfaccia
la modifica è stata effettuata per permettere una comprensione più chiara del menù di gioco  MODIFICALA FALLA PIU TARDI

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "homepage.h"
#include "interfaccia_util.h"
#include "menucaricapartita.h"
#include "menudifficolta.h"
#include "menustatistiche.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *  FUNZIONE: stampareMenuPrincipale()                      *
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
  printf("[2] Partite Salvate");
  spostaCursore(13, 50);
  printf("[3] Statistiche");
  spostaCursore(14, 50);
  printf("[4] Esci");
  spostaCursore(16, 48);
  printf("Inserisci una scelta (1 - 4)");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *  FUNZIONE: collezionaInput()                             *
 *  DESCRIZIONE: richiede un qualsiasi input con la stampa  *
 *               di un  testo, come la richiesta.           *
 *                                                          *
 *  ARGOMENTI:                                              *
 *  *int intput: variabile dedicata all'input da terminale  *
 *                                                          *
 *  RITORNO: //                                             *
 *                                                          *
 *  MODIFICHE:                                              *
 *  2025/03/26 - Prima versione                             *
 *  2025/03/28 - Seconda versione                           *
 *  2025/03/26 - Prima versione  MODIFICA DATA              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */

int inMenuPrinipale = 1;

void loopMenuPrincipale(){
  int input;
  stampareMenuPrincipale();
  collezionaInput(&input); 
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
      spostaCursore(posRiga, posColonna);
      printf("%s %s %s",COLOR_RED, testo, COLOR_RESET);
}

void collezionaInput(int *input) {
  while(inMenuPrinipale) {
    resetZonaInput(17, 50);
    while(scanf("%d", input) != 1) {
      pulireBuffer();
      mostrareMessaggioErrore(" Digita un Numero ", 19, 59);
      resetZonaInput(17, 50);
    }
    pulireBuffer();
    if(*input < 1 || *input > 4) {
      mostrareMessaggioErrore(" Digita un Numero ", 19, 59);
      resetZonaInput(17, 50);
    }

    else if (*input == 1) {
      loopMenuDifficolta();
      inMenuPrinipale = 0;
    }
    else if (*input == 2) {
      stampareMenuCaricaPartita();
      inMenuPrinipale = 0;
    }
    else if (*input == 3) {
      stampareMenuStatistiche();
      inMenuPrinipale = 0;
    }
    else if (*input == 4) {
      exit(0);
    }
  }
}

