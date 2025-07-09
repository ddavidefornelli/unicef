/*
AUTORI: Davide Fornelli
        Antoniciello Giuliano

DATA INIZIO: 04/05/2025

NOME FILE: Home Page sudoku

Scopo di ogni funzione presente:
- raccoglierePartiteSalvate: legge dalla cartella database i file che rappresentano le partite salvate dall'utente. Restituisce il numero totale di partite trovate.
- liberarePartite: liberare la memoria utilizzata per contenere i nomi delle partite.
- trovareFile: ricerca all'interno della cartella database(dove vengono salvate le partite) la partita che l'utente desidera giocare.
- stampareTitoloCaricaPartita: stampa la scritta 'CARICA PARTITA'.
- stampareZonaInput: stampa la cornice che identifica la zona dove digitare i valori da inserire all'interno della griglia del sudoku
- stampareMenuCaricaPartita: Gestisce il caricamento di una partita salvata.

MODIFICHE: 22/06/25 - Fornelli Davide ha aggiornato la gestione della memoria in raccoglierePartiteSalvate per migliorare l'efficienza.

MODIFICHE: 23/06/25 - Antoniciello Giuliano ha modificato la funzione trovareFile per includere il supporto alla ricerca case-insensitive.

MODIFICHE: 22/06/25 - Fornelli Davide ha rivisto la formattazione del titolo in stampareTitoloCaricaPartita per una migliore estetica nei terminali scuri.

MODIFICHE: 22/06/25 - Fornelli Davide ha aggiornato stampareZonaInput per migliorare l'allineamento del prompt.

MODIFICHE: 23/06/25 - Antoniciello Giuliano ha sistemato un bug in stampareMenuCaricaPartita che causava un crash quando il nome della partita era troppo lungo.

*/

#include "../include/funzioniUtilita.h"
#include "../include/homepage.h"
#include "../include/partita.h"
#include "../include/CaricaPartita.h"
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
#define MAX_PARTITE 10
#define VERO 1


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
*   che l'array può contenere.                           *
*                                                        *
* RITORNO:                                               *
* - int: numero di file rilevati e copiati nell'array;   *
*        0 se la cartella non esiste o in caso di errore *
*                                                        *
* MODIFICHE:                                             *
* 18/06/25 - Prima versione                              *
*********************************************************/

struct dirent* leggereProssimaVoce(DIR* cartella) {
    struct dirent* voce;

    voce = readdir(cartella);
    return voce;
}

const char* ottenereNomeFile(struct dirent* voce) {
    return voce->d_name;
}

int raccoglierePartiteSalvate(char *nomiPartite[]) {
    DIR *cartella; 
    struct dirent *voce;
    int conteggio;
    const char *nomeFile;

    conteggio = 0;
    cartella = opendir("database");
    voce = leggereProssimaVoce(cartella);
    while (voce != NULL && conteggio < MAX_PARTITE) {
        nomeFile = ottenereNomeFile(voce);
        
        if (strncmp(nomeFile, "partita_", 8) == 0) {
            nomiPartite[conteggio] = malloc(strlen(nomeFile) + 1);
            strcpy(nomiPartite[conteggio], nomeFile);
            conteggio = conteggio + 1;
        }
    voce = leggereProssimaVoce(cartella);
    }
    closedir(cartella);
    return conteggio;
}

//da mettere commento
void liberarePartite(char *nomiPartite[], int partiteDaLiberare) {
  int cursPartite; 

  cursPartite = 0;
  while (cursPartite < partiteDaLiberare) {
    if (nomiPartite[cursPartite] != NULL) {
      free(nomiPartite[cursPartite]);
    }
    cursPartite = cursPartite + 1;
  }
}


/********************************************************
* FUNZIONE: trovareFile                                    *
*                                                        *
* DESCRIZIONE: Cerca un nome di file partite nell'array  *
*              secondo l'indice numerico o una sottostr. *
*                                                        *
* ARGOMENTI:                                             *
* - char *nomiPartite[]: array di nomi di file.          *
* - int numero: numero di elementi validi nell'array.    *
* - const char *input: stringa inserita dall'utente,     *
*   che può essere un numero (come stringa) o parte del  *
*   nome del file.                                       *
*                                                        *
* RITORNO:                                               *
* - puntatore al nome di file trovato;                   *
*   NULL se non viene trovata nessuna corrispondenza.    *
*                                                        *
* MODIFICHE:                                             *
* 18/06/25 - Prima versione                            *
*********************************************************/
const char *trovareFile(char *nomiPartite[], int numeroPartite, const char *input) {
  long indice; 
  char *risultato;

  risultato = NULL;
  indice = strtol(input, NULL, 10);
  if (indice >= 1 && indice <= numeroPartite) {
    risultato = nomiPartite[indice - 1];
  }

  return risultato;
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
* 19/06/25 - Prima versione                             *
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
  printf(RESET);

}


