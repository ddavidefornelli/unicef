/*
AUTORI: Giuliano Antoniciello 
        Davide Fornelli
        Onofrio de Robertis

DATA INIZIO: 28/05/2025

NOME FILE: partita.c

Scopo delle funzioni presenti:
- avviarePartita: gestisce l'intero ciclo di gioco, dall'inizializzazione alla vittoria.
- mostraSchermo: stampa la schermata iniziale della partita in base alla dimensione.
- stampareTitoloPartita: stampa il titolo della partita.
- stampareVittoria: mostra il messaggio finale di vittoria.
- stampareTabellaInput: disegna la tabella per l'inserimento di riga, colonna e valore.
- disegnareCornice: stampa la cornice decorativa per l'input utente.
- convertireDimensione: converte un input numerico in dimensione reale della griglia (4, 9, 16).
- rimuovereNumeri: rimuove celle dalla griglia in base alla difficoltà scelta.
- calcolareCelleDaRimuovere: calcola la percentuale di celle da rimuovere in base alla difficoltà.
- verificareValidita: verifica se un numero può essere inserito in una cella (riga, colonna, quadrato).
- verificareRiga: controlla se un numero è già presente nella riga.
- verificareColonna: controlla se un numero è già presente nella colonna.
- verificareSottoquadrato: controlla se un numero è già presente nel quadrato interno.
- riempireGriglia: riempie ricorsivamente la griglia con una soluzione valida.
- trovareCellaVuota: trova una cella ancora vuota nella griglia.
- generareSudoku: genera una griglia completa e ne rimuove celle in base alla difficoltà.
- stampareGrigliaPartita: gestisce la stampa completa della griglia di gioco.
- calcolareSottoquadrato: calcola la dimensione del sotto-quadrato in base alla dimensione totale.
- stampareIntestazioneColonne: stampa l'intestazione delle colonne numerate.
- stampareLineaOrizzontale: stampa una riga di separazione tra righe della griglia.
- stampareRigheGriglia: stampa tutte le righe della griglia.
- stampareRigaGriglia: stampa una singola riga della griglia.
- collezionareInput: raccoglie input utente con controlli di validità e messaggi d'errore.
- controllareGrigliaPiena: verifica se tutte le celle della griglia sono state riempite.
- salvarePartitaCorrente: salva lo stato attuale della partita su file.
- salvarePartita: scrive su file tutti i dati della partita.
- caricaPartita: carica una partita precedentemente salvata da file.
- caricaValoriGriglia: legge e carica i valori della griglia da file.
- avviarePartitaContinuata: permette di continuare una partita precedentemente salvata.
                    su riga, colonna e sottoquadrato(verificareRiga, verificareColonna, verificareSottoquadrato), per avere un codice più leggibile e modulare

Nel giorno 18/06/25, Giuliano Antoniciello ha inserito la funziona: calcolareSottoquadrato() per calcolare dinamicamente la dimensione del quadrante in base alla dimensione della griglia.
                    In questo modo il codice è più dinamico e flessibile.

Nel giorno 20/06/25, Giuliano Antoniciello ha inserito le funzioni per il salvataggio e caricamento partita (salvarePartita, caricaPartita), per permettere di interrompere e riprendere 
                    una partita in momenti successivi

Nel giorno 20/06/25, Michele Amato ha inserito la funzione: stampareGrigliaPartita() per aumentare la leggibilità della griglia sul terminale

Nel giorno 21/06/25, Giuliano Antoniciello e Davide Fornelli hanno aggiornato le funzioni: collezionareInput(), riempireGriglia() e mostraSchermo() per rendere il codice più compatto
                    e metterlo al sicuro da eventuali arresti anomali
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/funzioniUtilita.h"
#include "../include/tipiDiDato.h"
#include "../include/partita.h"
#include "../include/CaricaPartita.h"

#include "../include/homepage.h"

#define RIGA_INPUT_RIGA 13
#define RIGA_INPUT_COLONNA 16
#define RIGA_INPUT_VALORE 19
#define RIGA_INPUT 28
#define COLONNA_INPUT 67
#define CELLA_VUOTA 0
#define FALSO 0
#define VERO 1
#define DIFFICOLTA_FACILE 1
#define DIFFICOLTA_MEDIA 2
#define DIFFICOLTA_DIFFICILE 3
#define RIGA_ERRORE 22
#define COLONNA_ERRORE 27
#define SALVA_PARTITA 31
#define TORNA_MENU 29
#define RIGA_INIZIO_CORNICE -4

#define BLU "\033[34m"
#define RESET "\033[0m"


/*******************************************************
* FUNZIONE: avviarePartita                             *
*                                                      *
* DESCRIZIONE: Avvia una nuova partita di Sudoku,      *
*              gestendo la logica di gioco fino alla   *
*              sua conclusione.                        *
*                                                      *
* ARGOMENTI:                                           *
* inputNome: nome della partita (stringa)              *
* inputDifficolta: livello di difficoltà               *
* inputDimensione: dimensione della griglia            *
*                                                      *
* RITORNO: permette all'utente di giocare al Sudoku    *
*******************************************************/
void avviarePartita(const char *inputNome, Impostazioni impostazioni) {
    int grigliaPiena;
    int valido;
    int errore;
    Griglia griglia; 
    Partita partita;
    int valDaInserire, riga, colonna;
    int sceltaAzione;
    int dimensione;

    grigliaPiena = FALSO;
    valido = FALSO;
    errore = FALSO;

    dimensione = leggereDimGrigliaImp(impostazioni);

    inizializzareGrigliaPartita(&partita, dimensione);
    scrivereNomePartita(&partita, (char *)inputNome);
    convertireDimensione(&dimensione);

    scrivereDimensioneImp(&impostazioni, dimensione);

    generareSudoku(&partita, impostazioni);

    while (grigliaPiena == FALSO) {
        mostraSchermo(dimensione);
        stampareGrigliaPartita(&partita);
        stampareTabellaInput();

        if (errore == VERO) {
            mostrareMessaggioErrore("Inserisci valori corretti", RIGA_ERRORE + 2, COLONNA_ERRORE);
            errore = FALSO;
        }

        spostareCursore(RIGA_INPUT - 18, COLONNA_INPUT );
        printf(">> ");
        scanf("%d", &sceltaAzione);
        pulireBuffer();

        if (sceltaAzione == 1) {
            griglia = leggereGrigliaPartita(&partita);
            collezionareInput(&griglia, &riga, RIGA_INPUT_RIGA);
            collezionareInput(&griglia, &colonna, RIGA_INPUT_COLONNA);
            collezionareInput(&griglia, &valDaInserire, RIGA_INPUT_VALORE);

            if (leggereValGriglia(griglia, riga - 1, colonna - 1) != 0) {
                errore = VERO;
            } else {
                valido = verificareValidita(&griglia, riga - 1, colonna - 1, valDaInserire);
                if (valido == VERO) {
                    scrivereValGrigliaPartita(&partita, valDaInserire, riga - 1, colonna - 1);
                    grigliaPiena = controllareGrigliaPiena(leggereGrigliaPartita(&partita));
                } else {
                    errore = VERO;
                }
            }
        } else if (sceltaAzione == 2) {
            salvarePartitaCorrente(&partita);
        } else if (sceltaAzione == 3) {
            avviareMenuPrincipale();
            return;
        } 
    }
    stampareVittoria();
}


