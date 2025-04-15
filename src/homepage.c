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

#include "homepage.h"
#include "menu.h"



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

void collezionaInput(int *input) {
  int inMenuPrinipale;

  inMenuPrinipale = 1;
  while(inMenuPrinipale) {
    spostaCursore(17, 55);
    printf(">>            ");
    spostaCursore(17, 58);

    while(scanf("%d", input) != 1) {
      while(getchar() != '\n'); // pulisce il buffer
                                
      spostaCursore(17, 55);
      printf(">>            ");

      spostaCursore(19, 50);
      printf("\033[31m Digita un Numero. \033[0m");
      spostaCursore(17, 58);
    }

    while(getchar() != '\n'); // <-- pulisce anche dopo un input valido
    if(*input < 1 || *input > 4) {
      spostaCursore(19, 50);
      printf("\033[31m      Riprova.     \033[0m");
      spostaCursore(17, 58);
    }

    else if (*input == 1) {
      stampareMenuDifficolta();
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

