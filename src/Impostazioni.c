#include "interfaccia_util.h"
#include "impostazioni.h"
#include "partita.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
  collezionareDifficolta(&inputDifficolta);
  collezionareDimensione(&inputDimensione);
  collezionareNomeGioco(nomePartita);
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

int collezionareDifficolta(int *inputDifficolta) {
  int inMenuDifficolta = 1;

  while(inMenuDifficolta) {
    impostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    
    while(scanf("%d", inputDifficolta) != 1) {
      pulireBuffer();
      impostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA - 6, ERR_MSG_COLONNA);
      impostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    }
   
    pulireBuffer();
    
    if(*inputDifficolta < OPZIONE_MIN || *inputDifficolta > OPZIONE_MAX) {
      mostrareMessaggioErrore("Digita un numero tra (1 - 4)", ERR_MSG_RIGA - 6, ERR_MSG_COLONNA - 5);
      impostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    } else {
      return *inputDifficolta;
    }
  }
}

int collezionareDimensione(int *inputDimensione) {
  int inMenuDifficolta = 1;

  while(inMenuDifficolta) {
    impostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    
    while(scanf("%d", inputDimensione) != 1) {
      pulireBuffer();
      impostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      impostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    }
   
    pulireBuffer();
    
    if(*inputDimensione < OPZIONE_MIN || *inputDimensione > OPZIONE_MAX) {
      mostrareMessaggioErrore("Digita un numero tra (1 - 4)", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA - 5);
      impostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    } else {
      return *inputDimensione;
    }
  }
}

void collezionareNomeGioco(char *nomeParitita) {
  impostareZonaInput(INPUT_RIGA_NOME, INPUT_COLONNA + 35);
  fgets(nomeParitita, NOME_MAX, stdin);
  int lunghezza = strlen(nomeParitita);
  if (lunghezza > 0 && nomeParitita[lunghezza - 1] == '\n') { 
    nomeParitita[lunghezza - 1] = '\0'; 
  }
  // Se il nome è vuoto, genera un nome random 
  if (strlen(nomeParitita) == 0) {
    snprintf(nomeParitita, NOME_MAX, "partita_%ld", time(NULL));
  }
}