/*******************************************************
* FUNZIONE: mostraSchermo                              *
*                                                      *
* DESCRIZIONE: Pulisce lo schermo e, se la dimensione  *
*              non è 16, stampa anche il titolo del    *
*              gioco.                                  *
*                                                      *
* ARGOMENTI:                                           *
* dimensione: dimensione della griglia di gioco        *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void mostraSchermo(int dimensione) {
    if (dimensione != 16) {
        stampareTitoloPartita();
    } else {
        pulireSchermo();
        printf("\n");
    }
}


/*******************************************************
* FUNZIONE: stampareTitoloPartita                      *
*                                                      *
* DESCRIZIONE: Pulisce lo schermo e stampa il titolo   *
*              artistico del gioco in formato ASCII,   *
*              centrato e colorato.                    *
*                                                      *
* ARGOMENTI: Nessuno                                   *
*                                                      *
* RITORNO: Titolo stampato al centro del terminale     *
*******************************************************/
void stampareTitoloPartita() {
    printf(BLU);
    pulireSchermo();
    printf("\n");
    stampareCentrato("                    _   _ _              ");
    stampareCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ");
    stampareCentrato("|___|  | . | .'|  _|  _| |  _| .'|  |___|");
    stampareCentrato("       |  _|__,|_| |_| |_|_| |__,|       ");
    stampareCentrato("       |_|                               ");
    printf("\n");
    printf(RESET);
}


