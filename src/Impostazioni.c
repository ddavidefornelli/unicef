/*
AUTORI: Davide Fornelli
        Giuliano Antoniciello

DATA INIZIO: 27/05/2025

NOME FILE: tipiDiDato.c

Scopo delle funzioni presenti:
- stampareMenuDifficolta: Pulisce lo schermo e mostra a video il titolo e il menu delle impostazioni.
- avviareMenuDifficolta: Gestisce l’avvio di una nuova partita. Mostra il menu delle impostazioni e raccoglie: difficoltà, la dimensione della griglia
                        e il nome della partita e infine avvia la partita con i parametri raccolti.
- stampareTitoloImpostazioni: Stampa il titolo per la sezione "Impostazioni".
- stampareMenuImpostazioni: Stampa le opzioni del menu delle impostazioni, incluse:
                        difficoltà: facile, intermedia, difficile
                        dimensione della griglia: piccola, media, grande
                        spazio per l' inserimento del nome della partita
- collezionaDifficolta: Richiede all’utente di inserire un valore intero che rappresenti la difficoltà della partita.
- collezionaDimensione: Richiede all’utente un valore numerico corrispondente alla dimensione della griglia di gioco.
- collezionaNomeGioco: Richiede all’utente il nome da assegnare alla nuova partita.
 */

#include "interfaccia_util.h"
#include "Impostazioni.h"
#include "partita.h"
#include <stdio.h>
#include <string.h>

#define  DIFFICOLTA_FACILE  1
#define  DIFFICOLTA_INTERMEDIA  2 
#define  DIFFICOLTA_DIFFICILE  3

#define OPZIONE_START_RIGA 11
#define OPZIONE_COLONNA 16
#define INPUT_RIGA_DIFFICOLTA 15
#define INPUT_RIGA_DIMENSIONE 23
#define INPUT_COLONNA 18
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 12
#define INPUT_RIGA_NOME 11 
#define NOME_MAX 49

#define OPZIONE_MIN 1
#define OPZIONE_MAX 3

#define PICCOLA 1
#define MEDIA 2
#define GRANDE 3

#define CIANO "\033[36m"
#define RESET "\033[0m"

void stampareMenuDifficolta() {
  pulireSchermo();
  stampareTitoloImpostazioni();
  stampareMenuImpostazioni();
}

void avviareMenuDifficolta() {
  int inputDifficolta;
  int inputDimensione;
  char nomePartita[NOME_MAX + 1];
  stampareMenuDifficolta();
  collezionaDifficolta(&inputDifficolta);
  collezionaDimensione(&inputDimensione);
  collezionaNomeGioco(nomePartita);
  avviarePartita(nomePartita, inputDifficolta, inputDimensione);
}

void stampareTitoloImpostazioni(){
  printf(CIANO);
  printf("\n");
  stampareCentrato("        _                   _           _         _        ");
  stampareCentrato(" ___   |_|_____ ___ ___ ___| |_ ___ ___|_|___ ___|_|   ___ ");
  stampareCentrato("|___|  | |     | . | . |_ -|  _| .'|- _| | . |   | |  |___|");
  stampareCentrato("       |_|_|_|_|  _|___|___|_| |__,|___|_|___|_|_|_|       ");
  stampareCentrato("               |_|                                         ");
  printf(RESET);
}

void stampareMenuImpostazioni(){

  spostareCursore(OPZIONE_START_RIGA - 2, OPZIONE_COLONNA - 7);
  printf("-Scegliere la Difficolta-");

  spostareCursore(OPZIONE_START_RIGA, OPZIONE_COLONNA);
  printf("[1] facile");
  
  spostareCursore(OPZIONE_START_RIGA + 1, OPZIONE_COLONNA);
  printf("[2] intermedia");
  
  spostareCursore(OPZIONE_START_RIGA + 2, OPZIONE_COLONNA);
  printf("[3] difficile");
  
  spostareCursore(OPZIONE_START_RIGA + 6, OPZIONE_COLONNA - 7);
  printf("-Scegliere la Dimensione-");

  spostareCursore(OPZIONE_START_RIGA + 8, OPZIONE_COLONNA);
  printf("[1] piccola");
  
  spostareCursore(OPZIONE_START_RIGA + 9, OPZIONE_COLONNA);
  printf("[2] media");
  
  spostareCursore(OPZIONE_START_RIGA + 10, OPZIONE_COLONNA);
  printf("[3] grande");

  spostareCursore(OPZIONE_START_RIGA - 2 , OPZIONE_COLONNA + 35);
  printf("-Scegliere il Nome-");

}

int collezionaDifficolta(int *inputDifficolta) {
  int inMenuDifficolta = 1;

  while(inMenuDifficolta) {
    resetZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    
    while(scanf("%d", inputDifficolta) != 1) {
      pulireBuffer();
      resetZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA - 6, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    }
   
    pulireBuffer();
    
    if(*inputDifficolta < OPZIONE_MIN || *inputDifficolta > OPZIONE_MAX) {
      mostrareMessaggioErrore("Digita un numero tra (1 - 4)", ERR_MSG_RIGA - 6, ERR_MSG_COLONNA - 5);
      resetZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    } else {
      return *inputDifficolta;
    }
  }
}

int collezionaDimensione(int *inputDimensione) {
  int inMenuDifficolta = 1;

  while(inMenuDifficolta) {
    resetZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    
    while(scanf("%d", inputDimensione) != 1) {
      pulireBuffer();
      resetZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    }
   
    pulireBuffer();
    
    if(*inputDimensione < OPZIONE_MIN || *inputDimensione > OPZIONE_MAX) {
      mostrareMessaggioErrore("Digita un numero tra (1 - 4)", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA - 5);
      resetZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    } else {
      return *inputDimensione;
    }
  }
}

void collezionaNomeGioco(char *nomeParitita) {
  resetZonaInput(INPUT_RIGA_NOME, INPUT_COLONNA + 35);
  fgets(nomeParitita, NOME_MAX, stdin);
  int lunghezza = strlen(nomeParitita);
  if (lunghezza > 0 && nomeParitita[lunghezza - 1] == '\n') { 
    nomeParitita[lunghezza - 1] = '\0'; 
  }
}
