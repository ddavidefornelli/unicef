#include "interfaccia_util.h"
#include "menuDifficolta.h"
#include "partita.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  DIFFICOLTA_FACILE = 1,
  DIFFICOLTA_INTERMEDIA,
  DIFFICOLTA_DIFFICILE,
  DIFFICOLTA_ESCI,
} DifficoltaOpzioni;

// Posizioni del menu (adattate per terminal 80 caratteri)
#define TITOLO_RIGA 9
#define TITOLO_COLONNA 0
#define OPZIONE_START_RIGA 9
#define OPZIONE_COLONNA 33 
#define PROMPT_RIGA 19
#define PROMPT_COLONNA 28 
#define INPUT_RIGA 12
#define INPUT_COLONNA 35 
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 32

// Opzioni del menu
#define OPZIONE_MIN 1
#define OPZIONE_MAX 4


void stampareMenuDifficolta() {
  pulireSchermo();
  stampareTitoloImpostazioni();
  stampareMenuImpostazioni();
}

void loopMenuDifficolta() {
  int inputDimensione;
  int inputDifficolta;
  stampareMenuDifficolta();
  collezionaInputDifficolta(&inputDifficolta);
  collezionaInputDimensione(&inputDimensione);
  loopPartita(inputDifficolta, inputDimensione);
}

void stampareTitoloImpostazioni(){
  printf("\n");
  stampareCentrato("        _                   _           _         _        ");
  stampareCentrato(" ___   |_|_____ ___ ___ ___| |_ ___ ___|_|___ ___|_|   ___ ");
  stampareCentrato("|___|  | |     | . | . |_ -|  _| .'|- _| | . |   | |  |___|");
  stampareCentrato("       |_|_|_|_|  _|___|___|_| |__,|___|_|___|_|_|_|       ");
  stampareCentrato("               |_|                                         ");
}

void stampareMenuImpostazioni(){

  spostareCursore(OPZIONE_START_RIGA - 1, OPZIONE_COLONNA - 6);
  printf("-SCEGLIERE LA DIFFICOLTA-");

  spostareCursore(OPZIONE_START_RIGA, OPZIONE_COLONNA);
  printf("[1] Facile");
  
  spostareCursore(OPZIONE_START_RIGA + 1, OPZIONE_COLONNA);
  printf("[2] Intermedia");
  
  spostareCursore(OPZIONE_START_RIGA + 2, OPZIONE_COLONNA);
  printf("[3] Difficile");

  spostareCursore(OPZIONE_START_RIGA + 6, OPZIONE_COLONNA - 6);
  printf("-SCEGLIERE LA DIMENSIONE-");

  spostareCursore(OPZIONE_START_RIGA + 7, OPZIONE_COLONNA);
  printf("[1] Piccola");
  
  spostareCursore(OPZIONE_START_RIGA + 8, OPZIONE_COLONNA);
  printf("[2] Media");
  
  spostareCursore(OPZIONE_START_RIGA + 9, OPZIONE_COLONNA);
  printf("[3] Grande");
  
}

void collezionaInputDifficolta(int *input) {

  int inMenuDifficolta = 1;

  while(inMenuDifficolta) {
    resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
    
    while(scanf("%d", input) != 1) {
      pulireBuffer();
      resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }
   
    pulireBuffer();
    
    if(*input < OPZIONE_MIN || *input > OPZIONE_MAX) {
      mostrareMessaggioErrore("Digita un numero tra (1 - 4)", ERR_MSG_RIGA, ERR_MSG_COLONNA - 5);
      resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }

    else if (*input == DIFFICOLTA_FACILE) {
      inMenuDifficolta = 0;
    }
    else if (*input == DIFFICOLTA_INTERMEDIA) {
      inMenuDifficolta = 0;
    }
    else if (*input == DIFFICOLTA_DIFFICILE) {
      inMenuDifficolta = 0;
    }
    else if (*input == DIFFICOLTA_ESCI) {
      exit(0);
    }

  }
}

void collezionaInputDimensione(int *input) {
  int inMenuDifficolta = 1;

  while(inMenuDifficolta) {
    resetZonaInput(INPUT_RIGA + 7, INPUT_COLONNA);
    
    while(scanf("%d", input) != 1) {
      pulireBuffer();
      resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }
   
    pulireBuffer();
    
    if(*input < OPZIONE_MIN || *input > OPZIONE_MAX) {
      mostrareMessaggioErrore("Digita un numero tra (1 - 4)", ERR_MSG_RIGA + 10, ERR_MSG_COLONNA - 5);
      resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }

    else if (*input == DIFFICOLTA_FACILE) {
      inMenuDifficolta = 0;
    }
    else if (*input == DIFFICOLTA_INTERMEDIA) {
      inMenuDifficolta = 0;
    }
    else if (*input == DIFFICOLTA_DIFFICILE) {
      inMenuDifficolta = 0;
    }
    else if (*input == DIFFICOLTA_ESCI) {
      exit(0);
    }

  }
}