/*********************************************************
* FUNZIONE: stampareVittoria                             *
*                                                        *
* DESCRIZIONE: Pulisce lo schermo e stampa a video un    *
*              messaggio di vittoria.                    *
*                                                        *
* ARGOMENTI: Nessuno                                     *
*                                                        *
* RITORNO: Terminale aggiornato con la stampa del titolo *
*********************************************************/
void stampareVittoria() {
    int input;
    pulireSchermo();
    printf("\n\n\n");

    stampareCentrato(" _   _    _    ___ ");
    stampareCentrato("| | | |  / \\  |_ _|");
    stampareCentrato("| |_| | / _ \\  | | ");
    stampareCentrato("|  _  |/ ___ \\ | | ");
    stampareCentrato("|_| |_/_/   \\_\\___|");
    printf("\n\n");

    stampareCentrato("__     _____ _   _ _____ ___  ");
    stampareCentrato("\\ \\   / /_ _| \\ | |_   _/ _ \\ ");
    stampareCentrato(" \\ \\ / / | ||  \\| | | || | | |");
    stampareCentrato("  \\ V /  | || |\\  | | || |_| |");
    stampareCentrato("   \\_/  |___|_| \\_| |_| \\___/ ");
    tornareHomepage(&input, RIGA_INPUT - 10, 30);
}


/*******************************************************
* FUNZIONE: stampareTabellaInput                       *
*                                                      *
* DESCRIZIONE: Disegna la cornice e stampa la tabella  *
*              con le etichette per l'inserimento di   *
*              riga, colonna e valore. Mostra anche le *
*              istruzioni per salvare o tornare alla   *
*              homepage.                               *
*                                                      *
* ARGOMENTI: Nessuno                                   *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void stampareTabellaInput() {
    disegnareCornice();
    
    spostareCursore(RIGA_INPUT_RIGA - 4, COLONNA_INPUT);
    printf("-Azione-");
    spostareCursore(RIGA_INPUT_RIGA - 1, COLONNA_INPUT + 1);
    printf("-Riga-");
    spostareCursore(RIGA_INPUT_COLONNA - 1, COLONNA_INPUT);
    printf("-Colonna-");
    spostareCursore(RIGA_INPUT_VALORE - 1, COLONNA_INPUT);
    printf("-Valore-");
    spostareCursore(25, 17);
    printf("\033[34m azione: (1 giocare / 2 salvare / 3 uscire)\033[0m");
}


/*******************************************************
* FUNZIONE: disegnareCornice                           *
*                                                      *
* DESCRIZIONE: Disegna a schermo una cornice grafica   *
*              per l'input, con intestazione e         *
*              spazio per riga, colonna e valore.      *
*                                                      *
* ARGOMENTI: Nessuno                                   *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void disegnareCornice() {
    int i; 
    
    spostareCursore(RIGA_INPUT_RIGA - 5, COLONNA_INPUT - 2);
    printf("+------------+\n");
    spostareCursore(RIGA_INPUT_RIGA - 6, COLONNA_INPUT - 2);
    printf("|   Input    |\n");
    spostareCursore(RIGA_INPUT_RIGA - 7, COLONNA_INPUT - 2);
    printf("+------------+\n");
    
    i = RIGA_INIZIO_CORNICE;
    while (i < 8) {
        spostareCursore(RIGA_INPUT_RIGA + i, COLONNA_INPUT - 2);
        printf("|            |\n");
        i = i + 1;
    }
    
    spostareCursore(RIGA_INPUT_RIGA + 7, COLONNA_INPUT - 2);
    printf("+------------+\n");
}


/*******************************************************
* FUNZIONE: convertireDimensione                       *
*                                                      *
* DESCRIZIONE: Converte un valore numerico associato   *
*              a una scelta dell'utente (1, 2 o 3)     *
*              nella dimensione effettiva della griglia*
*              (4, 9 o 16).                            *
*                                                      *
* ARGOMENTI:                                           *
* dimensione: puntatore alla dimensione scelta         *
*                                                      *
* RITORNO: valore di dimensione aggiornato             *
*******************************************************/
void convertireDimensione(int *dimensione) {
    if (*dimensione == 1) {
        *dimensione = 4;
    } else {
        if (*dimensione == 2) {
            *dimensione = 9;
        } else {
            if (*dimensione == 3) {
                *dimensione = 16;
            }
        }
    }
}


/********************************************************
* FUNZIONE: rimuovereNumeri                             *
*                                                       *
* DESCRIZIONE: Rimuove un certo numero di celle dalla   *
*              griglia del Sudoku, in base alla         *
*              difficoltà selezionata. Le celle vengono *
*              scelte casualmente.                      *
*                                                       *
* ARGOMENTI:                                            *
* griglia: puntatore alla griglia di gioco              *
* dimensione: dimensione della griglia                  *
* difficolta: livello di difficoltà selezionato         *
*                                                       *
* RITORNO: griglia di gioco aggiornata                  *
********************************************************/
void rimuovereNumeri(Griglia *griglia, Impostazioni impostazioni) {
    srand(time(NULL));
    int cellaGriglia;
    int celleDaRimuovere; 
    int rimosse;
    int riga, colonna;
    int dimensione;

    dimensione = leggereDimGrigliaImp(impostazioni);
    
    rimosse = 0;
    cellaGriglia = dimensione * dimensione;
    celleDaRimuovere = cellaGriglia * calcolareCelleDaRimuovere(impostazioni) / 100;

    while (rimosse < celleDaRimuovere) {
        riga = rand() % dimensione; 
        colonna = rand() % dimensione;
        //l' utilizzo della funzione modulo rallenta troppo
        //l esecuzione del programma
        if (leggereValGriglia(*griglia, riga, colonna) != CELLA_VUOTA) {
            scrivereValGriglia(griglia, riga, colonna, CELLA_VUOTA);
            rimosse = rimosse + 1;
        }
    }
}


