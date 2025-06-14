#include "interfaccia_util.h"
#include "menuDifficolta.h"
#include "partita.h"
#include <stdio.h>
#include <stdlib.h>

#define  DIFFICOLTA_FACILE  1
#define  DIFFICOLTA_INTERMEDIA  2 
#define  DIFFICOLTA_DIFFICILE  3

#define TITOLO_RIGA 9
#define TITOLO_COLONNA 0
#define OPZIONE_START_RIGA 11
#define OPZIONE_COLONNA 33 
#define PROMPT_RIGA 19
#define PROMPT_COLONNA 28 
#define INPUT_RIGA_DIFFICOLTA 15
#define INPUT_RIGA_DIMENSIONE 23
#define INPUT_COLONNA 35 
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 32

#define OPZIONE_MIN 1
#define OPZIONE_MAX 3

#define PICCOLA 1
#define MEDIA 2
#define GRANDE 3


void stampareMenuDifficolta() {
  pulireSchermo();
  stampareTitoloImpostazioni();
  stampareMenuImpostazioni();
}

void loopMenuDifficolta() {
  int inputDifficolta;
  int inputDimensione;
  stampareMenuDifficolta();
  collezionaDifficolta(&inputDifficolta);
  collezionaDimensione(&inputDimensione);
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

  spostareCursore(OPZIONE_START_RIGA - 2, 0);
  stampareCentrato("-Scegliere la Difficolta-");

  spostareCursore(OPZIONE_START_RIGA, OPZIONE_COLONNA);
  printf("[1] facile");
  
  spostareCursore(OPZIONE_START_RIGA + 1, OPZIONE_COLONNA);
  printf("[2] intermedia");
  
  spostareCursore(OPZIONE_START_RIGA + 2, OPZIONE_COLONNA);
  printf("[3] difficile");
  
  spostareCursore(OPZIONE_START_RIGA + 6, 0);
  stampareCentrato("-scegliere la dimensione-");

  spostareCursore(OPZIONE_START_RIGA + 8, OPZIONE_COLONNA);
  printf("[1] piccola");
  
  spostareCursore(OPZIONE_START_RIGA + 9, OPZIONE_COLONNA);
  printf("[2] mendia");
  
  spostareCursore(OPZIONE_START_RIGA + 10, OPZIONE_COLONNA);
  printf("[3] grande");

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