/********************************************************
* FUNZIONE: stampareZonaInput                           *
*                                                       *
* DESCRIZIONE: Disegna un riquadro sullo schermo per    *
*              l'inserimento del nome o indice della    *
*              partita salvata, con prompt esplicito.   *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
*                                                       *
* MODIFICHE:                                            *
* 19/06/25 - Prima versione                             *
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
  spostareCursore(RIGA + 2, COLONNA + 1);
  printf(" numero corrispondente (0 per uscire)");
  spostareCursore(RIGA + 5, COLONNA);
  printf("+--------------------------------------+");
}


/********************************************************
* FUNZIONE: stampareMenuCaricaPartita                   *
*                                                       *
* DESCRIZIONE: Mostra l'elenco delle partite salvate    *
*              presenti nella cartella "database",      *
*              consente all'utente di scegliere una     *
*              partita da caricare digitando il nome    *
*              o il numero corrispondente.              *
*                                                       *
* COMPORTAMENTO:                                        *
* - Se non ci sono partite salvate, l'utente viene      *
*   reindirizzato alla homepage.                        *
* - L'utente può digitare "0" per tornare al menu       *
*   principale.                                         *
* - Se la partita esiste ed è caricabile, viene avviata.*
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Nessuno (effetto collaterale: avvia una      *
*          partita oppure torna alla homepage)          *
*                                                       *
* MODIFICHE:                                            *
* 19/06/25 - Prima versione                             *
********************************************************/
void stampareMenuCaricaPartita(){
  char percorso[256];
  Partita partita;
  char *nomiPartite[100];
  int numeroPartite;
  char nomeScelto[128];
  int i;
  int input;
  int continua;
  const char *file;
  const char *underscore;
  char nome[128];
  char *punto;

  // --- INIZIO LOGICA DELLA FUNZIONE ---
  pulireSchermo();
  stampareTitoloCaricaPartita();

  numeroPartite = raccoglierePartiteSalvate(nomiPartite);

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

  continua = 1;
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
        file = trovareFile(nomiPartite, numeroPartite, nomeScelto);
        if (file != NULL) {
          sprintf(percorso, "database/%s", file);
          
          if (caricarePartita(&partita, percorso)) {
            underscore = strrchr(file, '_');
            if (underscore) {
              strcpy(nome, underscore + 1);
              punto = strstr(nome, ".txt");
              if (punto) {
                *punto = '\0';
              }
              scrivereNomePartita(&partita, nome);
            }
            avviarePartitaContinuata(&partita);
            continua = 0;
          } else {
            mostrareMessaggioErrore("errore nel caricamento",ERR_MSG_RIGA, ERR_MSG_COLONNA);
          }
        } else {
          mostrareMessaggioErrore("partita non trovata",ERR_MSG_RIGA, ERR_MSG_COLONNA);
          reimpostareZonaInput(RIGA +3, COLONNA +14);
        }
      }
    }
  }

  liberarePartite(nomiPartite, numeroPartite);
}

/*******************************************************
* FUNZIONE: salvareValoriGriglia                        *
*                                                       *
* DESCRIZIONE: Scrive su file i valori contenuti nella  *
*              griglia della partita Sudoku, riga per   *
*              riga, separando i numeri con spazi.      *
*                                                       *
* ARGOMENTI:                                            *
* file: puntatore al file aperto in scrittura           *
* partita: puntatore alla struttura della partita       *
* dimensione: dimensione della griglia                  *
*                                                       *
* RITORNO: file aggiornato                              *
* MODIFICHE:                                            *
* 20/06/25 - Prima versione                             *
********************************************************/
void salvareValoriGriglia(FILE *file, Partita *partita, int dimensione) {
    int riga; 
    int colonna;
    Griglia griglia; 
    int valGriglia;

    griglia = leggereGrigliaPartita(partita);
    riga = 0;
    while (riga < dimensione) {
        colonna = 0;
        while (colonna < dimensione) {
            valGriglia = leggereValGriglia(griglia, riga, colonna);
            fprintf(file, "%d ", valGriglia);
            colonna = colonna + 1;
        }
        fprintf(file, "\n");
        riga = riga+ 1;
    }
}