/*******************************************************
* FUNZIONE: calcolareCelleDaRimuovere                  *
*                                                      *
* DESCRIZIONE: Restituisce la percentuale di celle da  *
*              rimuovere in base alla difficoltà       *
*              scelta dall'utente.                     *
*                                                      *
* ARGOMENTI:                                           *
* difficolta: livello di difficoltà selezionato        *
*                                                      *
* RITORNO: Intero che rappresenta la percentuale di    *
*          celle da rimuovere                          *
*******************************************************/
int calcolareCelleDaRimuovere(Impostazioni impostazioni) {
    int difficolta;
    int risultato;

    difficolta = leggereDifficoltaImp(impostazioni);

    if(difficolta == DIFFICOLTA_FACILE)  {
        risultato = 20;
    } else if (difficolta == DIFFICOLTA_MEDIA) {
        risultato = 40;
    } else {
        risultato = 70;
    }
    return risultato;
}

/**********************************************************
* FUNZIONE: verificareValidita                            *
*                                                         *
* DESCRIZIONE: Verifica se un numero può essere           *
*              inserito in una specifica posizione        *
*              della griglia Sudoku, controllando la      *
*              validità rispetto a riga, colonna e        *
*              sottoquadrato.                             *
*                                                         *
* ARGOMENTI:                                              *
* griglia: puntatore alla struttura della griglia         *
* dimensione: dimensione della griglia                    *
* riga: indice della riga in cui inserire il numero       *
* colonna: indice della colonna in cui inserire il numero *
* numero: numero da inserire                              *
*                                                         *
* RITORNO:                                                *
* VERO se il numero può essere inserito senza violare     *
* le regole del Sudoku, FALSO altrimenti                  *
***********************************************************/

int verificareValidita(Griglia *griglia, int riga, int colonna, int numero) {
    int risultato;

    risultato = VERO;
    if (verificareRiga(griglia, riga, numero) == FALSO) {
        risultato = FALSO;
    } else {
        if (verificareColonna(griglia, colonna, numero) == FALSO) {
            risultato = FALSO;
        } else {
            if (verificareSottoquadrato(griglia, riga, colonna, numero) == FALSO) {
                risultato = FALSO;
            }
        }
    }
    return risultato;
}


/*******************************************************
* FUNZIONE: verificareRiga                             *
*                                                      *
* DESCRIZIONE: Controlla se un numero è già presente   *
*              in una specifica riga della griglia     *
*              Sudoku.                                 *
*                                                      *
* ARGOMENTI:                                           *
* griglia: puntatore alla struttura della griglia      *
* dimensione: dimensione della griglia                 *
* riga: indice della riga da controllare               *
* numero: numero da cercare nella riga                 *
*                                                      *
* RITORNO:                                             *
* VERO se il numero non è presente nella riga,         *
* FALSO se invece è già presente                       *
*******************************************************/
int verificareRiga(Griglia *griglia, int riga, int numero) {
    int cursColonna; 
    int risultato; 
    int dimensione;
    
    dimensione = leggereDimGriglia(*griglia);

    cursColonna = 0;
    risultato = VERO;
    
    while (cursColonna < dimensione && risultato == VERO) {
        if (leggereValGriglia(*griglia, riga, cursColonna) == numero) {
            risultato = FALSO;
        } else {
            cursColonna = cursColonna + 1;
        }
    }
    return risultato;
}


/*******************************************************
* FUNZIONE: verificareColonna                          *
*                                                      *
* DESCRIZIONE: Controlla se un numero è già presente   *
*              in una specifica colonna della griglia  *
*              Sudoku.                                 *
*                                                      *
* ARGOMENTI:                                           *
* griglia: puntatore alla struttura della griglia      *
* dimensione: dimensione della griglia                 *
* colonna: indice della colonna da controllare         *
* numero: numero da cercare nella colonna              *
*                                                      *
* RITORNO:                                             *
* VERO se il numero non è presente nella colonna,      *
* FALSO se invece è già presente                       *
*******************************************************/
int verificareColonna(Griglia *griglia, int colonna, int numero) {
    int cursRiga;
    int risultato;
    int dimensione;

    risultato = VERO;
    cursRiga = 0;
    dimensione = leggereDimGriglia(*griglia);

    while (cursRiga < dimensione && risultato == VERO) {
        if (leggereValGriglia(*griglia, cursRiga, colonna) == numero) {
            risultato = FALSO;
        } else {
            cursRiga = cursRiga + 1;
        }
    }
    return risultato;
}


