/*
Autori: Davide Fornelli
        Antoniciello Giuliano

Data di inizio di scrittura del file: 
        04/05/2025

Nome del file:
        Home Page sudoku

Scopo di ogni funzione presente:
- stampareTitoloHomepage: Visualizza il titolo del gioco al centro del terminale.
- stampareMenuHomepage: Stampa le opzioni del menu principale.
- stampareMenuPrincipale: Pulisce lo schermo e mostra sia il titolo che il menu principale del gioco.
- avviareMenuPrincipale: Avvia il menu principale mostrando il contenuto a schermo.
- collezionareInput: Gestisce l’acquisizione dell’input numerico da parte dell’utente nel menu principale.

*/

#include <stdio.h>
#include <stdlib.h>
#include "homepage.h"
#include "funzioni_utilita.h"
#include "CaricaPartita.h"
#include "Impostazioni.h"

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
#define ESCI 3

#define OPZIONE_MIN 1
#define OPZIONE_MAX 4

#define VERDE "\033[32m"
#define RESET "\033[0m"


/********************************************************
* FUNZIONE: stampareTitoloHomepage                      *
*                                                       *
* DESCRIZIONE: Stampa a schermo il titolo grafico       *
*              colorato della homepage, centrato        *
*              orizzontalmente nel terminale.           *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
*                                                       *
* MODIFICHE:                                            *
* 2025/06/23 - Prima versione                           *
********************************************************/
void stampareTitoloHomepage(){
  printf(VERDE);
  printf("\n");
  stampareCentrato("        _____ _____ ____  _____ _____ _____         ___ ___        ");
  stampareCentrato(" ___   |   __|  |  |    \\|     |  |  |  |  |       |_  |_  |   ___ ");
  stampareCentrato("|___|  |__   |  |  |  |  |  |  |    -|  |  |   _   |_  |  _|  |___|");
  stampareCentrato("       |_____|_____|____/|_____|__|__|_____|  |_|  |___|___|       ");
  stampareCentrato("                                                                   ");
  printf(RESET);
}


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
void stampareMenuHomepage(){
  spostareCursore(TITOLO_RIGA, TITOLO_COLONNA);
  printf("- MENU -");
  spostareCursore(OPZIONE_START_RIGA, OPZIONE_COLONNA);
  printf("[1] Nuova Partita");
  spostareCursore(OPZIONE_START_RIGA + 1, OPZIONE_COLONNA);
  printf("[2] Partite Salvate");
  spostareCursore(OPZIONE_START_RIGA + 2, OPZIONE_COLONNA);
  printf("[4] Esci");
  spostareCursore(PROMPT_RIGA, PROMPT_COLONNA);
  printf("Inserisci una scelta (1 - 4)");
}


/********************************************************
* FUNZIONE: stampareMenuPrincipale                      *
*                                                       *
* DESCRIZIONE: Pulisce lo schermo e visualizza il       *
*              titolo della homepage seguito dal menu   *
*              principale.                              *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
*                                                       *
* MODIFICHE:                                            *
* 2025/06/23 - Prima versione                           *
********************************************************/
void stampareMenuPrincipale() 
{
  pulireSchermo();
  stampareTitoloHomepage();
  stampareMenuHomepage();
}


/********************************************************
* FUNZIONE: avviareMenuPrincipale                       *
*                                                       *
* DESCRIZIONE: Avvia il menu principale visualizzandolo *
*              e raccogliendo l'input dell'utente.      *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
*                                                       *
* MODIFICHE:                                            *
* 2025/06/23 - Prima versione                           *
********************************************************/
void avviareMenuPrincipale(){
  int input;
  stampareMenuPrincipale();
  collezionareInput(&input); 
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
      avviareMenuDifficolta();
      inMenuPrinipale = 0;
    }
    else if (*input == PARTITE_SALVATE) {
      stampareMenuCaricaPartita();
      inMenuPrinipale = 0;
    }
    else if (*input == ESCI) {
      exit(0);
    }
  }
}
