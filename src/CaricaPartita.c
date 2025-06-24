/*
AUTORI: Davide Fornelli
        Antoniciello Giuliano

DATA INIZIO: 04/05/2025

NOME FILE: Home Page sudoku

Scopo di ogni funzione presente:
- raccoglierePartiteSalvate: legge dalla cartella database i file che rappresentano le partite salvate dall’utente. Restituisce il numero totale di partite trovate.
- liberaPartite: liberare la memoria utilizzata per contenere i nomi delle partite.
- trovaFile: ricerca all'interno della cartella database(dove vengono salvate le partite) la partita che l'utente desidera giocare.
- stampareTitoloCaricaPartita: stampa la scritta 'CARICA PARTITA'.
- stampareZonaInput: stampa la cornice che identifica la zona dove digitare i valori da inserire all'interno della griglia del sudoku
- stampareMenuCaricaPartita: Gestisce il caricamento di una partita salvata.

*/

#include "funzioni_utilita.h"
#include "homepage.h"
#include "partita.h"
#include "CaricaPartita.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define RIGA 11
#define COLONNA 40
#define TITOLO_RIGA 9
#define TITOLO_COLONNA 0
#define OPZIONE_START_RIGA 12
#define OPZIONE_COLONNA 28
#define PROMPT_RIGA 19
#define PROMPT_COLONNA 28
#define INPUT_RIGA 20
#define INPUT_COLONNA 35
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 31
#define ARANCIONE "\033[38;5;208m"
#define RESET "\033[0m"


/********************************************************
* FUNZIONE: raccoglierePartiteSalvate                    *
*                                                        *
* DESCRIZIONE: Scansiona la cartella "database" per      *
*              trovare file che iniziano con "partita_"  *
*              e ne raccoglie i nomi in un array.        *
*                                                        *
* ARGOMENTI:                                             *
* - nomiPartite: array di stringhe dove salvare i nomi   *
*   dei file.                                            *
* - massimePartite: numero massimo di elementi           *
*   che l’array può contenere.                           *
*                                                        *
* RITORNO:                                               *
* - int: numero di file rilevati e copiati nell’array;   *
*        0 se la cartella non esiste o in caso di errore *
*                                                        *
* MODIFICHE:                                             *
* 2025/06/23 - Prima versione                            *
*********************************************************/
int raccoglierePartiteSalvate(char *nomiPartite[], int massimePartite) {
  DIR *cartella = opendir("database");
  struct dirent *voce;
  int conteggio = 0;

  if (cartella == NULL) {
    return 0;
  }
  
  while ((voce = readdir(cartella)) != NULL && conteggio < massimePartite) {
    if (strncmp(voce->d_name, "partita_", 8) == 0) {
      nomiPartite[conteggio] = malloc(strlen(voce->d_name) + 1);
      strcpy(nomiPartite[conteggio], voce->d_name);
      conteggio = conteggio + 1;
    }
  }
  closedir(cartella);
  return conteggio;
}


void liberaPartite(char *nomiPartite[], int numero) {
  int i = 0;
  while (i < numero) {
    if (nomiPartite[i] != NULL) {
      free(nomiPartite[i]);
    }
    i = i + 1;
  }
}


/********************************************************
* FUNZIONE: trovaFile                                    *
*                                                        *
* DESCRIZIONE: Cerca un nome di file partite nell’array  *
*              secondo l’indice numerico o una sottostr. *
*                                                        *
* ARGOMENTI:                                             *
* - char *nomiPartite[]: array di nomi di file.          *
* - int numero: numero di elementi validi nell’array.    *
* - const char *input: stringa inserita dall’utente,     *
*   che può essere un numero (come stringa) o parte del  *
*   nome del file.                                       *
*                                                        *
* RITORNO:                                               *
* - puntatore al nome di file trovato;                   *
*   NULL se non viene trovata nessuna corrispondenza.    *
*                                                        *
* MODIFICHE:                                             *
* 2025/06/23 - Prima versione                            *
*********************************************************/
const char *trovaFile(char *nomiPartite[], int numero, const char *input) {
  long indice = strtol(input, NULL, 10);
  int i = 0;
  
  if (indice >= 1 && indice <= numero) {
    return nomiPartite[indice - 1];
  }
  
  while (i < numero) {
    if (strstr(nomiPartite[i], input) != NULL) {
      return nomiPartite[i];
    }
    i = i + 1;
  }
  
  return NULL;
}