/**********************************************************
* FUNZIONE: verificareSottoquadrato                        *
*                                                          *
* DESCRIZIONE: Controlla se un numero è già presente       *
*              nel sottoquadrato (blocco) della griglia    *
*              Sudoku corrispondente alla posizione        *
*              specificata da riga e colonna.              *
*                                                          *
* ARGOMENTI:                                               *
* griglia: puntatore alla struttura della griglia          *
* dimensione: dimensione della griglia                     *
* riga: indice della riga della cella da controllare       *
* colonna: indice della colonna della cella da controllare *
* numero: numero da cercare nel sottoquadrato              *
*                                                          *
* RITORNO:                                                 *
* VERO se il numero non è presente nel sottoquadrato,      *
* FALSO se invece è già presente                           *
***********************************************************/
int verificareSottoquadrato(Griglia *griglia, int riga, int colonna, int numero) {
    int dimensioneSottoquadrato;
    int inizioRiga;
    int inizioColonna;
    int cursRiga;
    int cursColonna; 
    int risultato; 

    dimensioneSottoquadrato= calcolareSottoquadrato(leggereDimGriglia(*griglia));;
    inizioRiga  = riga - modulo(riga, dimensioneSottoquadrato);
    risultato = VERO;
    inizioColonna = colonna - modulo(colonna, dimensioneSottoquadrato);

    cursRiga = 0;
    while (cursRiga < dimensioneSottoquadrato && risultato == VERO) {
        cursColonna = 0;
        while (cursColonna < dimensioneSottoquadrato && risultato == VERO) {
            if (leggereValGriglia(*griglia, cursRiga + inizioRiga, cursColonna + inizioColonna) == numero) {
                risultato = FALSO;
            } else {
                cursColonna = cursColonna + 1;
            }
        }
        if (risultato == VERO) {
            cursRiga = cursRiga + 1;
        }
    }
    return risultato;
}



/*******************************************************
* FUNZIONE: riempireGriglia                            *
*                                                      *
* DESCRIZIONE: Riempie ricorsivamente la griglia       *
*              Sudoku utilizzando backtracking,        *
*              cercando di inserire numeri validi      *
*              in celle vuote fino al completamento.   *
*                                                      *
* ARGOMENTI:                                           *
* griglia: puntatore alla struttura della griglia      *
* dimensione: dimensione della griglia                 *
*                                                      *
* RITORNO:                                             *
* VERO se la griglia è stata riempita correttamente,   *
* FALSO se non è possibile completare la griglia       *
*******************************************************/
int riempireGriglia(Griglia *griglia) {
    int cursRiga;
    int cursColonna;
    int cellaVuota;
    int grigliaPiena;
    int cursNumProva;
    int valDaInserire;
    int dimensione;

    dimensione = leggereDimGriglia(*griglia);

    int numeriDaProvare[dimensione];
    grigliaPiena = FALSO;
    cellaVuota = trovareCellaVuota(griglia);
    
    if (cellaVuota == FALSO) {
        grigliaPiena = VERO;
    } else {
        cellaVuota = cellaVuota - 1;
        cursRiga = cellaVuota / dimensione;
        cursColonna = modulo(cellaVuota, dimensione);
        
        cursNumProva = 0;
        while (cursNumProva < dimensione) {
            numeriDaProvare[cursNumProva] = cursNumProva + 1;
            cursNumProva = cursNumProva + 1;
        }
        
        mescolareArray(numeriDaProvare, dimensione);

        cursNumProva = 0;
        while (cursNumProva < dimensione && grigliaPiena == FALSO) {
            valDaInserire = numeriDaProvare[cursNumProva];
            if (verificareValidita(griglia, cursRiga, cursColonna, valDaInserire) == VERO) {
                scrivereValGriglia(griglia, cursRiga, cursColonna, valDaInserire);
                if (riempireGriglia(griglia) == VERO) {
                    grigliaPiena = VERO;
                } else {
                    scrivereValGriglia(griglia, cursRiga, cursColonna, CELLA_VUOTA);
                }
            }
            if (grigliaPiena == FALSO) {
                cursNumProva = cursNumProva + 1;
            }
        }
    }
    return grigliaPiena;
}

