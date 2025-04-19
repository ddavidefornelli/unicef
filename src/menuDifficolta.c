#include "interfaccia_util.h"
#include "menudifficolta.h"
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
#define OPZIONE_START_RIGA 11
#define OPZIONE_COLONNA 30 
#define OPZIONE_INCREMENTO 1
#define PROMPT_RIGA 16
#define PROMPT_COLONNA 28 
#define INPUT_RIGA 17
#define INPUT_COLONNA 35 
#define ERR_MSG_RIGA 19
#define ERR_MSG_COLONNA 30 

// Opzioni del menu
#define OPZIONE_MIN 1
#define OPZIONE_MAX 4

int inMenuDifficolta = 1;

void loopMenuDifficolta() {
  int input;
  stampareMenuDifficolta();
  collezionaInputMenuDifficolta(&input);
}

void stampareMenuDifficolta() {
  system("clear || cls");

  printf("\n");
  stampaCentrato("        _                   _           _         _        ");
  stampaCentrato(" ___   |_|_____ ___ ___ ___| |_ ___ ___|_|___ ___|_|   ___ ");
  stampaCentrato("|___|  | |     | . | . |_ -|  _| .'|- _| | . |   | |  |___|");
  stampaCentrato("       |_|_|_|_|  _|___|___|_| |__,|___|_|___|_|_|_|       ");
  stampaCentrato("               |_|                                         ");

  
  spostaCursore(OPZIONE_START_RIGA, OPZIONE_COLONNA);
  printf("[%d] Facile", DIFFICOLTA_FACILE);
  
  spostaCursore(OPZIONE_START_RIGA + OPZIONE_INCREMENTO, OPZIONE_COLONNA);
  printf("[%d] Intermedia", DIFFICOLTA_INTERMEDIA);
  
  spostaCursore(OPZIONE_START_RIGA + 2*OPZIONE_INCREMENTO, OPZIONE_COLONNA);
  printf("[%d] Difficile", DIFFICOLTA_DIFFICILE);
  
  spostaCursore(OPZIONE_START_RIGA + 3*OPZIONE_INCREMENTO, OPZIONE_COLONNA);
  printf("\033[31m[%d] Esci \033[0m", DIFFICOLTA_ESCI);
  
  spostaCursore(PROMPT_RIGA, PROMPT_COLONNA);
  printf("Inserisci una scelta (%d - %d)", OPZIONE_MIN, OPZIONE_MAX);
}

void collezionaInputMenuDifficolta(int *input) {
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
      mostrareMessaggioErrore("Digita un numero tra (1 - 4)", ERR_MSG_RIGA, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }
    else if (*input == DIFFICOLTA_FACILE) {
      loopPartita();
      inMenuDifficolta = 0;
    }
    else if (*input == DIFFICOLTA_INTERMEDIA) {
      loopPartita();
      inMenuDifficolta = 0;
    }
    else if (*input == DIFFICOLTA_DIFFICILE) {
      loopPartita();
      inMenuDifficolta = 0;
    }
    else if (*input == DIFFICOLTA_ESCI) {
      exit(0);
    }
  }
}
