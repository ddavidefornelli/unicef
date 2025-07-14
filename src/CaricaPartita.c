/*
AUTORI: Davide Fornelli
        Antoniciello Giuliano

DATA INIZIO: 04/05/2025

NOME FILE: Home Page sudoku

Scopo di ogni funzione presente:
- raccoglierePartiteSalvate: legge dalla cartella database i file che rappresentano le partite salvate dall'utente. Restituisce il numero totale di partite trovate.
- stampareTitoloCaricaPartita: stampa la scritta 'CARICA PARTITA'.
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
#define MAX_PARTITE 13
#define VERO 1
#define MAX_NOME_FILE 50


/***********************************************************
* FUNZIONE: leggereProssimaVoce                            *
*                                                          *
* DESCRIZIONE: legge la voce succesiva all' interno della  *
* cartella database (in cui ci sono le partite salvate)    *
*                                                          *
* ARGOMENTI:                                               *
* -cartella: cartella in cui andare a leggere la voce      *
*  successiva, tipo cartella                               *
*                                                          *
* RITORNO:                                                 *
* -voce: voce successiva letta, tipo file                  *
************************************************************/
//
// abbiamo messo qui le funzioni (anche se sono di accesso al tipo di dato Cartella)
// per continuita' del codice... 
//
struct dirent* leggereProssimaVoce(DIR* cartella) {
    struct dirent* voceLetta;

    voceLetta = readdir(cartella);
    return voceLetta;
}

/*********************************************************************
* FUNZIONE: ottenereNomeFile                                         *
*                                                                    *
* DESCRIZIONE: ottiene il nome della voce letta all' interno di una  *
*              directory                                             *
*                                                                    *
*                                                                    *
* ARGOMENTI:                                                         * 
* voce: voce di cui si vuole sapere il nome, tipo file               *
*                                                                    *
* RITORNO:                                                           *
* nomeVoce: nome della voce, stringa                                 *
**********************************************************************/
const char* ottenereNomeFile(struct dirent* voce) {
    const char* nomeVoce = voce->d_name;
    return nomeVoce;
}

/********************************************************
* FUNZIONE: raccogliereNomiPartiteSalvate                *
*                                                        *
* DESCRIZIONE: Scansiona la cartella "database" per      *
*              trovare file che iniziano con "partita_"  *
*              e le salva in un array statico            *
* ARGOMENTI:                                             *
* - nomiPartite: array statico di stringhe dove salvare  *
*   i nomi dei file.                                     *
*                                                        *
* RITORNO:                                               *
* Nessuno (l'array viene riempito direttamente)         *
*********************************************************/
void raccogliereNomiPartiteSalvate(char nomiPartite[][MAX_NOME_FILE]) {
    DIR *cartella; 
    struct dirent *voce;
    int conteggio;
    const char *nomeFile;

    conteggio = 0;
    cartella = opendir("database");
    voce = leggereProssimaVoce(cartella);
    while (voce != NULL && conteggio < MAX_PARTITE) {
        nomeFile = ottenereNomeFile(voce);
        
        if (confrontarePrefisso(nomeFile, "partita_") == VERO) {
            strcpy(nomiPartite[conteggio], nomeFile);
            conteggio = conteggio + 1;
        }
    voce = leggereProssimaVoce(cartella);
    }
    closedir(cartella);
}