/*******************************************************
* FUNZIONE: trovareCellaVuota                          *
*                                                      *
* DESCRIZIONE: Cerca la prima cella vuota (valore 0)   *
*              nella griglia Sudoku, e ne restituisce  *
*              la posizione tramite i puntatori riga e *
*              colonna.                                *
*                                                      *
* ARGOMENTI:                                           *
* griglia: puntatore alla struttura della griglia      *
* dimensione: dimensione della griglia                 *
* riga: puntatore a intero per memorizzare l'indice    *
*       della riga della cella vuota                   *
* colonna: puntatore a intero per memorizzare l'indice *
*         della colonna della cella vuota              *
*                                                      *
* RITORNO:                                             *
* VERO se è stata trovata una cella vuota,             *
* FALSO se non ci sono celle vuote                     *
*******************************************************/
int trovareCellaVuota(Griglia *griglia) {
    int cursRiga;
    int cursColonna;
    int risultato;
    int trovata;
    int dimensione;

    dimensione = leggereDimGriglia(*griglia);
    trovata = FALSO;
    cursRiga = 0;
    risultato = 0;
    while (cursRiga < dimensione && trovata == FALSO) {
        cursColonna = 0;
        while (cursColonna < dimensione && trovata == FALSO) {
            if (leggereValGriglia(*griglia, cursRiga, cursColonna) == 0) {
                risultato = cursRiga * dimensione + cursColonna + 1;
                trovata = VERO;
            } else {
                cursColonna = cursColonna + 1;
            }
        }
        if (trovata == FALSO) {
            cursRiga = cursRiga + 1;
        }
    }
    return risultato;
}


/*********************************************************
* FUNZIONE: generareSudoku                               *
*                                                        *
* DESCRIZIONE: Genera una nuova griglia Sudoku           *
*              completa e ne rimuove alcuni numeri       *
*              in base al livello di difficoltà scelto.  *
*                                                        *
* ARGOMENTI:                                             *
* partita: puntatore alla struttura partita che contiene *
*          la griglia Sudoku                             *
* dimensione: dimensione della griglia                   *
* difficolta: livello di difficoltà che determina quanti *
*            numeri verranno rimossi                     *
*                                                        *
* RITORNO: partita aggiornata con la griglia di gioco    *
*          creata                                        *
*********************************************************/
void generareSudoku(Partita *partita,  Impostazioni impostazioni){
    Griglia griglia = leggereGrigliaPartita(partita);

    riempireGriglia(&griglia);
    rimuovereNumeri(&griglia, impostazioni);
}


/*******************************************************
* FUNZIONE: stampareGrigliaPartita                      *
*                                                       *
* DESCRIZIONE: Stampa a video la griglia Sudoku         *
*              corrente della partita, includendo       *
*              intestazioni di colonna e linee          *
*              orizzontali per una migliore leggibilità *
*                                                       *
* ARGOMENTI:                                            *
* partita: puntatore alla struttura della partita       *
*                                                       *
* RITORNO: Terminale aggiornato                         *
*                                                       *
********************************************************/
void stampareGrigliaPartita(Partita *partita) {
    Griglia griglia; 
    int dimensione; 
    int numeroSottoquadrato;

    griglia = leggereGrigliaPartita(partita);
    dimensione = leggereDimGriglia(griglia);
    numeroSottoquadrato = calcolareSottoquadrato(dimensione);

    stampareIntestazioneColonne(dimensione, numeroSottoquadrato);
    stampareLineaOrizzontale(dimensione, numeroSottoquadrato);
    stampareRigheGriglia(griglia);
    stampareLineaOrizzontale(dimensione, numeroSottoquadrato);
}


/********************************************************
* FUNZIONE: calcolareSottoquadrato                       *
*                                                        *
* DESCRIZIONE: Calcola la dimensione del sottoquadrato   *
*              (blocco) di una griglia Sudoku            *
*              in base alla dimensione totale della      *
*              griglia.                                  *
*                                                        *
* ARGOMENTI:                                             *
* dimensione: dimensione della griglia Sudoku            *
*                                                        *
* RITORNO:                                               *
* Intero che rappresenta la dimensione del sottoquadrato *
* (ad esempio, 3 per una griglia 9x9, 4 per 16x16)       *
*********************************************************/
int calcolareSottoquadrato(int dimensione) {
    int risultato;

    risultato = 2;
    if (dimensione == 9) {
        risultato = 3;
    } else {
        if (dimensione == 16) {
            risultato = 4;
        }
    }
    return risultato;
}


