/*
Autori:
Fornelli Davide
Antoniciello Giuliano
Data di inizio di scrittura del file: 
04/04/2025
Nome del file:
Home Page sudoku
Scopo di ogni funzione presente:
mostraMenu() -> funzione utilizzata per stamparere a video il menù di partenza;
Modifiche apportate:
Nel giorno 06/04/2025, Fornelli Davide e Antonciello Giuliano, hanno inserito la funzioni stampareASinistra() e modificato layout e interfaccia
la modifica è stata effettuata per permettere una comprensione più chiara del menù di gioco
*/
#include <stdio.h>
#include <stdlib.h>
#include "homepage.h"
#include "interfaccia_util.h"
#include "menuCaricaPartita.h"
#include "menuDifficolta.h"
#include "menuStatistiche.h"

#define LARGHEZZA_TERMINALE 80

#define TITOLO_RIGA 10
#define TITOLO_COLONNA 36  
#define OPZIONE_START_RIGA 12
#define OPZIONE_COLONNA 30 
#define PROMPT_RIGA 19
#define PROMPT_COLONNA 28 
#define INPUT_RIGA 20
#define INPUT_COLONNA 35 
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 31

#define NUOVA_PARTITA 1
#define PARTITE_SALVATE 2
#define STATISTICHE 3
#define ESCI 4

#define OPZIONE_MIN 1
#define OPZIONE_MAX 4

/************************************************************ 
 *  FUNZIONE: stampareMenuPrincipale()                      *
 *  DESCRIZIONE: Mostra il menù iniziale del gioco          *
 *                                                          *
 *  ARGOMENTI: //                                           *
 *                                                          *
 *  RITORNO: //                                             *
 *                                                          *
 *  MODIFICHE:                                              *
 *  2025/03/26 - Prima versione                             *
 ************************************************************/

void stampareTitoloHomepage(){
  printf("\n");
  stampareCentrato("        _____ _____ ____  _____ _____ _____         ___ ___        ");
  stampareCentrato(" ___   |   __|  |  |    \\|     |  |  |  |  |       |_  |_  |   ___ ");
  stampareCentrato("|___|  |__   |  |  |  |  |  |  |    -|  |  |   _   |_  |  _|  |___|");
  stampareCentrato("       |_____|_____|____/|_____|__|__|_____|  |_|  |___|___|       ");
  stampareCentrato("                                                                   ");
}

void stampareMenuHomepage(){
  spostareCursore(TITOLO_RIGA, TITOLO_COLONNA);
  printf("- MENU -");
  spostareCursore(OPZIONE_START_RIGA, OPZIONE_COLONNA);
  printf("[1] Nuova Partita");
  spostareCursore(OPZIONE_START_RIGA + 1, OPZIONE_COLONNA);
  printf("[2] Partite Salvate");
  spostareCursore(OPZIONE_START_RIGA + 2, OPZIONE_COLONNA);
  printf("[3] Statistiche");
  spostareCursore(OPZIONE_START_RIGA + 3, OPZIONE_COLONNA);
  printf("[4] Esci");
  spostareCursore(PROMPT_RIGA, PROMPT_COLONNA);
  printf("Inserisci una scelta (1 - 4)");
}

void stampareMenuPrincipale() 
{
  pulireSchermo();
  stampareTitoloHomepage();
  stampareMenuHomepage();
}

/************************************************************ 
 *  FUNZIONE: collezionareInput()                             *
 *  DESCRIZIONE: richiede un qualsiasi input con la stampare  *
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
 *  2025/04/06 - Terza versione                             *
 *************************************************************/

void loopMenuPrincipale(){
  int input;
  stampareMenuPrincipale();
  collezionareInput(&input); 
}

void collezionareInput(int *input) {
  int inMenuPrinipale; 

  inMenuPrinipale = 1;
  while(inMenuPrinipale) {
    resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
    
    while(scanf("%d", input) != 1) { // input é formato da caratteri  
      pulireBuffer();
      mostrareMessaggioErrore(" Digita un Numero ", ERR_MSG_RIGA, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }

    pulireBuffer();

    if(*input < OPZIONE_MIN || *input > OPZIONE_MAX) {
      mostrareMessaggioErrore("Digita un Numero compreso tra 1 - 4 ", ERR_MSG_RIGA, ERR_MSG_COLONNA - 7);
      resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }
    else if (*input == NUOVA_PARTITA) {
      loopMenuDifficolta();
      inMenuPrinipale = 0;
    }
    else if (*input == PARTITE_SALVATE) {
      stampareMenuCaricaPartita();
      inMenuPrinipale = 0;
    }
    else if (*input == STATISTICHE) {
      stampareMenuStatistiche();
      inMenuPrinipale = 0;
    }
    else if (*input == ESCI) {
      exit(0);
    }
  }
}
