/*
AUTORI: Davide Fornelli
        Giuliano Antoniciello

DATA INIZIO: 27/05/2025

NOME FILE: tipiDiDato.c

Scopo delle funzioni presenti:
- stampareMenuDifficolta: Pulisce lo schermo e mostra a video il titolo e il menu delle impostazioni.
  e il nome della partita e infine avvia la partita con i parametri raccolti.
- stampareTitoloImpostazioni: Stampa il titolo per la sezione "Impostazioni".
- stampareMenuImpostazioni: Stampa le opzioni del menu delle impostazioni, incluse:
- difficoltà: facile, intermedia, difficile
- dimensione della griglia: piccola, media, grande
- spazio per l' inserimento del nome della partita
- collezionareDifficolta: Richiede all’utente di inserire un valore intero che rappresenti la difficoltà della partita.
- collezionareDimensione: Richiede all’utente un valore numerico corrispondente alla dimensione della griglia di gioco.
- collezionaNomeGioco: Richiede all’utente il nome da assegnare alla nuova partita.
 */

#include "../include/funzioniUtilita.h"
#include "../include/Impostazioni.h"
#include "../include/partita.h"
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


/********************************************************
* FUNZIONE: stampareMenuDifficolta                      *
*                                                       *
* DESCRIZIONE: Pulisce lo schermo e stampa il titolo e  *
*              il menu delle impostazioni di difficoltà *
*              per iniziare una nuova partita.          *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
********************************************************/
void stampareMenuDifficolta() {
  pulireSchermo();
  printf(CIANO);
  printf("\n");
  stampareCentrato("        _                   _           _         _        ");
  stampareCentrato(" ___   |_|_____ ___ ___ ___| |_ ___ ___|_|___ ___|_|   ___ ");
  stampareCentrato("|___|  | |     | . | . |_ -|  _| .'|- _| | . |   | |  |___|");
  stampareCentrato("       |_|_|_|_|  _|___|___|_| |__,|___|_|___|_|_|_|       ");
  stampareCentrato("               |_|                                         ");
  printf(RESET);
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


/********************************************************
* FUNZIONE: avviareMenuImpostazioni                     *
*                                                       *
* DESCRIZIONE: Avvia il processo per iniziare una       *
*              nuova partita. Mostra il menu di scelta  *
*              della difficoltà, raccoglie i parametri  *
*              necessari (difficoltà, dimensione, nome  *
*              della partita) e avvia il gioco.         *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
********************************************************/
void avviareImpostazioni() {
  int inputDifficolta;
  int inputDimensione;
  char inputNomePartita[NOME_MAX + 1];
  Impostazioni impostazioni;

  stampareMenuDifficolta();

  inputDifficolta = collezionareDifficolta();
  inputDimensione = collezionareDimensione();
  collezionareNomePartita(inputNomePartita);


  scrivereDifficoltaImp(&impostazioni, inputDifficolta);
  scrivereDimensioneImp(&impostazioni, inputDimensione);
  avviarePartita(inputNomePartita, impostazioni);
}




/*********************************************************
* FUNZIONE: collezionareDifficolta                       *
*                                                        *
* DESCRIZIONE: Permette all'utente di inserire un valore *
*              numerico per la difficoltà del gioco.     *
*              Controlla che l'input sia numerico e      *
*              compreso tara OPZIONE_MIN e OPZIONE_MAX.  *
*                                                        *
* ARGOMENTI:                                             *
* - int *inputDifficolta: puntatore alla variabile che   *
*   conterrà il valore scelto dall'utente.               *
*                                                        *
* RITORNO: valore della difficoltà selezionata           *
********************************************************/
int collezionareDifficolta() {
  int inputDifficolta;
  int inMenuDifficolta;

  inMenuDifficolta = VERO;

  while(inMenuDifficolta) {
    reimpostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    
    while(scanf("%d", &inputDifficolta) != 1) {
      pulireBuffer();
      reimpostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA - 6, ERR_MSG_COLONNA);
      reimpostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    }
    
    pulireBuffer();
    
    if(inputDifficolta >= OPZIONE_MIN && inputDifficolta <= OPZIONE_MAX) {
      inMenuDifficolta = 0;  
    } else {
      mostrareMessaggioErrore("Digita un numero tra (1 - 4)", ERR_MSG_RIGA - 6, ERR_MSG_COLONNA - 5);
      reimpostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    }
  }

  return inputDifficolta;
}

/*********************************************************
* FUNZIONE: collezionareDimensione                       *
*                                                        *
* DESCRIZIONE: Permette all'utente di inserire un valore *
*              numerico per la dimensione della griglia. *
*              Valida l’input assicurandosi che rientri  *
*              nell’intervallo OPZIONE_MIN - OPZIONE_MAX *
*                                                        *
* ARGOMENTI:                                             *
* - int *inputDimensione: puntatore alla variabile che   *
*   conterrà il valore scelto dall’utente.               *
*                                                        *
* RITORNO: valore della dimensione selezionata           *
********************************************************/

int collezionareDimensione() {
  int inMenuDimensione;
  int inputDimensione;

  inMenuDimensione = 1;
  while(inMenuDimensione) {
    reimpostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    
    while(scanf("%d", &inputDimensione) != 1) {
      pulireBuffer();
      reimpostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      reimpostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    }

    pulireBuffer();

    if(inputDimensione >= OPZIONE_MIN && inputDimensione <= OPZIONE_MAX) {
      inMenuDimensione = 0;  
    } else {
      mostrareMessaggioErrore("Digita un numero tra (1 - 4)", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA - 5);
      reimpostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    }
  }

  return inputDimensione;
}


/**************************************************************
* FUNZIONE: collezionaNomePartita                             *
*                                                             *
* DESCRIZIONE: Permette all’utente di inserire un nome per la *
*              partita. Se non viene inserito alcun nome,     *
*              ne genera uno automaticamente in base al tempo *
*              corrente.                                      *
*                                                             *
* ARGOMENTI:                                                  *
* - char *nomeParitita: puntatore a buffer dove salvare il    *
*   nome della partita.                                       *
*                                                             *
* RITORNO: partita aggiornata                                 *
**************************************************************/
void collezionareNomePartita(char *nomeParitita) {
  int lunghezza;

  reimpostareZonaInput(INPUT_RIGA_NOME, INPUT_COLONNA + 35);
  fgets(nomeParitita, NOME_MAX, stdin);
  lunghezza = strlen(nomeParitita);
  if (lunghezza > 0 && nomeParitita[lunghezza - 1] == '\n') { 
    nomeParitita[lunghezza - 1] = '\0'; 
  }
}