/*******************************************************
* FUNZIONE: stampareIntestazioneColonne                 *
*                                                       *
* DESCRIZIONE: Stampa l'intestazione delle colonne      *
*              numerate della griglia Sudoku,           *
*              formattando gli spazi in base alla       *
*              dimensione e alla dimensione del         *
*              sottoquadrato per una migliore           *
*              leggibilità.                             *
*                                                       *
* ARGOMENTI:                                            *
* dimensione: numero totale di colonne della griglia    *
* numeroSottoquadrato: dimensione del sottoquadrato     *
*                                                       *
* RITORNO: Terminale aggiornato                         *
********************************************************/
void stampareIntestazioneColonne(int dimensione, int numeroSottoquadrato) {
    int j;

    j = 0;
    printf("    ");
    while (j < dimensione) {
        if (dimensione == 16 && j + 1 < 10) {
            printf("  %d", j + 1);
        } else {
            printf("%3d", j + 1);
        }
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
            printf("  ");
        }
        j = j + 1;
    }
    printf("\n");
}


/*******************************************************
* FUNZIONE: stampareLineaOrizzontale                   *
*                                                      *
* DESCRIZIONE: Stampa una linea orizzontale            *
*              formattata per separare i sottoquadrati *
*              nella griglia Sudoku durante la stampa. *
*                                                      *
* ARGOMENTI:                                           *
* dimensione: dimensione della griglia                 *
* numeroSottoquadrato: dimensione del sottoquadrato    *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void stampareLineaOrizzontale(int dimensione, int numeroSottoquadrato) {
    int j;
    j = 0;
    printf("   +");
    while (j < dimensione) {
        printf("---");
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
            printf("-+");
        }
        j = j + 1;
    }
    printf("-+\n");
}


/*******************************************************
* FUNZIONE: stampareRigheGriglia                       *
*                                                      *
* DESCRIZIONE: Stampa tutte le righe della griglia     *
*              Sudoku, separando i sottoquadrati con   *
*              linee orizzontali per una migliore      *
*              leggibilità.                            *
*                                                      *
* ARGOMENTI:                                           *
* griglia: struttura della griglia Sudoku              *
* dimensione: dimensione della griglia                 *
* numeroSottoquadrato: dimensione del sottoquadrato    *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void stampareRigheGriglia(Griglia griglia) {
    int i;
    int dimensione;
    int numeroSottoquadrato;

    dimensione = leggereDimGriglia(griglia);
    numeroSottoquadrato = calcolareSottoquadrato(dimensione);

    i = 0;
    while (i < dimensione) {
        stampareRigaGriglia(griglia, i);
        
        if ((i + 1) % numeroSottoquadrato == 0 && i != dimensione - 1) {
            stampareLineaOrizzontale(dimensione, numeroSottoquadrato);
        }
        i = i + 1;
    }
}


/*******************************************************
* FUNZIONE: stampareRigaGriglia                        *
*                                                      *
* DESCRIZIONE: Stampa una singola riga della griglia   *
*              Sudoku, visualizzando i numeri o un     *
*              punto ('.') per celle vuote, con        *
*              separatori per i sottoquadrati.         *
*                                                      *
* ARGOMENTI:                                           *
* griglia: struttura della griglia Sudoku              *
* dimensione: dimensione della griglia                 *
* numeroSottoquadrato: dimensione del sottoquadrato    *
* riga: indice della riga da stampare                  *
*                                                      *
*******************************************************/
void stampareRigaGriglia(Griglia griglia, int riga) {
    int j; 
    int valore;
    int dimensione;
    int numeroSottoquadrato;

    dimensione = leggereDimGriglia(griglia);
    numeroSottoquadrato = calcolareSottoquadrato(dimensione);


    
    j = 0;
    if (dimensione == 16) {
        printf("%2d |", riga + 1);
    } else {
        printf("%2d |", riga + 1);
    }
    
    while (j < dimensione) {
        valore = leggereValGriglia(griglia, riga, j);
        if (valore == 0) {
            printf("  .");
        } else {
            printf("%3d", valore);
        }
        
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
            printf(" |");
        }
        j = j + 1;
    }
    printf(" |\n");
}