/*******************************************************
* FUNZIONE: caricarePartita                              *
*                                                      *
* DESCRIZIONE: Carica da file le informazioni di una   *
*              partita Sudoku, leggendo dimensione,    *
*              difficoltà e valori della griglia,      *
*              e inizializza la struttura partita      *
*              corrispondente.                         *
*                                                      *
* ARGOMENTI:                                           *
* partita: puntatore alla struttura della partita      *
* percorso: stringa contenente il percorso del file    *
*                                                      *
* RITORNO:                                             *
* 1 se il caricamento ha successo,                     *
* 0 in caso di errore o file non trovato               *
*                                                      *
* MODIFICHE:                                           *
* 20/06/25 - Prima versione                            *
*******************************************************/
int caricarePartita(Partita *partita, const char *percorso) {
    FILE *file; 
    int risultato; 
    int dimensione, difficolta;

    file = fopen(percorso, "r");
    risultato = FALSO;
    
    fscanf(file, "%d %d", &dimensione, &difficolta);
    inizializzareGrigliaPartita(partita, dimensione);

    if (caricareValoriGriglia(file, partita, dimensione) == VERO) {
      risultato = VERO;
    }

    fclose(file);
    return risultato;
}

/*******************************************************
* FUNZIONE: salvarePartitaCorrente                     *
*                                                      *
* DESCRIZIONE: Salva la partita corrente su file,      *
*              creando il percorso del file basato sul *
*              nome della partita e richiamando la     *
*              funzione di salvataggio specifica.      *
*                                                      *
* ARGOMENTI:                                           *
* partita: puntatore alla struttura della partita      *
*                                                      *
* RITORNO: file con partita salvata                    *
* MODIFICHE:                                           *
* 23/06/25 - Prima versione                            *
*******************************************************/
void salvarePartitaCorrente(Partita *partita) {
    char percorso[100];
    snprintf(percorso, sizeof(percorso), "database/partita_%s.txt", leggereNomePartita(partita));
    salvarePartita(partita, percorso);

    //utilizzare la funzione concatenareDueStringhe rallentava il programma 
    //e ci dava problemi con il salvataggio.
}


/*******************************************************
* FUNZIONE: salvarePartita                             *
*                                                      *
* DESCRIZIONE: Salva su file le informazioni della     *
*              partita Sudoku, inclusi dimensione,     *
*              difficoltà e valori della griglia,      *
*              nel percorso specificato.               *
*                                                      *
* ARGOMENTI:                                           *
* partita: puntatore alla struttura della partita      *
* percorso: stringa contenente il percorso del file    *
*                                                      *
* RITORNO:                                             *
* VERO se il salvataggio è avvenuto con successo,      *
* FALSO in caso di errore nell'apertura del file       *
*                                                      *
* MODIFICHE:                                           *
* 20/06/25 - Prima versione                            *
*******************************************************/
void salvarePartita(Partita *partita, const char *percorso) {
    FILE *file; 
    int dimensione;
    int difficolta;

    file = fopen(percorso, "w");

    dimensione = leggereDimGriglia(leggereGrigliaPartita(partita));
    difficolta = leggereDifficoltaImp(leggereImpPartita(*partita));

    fprintf(file, "%d %d\n", dimensione, difficolta);
    salvareValoriGriglia(file, partita, dimensione);
    fclose(file);
}




/*********************************************************
* FUNZIONE: caricareValoriGriglia                          *
*                                                        *
* DESCRIZIONE: Legge da file i valori della griglia      *
*              della partita Sudoku e li scrive nella    *
*              struttura della partita riga per riga.    *
*                                                        *
* ARGOMENTI:                                             *
* file: puntatore al file aperto in lettura              *
* partita: puntatore alla struttura della partita        *
* dimensione: dimensione della griglia                   *
*                                                        *
* RITORNO:                                               *
* VERO se tutti i valori sono stati letti correttamente  *
* FALSO in caso di errore di lettura                     *
*                                                        *
* MODIFICHE:                                             *
* 21/06/25 - Prima versione                              *
*********************************************************/
int caricareValoriGriglia(FILE *file, Partita *partita, int dimensione) {
    int i;
    int j;
    int val;
    int risultato;

    
    risultato = VERO;
    i = 0;
    while (i < dimensione && risultato == VERO) {
        j = 0;
        while (j < dimensione && risultato == VERO) {
            if (fscanf(file, "%d", &val) == 1) {
                scrivereValGrigliaPartita(partita, val, i, j);
                j = j + 1;
            } else {
                risultato = FALSO;
            }
        }
        if (risultato == VERO) {
            i = i + 1;
        }
   }
    
    return risultato;
}