/********************************************************
* FUNZIONE: stampareTitoloCaricaPartita                 *
*                                                       *
* DESCRIZIONE: Mostra a schermo un titolo artistico     *
*              colorato per la schermata di caricamento *
*              delle partite salvate.                   *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
*                                                       *
* MODIFICHE:                                            *
* 2025/06/23 - Prima versione                           *
********************************************************/
void stampareTitoloCaricaPartita() {

printf(ARANCIONE);
stampareCentrato("     _____ _____ _____ _____ _____ _____     ");
stampareCentrato("    |     |  _  | __  |     |     |  _  |    ");
stampareCentrato("    |   --|     |    -|-   -|   --|     |    ");
stampareCentrato("    |_____|__|__|__|__|_____|_____|__|__|    ");
stampareCentrato("   _____ _____ _____ _____ _____ _____ _____ ");
stampareCentrato("  |  _  |  _  | __  |_   _|     |_   _|  _  |");
stampareCentrato("  |   __|     |    -| | | |-   -| | | |     |");
stampareCentrato("  |__|  |__|__|__|__| |_| |_____| |_| |__|__|");
stampareCentrato("                                             ");
printf("\n");
printf(RESET);
}


/********************************************************
* FUNZIONE: stampareZonaInput                           *
*                                                       *
* DESCRIZIONE: Disegna un riquadro sullo schermo per    *
*              l’inserimento del nome o indice della    *
*              partita salvata, con prompt esplicito.   *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
*                                                       *
* MODIFICHE:                                            *
* 2025/06/23 - Prima versione                           *
********************************************************/
void stampareZonaInput() {
  int contatore;

  printf("\n\n\n\n");
  spostareCursore(RIGA, COLONNA);
  printf("+--------------------------------------+");
  contatore = 0;
  while(contatore < 4) {
    spostareCursore(RIGA + 1 + contatore, COLONNA);
    printf("|                                      |");
    contatore = contatore + 1;
  }
  spostareCursore(RIGA + 2, COLONNA + 2);
  printf("Digita numero o nome (0 per uscire): ");
  spostareCursore(RIGA + 5, COLONNA);
  printf("+--------------------------------------+");
}


/********************************************************
* FUNZIONE: stampareMenuCaricaPartita                   *
*                                                       *
* DESCRIZIONE: Mostra l'elenco delle partite salvate    *
*              presenti nella cartella "database",      *
*              consente all’utente di scegliere una     *
*              partita da caricare digitando il nome    *
*              o il numero corrispondente.              *
*                                                       *
* COMPORTAMENTO:                                        *
* - Se non ci sono partite salvate, l'utente viene      *
*   reindirizzato alla homepage.                        *
* - L’utente può digitare “0” per tornare al menu       *
*   principale.                                         *
* - Se la partita esiste ed è caricabile, viene avviata.*
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Nessuno (effetto collaterale: avvia una      *
*          partita oppure torna alla homepage)          *
*                                                       *
* MODIFICHE:                                            *
* 2025/06/23 - Prima versione                           *
********************************************************/
void stampareMenuCaricaPartita(){
  char *nomiPartite[100];
  int numeroPartite;
  char nomeScelto[128];
  int i;
  int input;

  pulireSchermo();
  stampareTitoloCaricaPartita();

  numeroPartite = raccoglierePartiteSalvate(nomiPartite, 100);

  if (numeroPartite == 0) {
    printf("Nessuna partita salvata.\n");
    tornareHomepage(&input, TITOLO_RIGA + 2, TITOLO_COLONNA -10);
  }

  i = 0;
  while (i < numeroPartite) {
    printf("  [%d] %s\n", i + 1, nomiPartite[i]);
    i = i + 1;
  }

  stampareZonaInput();

  int continua = 1;
  while (continua) {
    spostareCursore(RIGA + 3, COLONNA + 14);
    printf(">> ");
    spostareCursore(RIGA + 3, COLONNA + 17);
    if (fgets(nomeScelto, 128, stdin) != NULL) {
      nomeScelto[strlen(nomeScelto) - 1] = '\0';
      if (strcmp(nomeScelto, "0") == 0) {
        avviareMenuPrincipale();
        continua = 0;
      } else {
        const char *file = trovaFile(nomiPartite, numeroPartite, nomeScelto);
        if (file != NULL) {
          char percorso[256];
          Partita partita;
          sprintf(percorso, "database/%s", file);
          
          if (caricaPartita(&partita, percorso)) {
            const char *underscore = strrchr(file, '_');
            if (underscore) {
              char nome[128];
              strcpy(nome, underscore + 1);
              char *punto = strstr(nome, ".txt");
              if (punto) {
                *punto = '\0';
              }
              scrivereNomePartita(&partita, nome);
            }
            avviarePartitaContinuata(&partita);
            continua = 0;
          } else {
            printf("Errore caricamento\n");
          }
        } else {
          printf("Partita non trovata\n");
        }
        if (continua) {
          printf("Riprova: ");
        }
      }
    }
  }
  liberaPartite(nomiPartite, numeroPartite);
}