/********************************************************
* FUNZIONE: contareNumeroPartiteSalvate                  *
*                                                        *
* DESCRIZIONE: Scansiona la cartella "database" per      *
*              trovare file che iniziano con "partita_"  *
*              e conta quante ce ne sono.                *
*                                                        *
* ARGOMENTI:                                             *
* Nessuno                                                *
*                                                        *
* RITORNO:                                               *
* - conteggio: numero di file rilevati;                  *
*        0 se la cartella non esiste o in caso di errore *
*********************************************************/
int contareNumeroPartiteSalvate() {
    DIR *cartella; 
    struct dirent *voce;
    int conteggio;
    const char *nomeFile;

    conteggio = 0;
    cartella = opendir("database");
    voce = leggereProssimaVoce(cartella);
    while (voce != NULL && conteggio < MAX_PARTITE) {
        nomeFile = ottenereNomeFile(voce);
        
        if (confrontarePrefisso(nomeFile, "partita_") == VERO) {
            conteggio = conteggio + 1;
        }
    voce = leggereProssimaVoce(cartella);
    }
    closedir(cartella);
    return conteggio;
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
* FUNZIONE: avviareMenuCaricaPartita                    *
*                                                       *
* DESCRIZIONE: Mostra l'elenco delle partite salvate    *
*              presenti nella cartella "database",      *
*              consente all'utente di scegliere una     *
*              partita da caricare digitando il nome    *
*              o il numero corrispondente.              *
*                                                       *
* COMPORTAMENTO:                                        *
* - Se non ci sono partite salvate, l'utente viene      *
* - L'utente può digitare "0" per tornare al menu       *
*   principale.                                         *
* - Se la partita esiste ed è caricabile, viene avviata.*
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Nessuno (effetto collaterale: avvia una      *
*          partita oppure torna alla homepage)          *
*                                                       *
********************************************************/
void avviareMenuCaricaPartita() {
  char nomiPartite[MAX_PARTITE][MAX_NOME_FILE];
  int numeroPartite;
  char input[128];
  int scelta;
  int tornaHP;
  int cursPartite;
  char nomeVisualizzato[128];
  char percorso[256];
  Partita partita;
  char nome[128];

  pulireSchermo();
  stampareTitoloCaricaPartita();

  raccogliereNomiPartiteSalvate(nomiPartite);
  numeroPartite = contareNumeroPartiteSalvate();
  if (numeroPartite == 0) {
    stampareCentrato("Nessuna partita salvata.");
    tornareHomepage(&tornaHP, RIGA_ERRORE, COLONNA - 10);
    return;
  }
  printf("  [0] Torna al menu principale\n");

  cursPartite = 0;
  while (cursPartite < numeroPartite) {
    estrapolareNomeDaFile(nomiPartite[cursPartite], nomeVisualizzato);
    printf("  [%d] %s\n", cursPartite + 1, nomeVisualizzato);
    cursPartite = cursPartite + 1;
  }

  // Chiedi quale partita caricare
  printf("\n Scegli una partita: ");
  fgets(input, 128, stdin);

  if (*input == '0') {
    avviareMenuPrincipale(); 
  }
  
  //abbiamo dovuto mettere prima il controllo
  //perche' se l' utente digitava caratteri
  //atoi dava come risultato = 0 e quindi faceva
  //tornare al menu principale con input errato

  scelta = atoi(input);

  // Gestisci scelta
    if (scelta > 0 && scelta <= numeroPartite) {

    snprintf(percorso, sizeof(percorso), "database/%s", nomiPartite[scelta-1]);

    // Carica la partita
    caricarePartita(&partita, percorso);
    estrapolareNomeDaFile(nomiPartite[scelta-1], nome);
    scrivereNomePartita(&partita, nome);

    avviarePartitaContinuata(&partita);
  } else {
    avviareMenuCaricaPartita(); 
  }
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
********************************************************/
void salvareValoriGriglia(FILE *file, Partita *partita) {
    int riga; 
    int colonna;
    Griglia griglia; 
    int valGriglia;
    int dimensione;

    griglia = leggereGrigliaPartita(partita);
    dimensione = leggereDimGriglia(griglia);

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
*******************************************************/
void caricarePartita(Partita *partita, const char *percorso) {
    FILE *file; 
    int dimensione, difficolta;
    Impostazioni impostazioni;

    file = fopen(percorso, "r");
    
    fscanf(file, "%d %d", &dimensione, &difficolta);

    scrivereDimensioneImp(&impostazioni, dimensione);
    scrivereDifficoltaImp(&impostazioni, difficolta);

    inizializzareGrigliaPartita(partita, dimensione);

    caricareValoriGriglia(file, partita);

    fclose(file);
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
*******************************************************/
void salvarePartitaCorrente(Partita *partita) {
  char percorso[100]; 
  snprintf(percorso, sizeof(percorso), "database/partita_%s.txt", leggereNomePartita(partita));
  salvarePartita(partita, percorso);

    //utilizzare la funzione concatenareDueStringhe 
    //rallentava il programma 
    //e dava problemi con il salvataggio.
}


/**************************************************************
* FUNZIONE: estrapolareNomeFile                               * 
*                                                             *
* DESCRIZIONE: elimina il prefisso e il suffisso da nomeFile  *
*                                                             *
* ARGOMENTI:                                                  *
* nomeFile: nome da modificare, stringa                       *
* nome: nome modificato, stringa                              *
*                                                             *
* RITORNO:                                                    *
* nome: nome modificato, stringa                              *
***************************************************************/

void estrapolareNomeDaFile(const char *nomeFile, char *nome) {
    int cursNomeFile;
    int cursNome;

    cursNome = 0;
    cursNomeFile = 8;

    while(nomeFile[cursNomeFile] != '.') {
      nome[cursNome] = nomeFile[cursNomeFile];
      cursNomeFile = cursNomeFile + 1;
      cursNome = cursNome + 1;
    }
    nome[cursNome] = '\0';
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
* file: file aggiornato con i dati utili di partita    *
*******************************************************/

void salvarePartita(Partita *partita, const char *percorso) {
    FILE *file; 
    int dimensione;
    int difficolta;

    file = fopen(percorso, "w");

    dimensione = leggereDimGriglia(leggereGrigliaPartita(partita));
    difficolta = leggereDifficoltaImp(leggereImpPartita(*partita));

    fprintf(file, "%d %d\n", dimensione, difficolta);
    salvareValoriGriglia(file, partita);
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
* partita: partita aggiornata
*********************************************************/
void caricareValoriGriglia(FILE *file, Partita *partita) {
    int riga;
    int colonna;
    int val;
    int risultato;
    int dimensione;
    dimensione = leggereDimGriglia(leggereGrigliaPartita(partita));

    
    risultato = VERO;
    riga = 0;
    while (riga < dimensione && risultato == VERO) {
        colonna = 0;
        while (colonna < dimensione && risultato == VERO) {
            if (fscanf(file, "%d", &val) == 1) {
                scrivereValGrigliaPartita(partita, val, riga, colonna);
                colonna = colonna + 1;
            } else {
                risultato = FALSO;
            }
        }
        if (risultato == VERO) {
            riga = riga + 1;
        }
   }
}