/*******************************************************
* FUNZIONE: collezionareInput                             *
*                                                       *
* DESCRIZIONE: Gestisce la raccolta sicura di un        *
*              input numerico da tastiera, effettuando  *
*              controlli di validità e fornendo         *
*              messaggi di errore fino a ottenere un    *
*              valore corretto o l'uscita al menu       *
*              principale.                              *
*                                                       *
* ARGOMENTI:                                            *
* partita: puntatore alla struttura della partita       *
* griglia: puntatore alla struttura della griglia       *
* inputRiga: puntatore a intero dove memorizzare        *
*           l'input acquisito                           *
* posRiga: posizione verticale dello spazio di input    *
*          nella UI (per la gestione dei messaggi)      *
*                                                       *
* RITORNO:                                              *
* Valore intero inserito dall'utente, se valido, o      *
* attivazione del menu principale in caso di input      *
* speciale (32).                                        *
********************************************************/
int collezionareInput(Griglia *griglia, int *input, int rigaTerminale) {
    int valida;
    int inputOk;

    valida = FALSO;
    while (valida == FALSO) {
        reimpostareZonaInput(rigaTerminale, COLONNA_INPUT);
        inputOk = FALSO;

        while (inputOk == FALSO) {
            if (scanf("%d", input) == 1) {
                // non utilizziamo la funzione eUnNumero
                // perche' ci da problemi con il formato dell' input
                inputOk = VERO;
            } else {
                pulireBuffer();
                reimpostareZonaInput(rigaTerminale, COLONNA_INPUT);
                mostrareMessaggioErrore("Digita un Numero", RIGA_ERRORE + 2, COLONNA_ERRORE);
                reimpostareZonaInput(rigaTerminale, COLONNA_INPUT);
            }
        }

        pulireBuffer();

        if (*input < 1 || *input > leggereDimGriglia(*griglia)) {
            mostrareMessaggioErrore("Numero fuori intervallo", RIGA_ERRORE + 2, COLONNA_ERRORE);
            reimpostareZonaInput(rigaTerminale, COLONNA_INPUT);
        } else {
            valida = VERO;
        }
    }
    return *input;
}

/*******************************************************
* FUNZIONE: controllareGrigliaPiena                    *
*                                                      *
* DESCRIZIONE: Verifica se la griglia Sudoku è         *
*              completamente riempita, cioè se non ci  *
*              sono celle vuote (valore 0).            *
*                                                      *
* ARGOMENTI:                                           *
* griglia: struttura della griglia Sudoku              *
*                                                      *
* RITORNO:                                             *
* VERO se la griglia è piena,                          *
* FALSO se esiste almeno una cella vuota               *
*******************************************************/
int controllareGrigliaPiena(Griglia griglia) {
    int dimensione;
    int cursRiga;
    int cursColonna; 
    int esito;

    esito = VERO;
    dimensione = leggereDimGriglia(griglia);
    cursRiga = 0;

    while (cursRiga < dimensione && esito == VERO) {
        cursColonna = 0;
        while (cursColonna < dimensione && esito == VERO) {
            if (leggereValGriglia(griglia, cursRiga, cursColonna) == 0) {
                esito = FALSO;
            } else {
                cursColonna = cursColonna + 1;
            }
        }
        if (esito == VERO) {
            cursRiga = cursRiga + 1;
        }
    }
    return esito;
}



/*************************************************************
* FUNZIONE: avviarePartitaContinuata                          *
*                                                             *
* DESCRIZIONE: Gestisce il ciclo di gioco di una              *
*              partita Sudoku già iniziata,                   *
*              permettendo all'utente di inserire             *
*              valori, salvare la partita e controllare       *
*              la validità delle mosse fino al completamento. *
*                                                             *
* ARGOMENTI:                                                  *
* partita: puntatore alla struttura della partita             *
*                                                             *
* RITORNO: permette all'utente di giocare                     *
*************************************************************/
void avviarePartitaContinuata(Partita *partita) {
    Griglia griglia;
    int dimensione;
    int valore, riga, colonna;
    int grigliaPiena;
    int valido;
    int errore;
    int sceltaAzione;

    dimensione = leggereDimGriglia(leggereGrigliaPartita(partita));
    grigliaPiena = FALSO;
    valido = FALSO;
    errore = FALSO;

    while (grigliaPiena == FALSO) {
        mostraSchermo(dimensione);
        stampareGrigliaPartita(partita);
        stampareTabellaInput();

        if (errore == VERO) {
            mostrareMessaggioErrore("Inserisci valori corretti", RIGA_ERRORE + 2, COLONNA_ERRORE);
            errore = FALSO;
        }

        spostareCursore(RIGA_INPUT - 18, COLONNA_INPUT );
        printf(">> ");
        scanf("%d", &sceltaAzione);
        pulireBuffer();

        if (sceltaAzione == 1) {
            griglia = leggereGrigliaPartita(partita);
            collezionareInput(&griglia, &riga, RIGA_INPUT_RIGA);
            collezionareInput(&griglia, &colonna, RIGA_INPUT_COLONNA);
            collezionareInput(&griglia, &valore, RIGA_INPUT_VALORE);

            valido = verificareValidita(&griglia, riga - 1, colonna - 1, valore);
            if (valido == VERO) {
                scrivereValGrigliaPartita(partita, valore, riga - 1, colonna - 1);
                grigliaPiena = controllareGrigliaPiena(leggereGrigliaPartita(partita));
            } else {
                errore = VERO;
            }
        } else if (sceltaAzione == 2) {
            salvarePartitaCorrente(partita);
        } else if (sceltaAzione == 3) {
            avviareMenuPrincipale();
            return;
        } 
    }
    stampareVittoria();
}
