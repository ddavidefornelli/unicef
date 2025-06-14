#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "interfaccia_util.h"
#include "tipiDiDato.h"
#include "partita.h"

// Costanti per le posizioni dell'interfaccia
#define INPUT_RIGA_NUMERO_RIGA     13
#define INPUT_RIGA_NUMERO_COLONNA  16
#define INPUT_RIGA_NUMERO_VALORE   19
#define INPUT_RIGA_BASE            28
#define INPUT_COLONNA_BASE         68
#define ERRORE_MESSAGGIO_RIGA      22
#define ERRORE_MESSAGGIO_COLONNA   27

// Costanti logiche
#define FALSO 0
#define VERO  1

// Costanti per le dimensioni del Sudoku
#define DIMENSIONE_PICCOLA  4
#define DIMENSIONE_MEDIA    9
#define DIMENSIONE_GRANDE   16

// Costanti per il numero di celle da rimuovere per difficoltà
#define CELLE_RIMUOVERE_FACILE_4x4   6
#define CELLE_RIMUOVERE_FACILE_9x9   40
#define CELLE_RIMUOVERE_FACILE_16x16 150

/**
 * Funzione principale per gestire il loop di gioco del Sudoku
 */
void loopPartita(int codiceDifficolta, int codiceDimensione) {
    // Dichiarazione variabili
    int inputUtente;
    Partita partitaCorrente;
    int numeroValoreInserito;
    int numeroRigaInserita;
    int numeroColonnaInserita;
    int grigliaCompletamenteRiempita;
    int inputValido;
    int errorePresente;
    Griglia grigliaGioco;

    // Inizializzazione variabili
    grigliaCompletamenteRiempita = FALSO;
    inputValido = FALSO;
    errorePresente = FALSO;

    // Inizializzazione partita
    inizializzareGrigliaPartita(&partitaCorrente, codiceDifficolta, codiceDimensione);
    convertiDifficoltaEDimensione(&codiceDifficolta, &codiceDimensione);
    generareSudoku(&partitaCorrente, codiceDimensione, codiceDifficolta);

    // Loop principale di gioco
    while (!grigliaCompletamenteRiempita) {
        // Visualizzazione interfaccia
        if (codiceDimensione != DIMENSIONE_GRANDE) {
            stampareTitoloPartita();
        } else {
            pulireSchermo();
            printf("\n\n");
        }
        
        stampareGrigliaPartita(&partitaCorrente);
        stampareInterfacciaInput();

        // Gestione messaggi di errore
        if (errorePresente) {
            mostrareMessaggioErrore("Inserisci i valori richiesti", 
                                  ERRORE_MESSAGGIO_RIGA + 2, 
                                  ERRORE_MESSAGGIO_COLONNA);
            errorePresente = FALSO;
        }

        // Raccolta input utente
        grigliaGioco = leggereGrigliaPartita(partitaCorrente);
        raccogliereDatiRiga(&grigliaGioco, &numeroRigaInserita);
        raccogliereDatiColonna(&grigliaGioco, &numeroColonnaInserita);
        raccogliereDatiValore(&grigliaGioco, &numeroValoreInserito);
        tornareHomepage(&inputUtente, ERRORE_MESSAGGIO_RIGA, ERRORE_MESSAGGIO_COLONNA);

        // Validazione e aggiornamento griglia
        inputValido = verificareValiditaMossa(&grigliaGioco, codiceDimensione, 
                                            numeroRigaInserita - 1, 
                                            numeroColonnaInserita - 1, 
                                            numeroValoreInserito);
        
        if (inputValido) {
            scrivereValGrigliaPartita(&partitaCorrente, numeroValoreInserito, 
                                    numeroRigaInserita - 1, numeroColonnaInserita - 1);
            grigliaCompletamenteRiempita = controllareSeLaGrigliaECompleta(leggereGrigliaPartita(partitaCorrente));
        } else {
            errorePresente = VERO;
        }
    }

    stampareSchermataDiVittoria();
}

/**
 * Stampa il titolo principale della partita
 */
void stampareTitoloPartita() {
    pulireSchermo();
    printf("\n");
    stampareCentrato("                    _   _ _              ");
    stampareCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ");
    stampareCentrato("|___|  | . | .'|  _|  _| |  _| .'|  |___|");
    stampareCentrato("       |  _|__,|_| |_| |_|_| |__,|       ");
    stampareCentrato("       |_|                               ");
}

/**
 * Stampa la schermata di vittoria
 */
void stampareSchermataDiVittoria() {
    int inputUtente;

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

    tornareHomepage(&inputUtente, INPUT_RIGA_BASE - 10, 30);
}

/**
 * Stampa l'interfaccia per l'input dell'utente
 */
void stampareInterfacciaInput() {
    int contatore;

    // Inizializzazione variabili
    contatore = 0;

    // Disegno del riquadro di input
    spostareCursore(INPUT_RIGA_NUMERO_RIGA - 2, INPUT_COLONNA_BASE - 2);
    printf("+------------+\n");
    spostareCursore(INPUT_RIGA_NUMERO_RIGA - 3, INPUT_COLONNA_BASE - 2);
    printf("|   Input    |\n");
    spostareCursore(INPUT_RIGA_NUMERO_RIGA - 4, INPUT_COLONNA_BASE - 2);
    printf("+------------+\n");

    // Disegno delle righe laterali del riquadro
    while (contatore < 8) {
        spostareCursore(INPUT_RIGA_NUMERO_RIGA - 1 + contatore, INPUT_COLONNA_BASE - 2);
        printf("|            |\n");
        contatore = contatore + 1;
    }

    spostareCursore(INPUT_RIGA_NUMERO_RIGA + 7, INPUT_COLONNA_BASE - 2);
    printf("+------------+\n");

    // Etichette per i campi di input
    spostareCursore(INPUT_RIGA_NUMERO_RIGA - 1, INPUT_COLONNA_BASE + 1);
    printf("-Riga-");
    spostareCursore(INPUT_RIGA_NUMERO_COLONNA - 1, INPUT_COLONNA_BASE);
    printf("-Colonna-");
    spostareCursore(INPUT_RIGA_NUMERO_VALORE - 1, INPUT_COLONNA_BASE);
    printf("-Valore-");
}

/**
 * Converte i codici di difficoltà e dimensione nei valori effettivi
 */
void convertiDifficoltaEDimensione(int *puntatoreDifficolta, int *puntatoreDimensione) {
    // Conversione difficoltà
    if (*puntatoreDifficolta == 1) {
        *puntatoreDifficolta = DIMENSIONE_PICCOLA;
    } else if (*puntatoreDifficolta == 2) {
        *puntatoreDifficolta = DIMENSIONE_MEDIA;
    } else if (*puntatoreDifficolta == 3) {
        *puntatoreDifficolta = DIMENSIONE_GRANDE;
    }

    // Conversione dimensione
    if (*puntatoreDimensione == 1) {
        *puntatoreDimensione = DIMENSIONE_PICCOLA;
    } else if (*puntatoreDimensione == 2) {
        *puntatoreDimensione = DIMENSIONE_MEDIA;
    } else if (*puntatoreDimensione == 3) {
        *puntatoreDimensione = DIMENSIONE_GRANDE;
    }
}

/**
 * Rimuove un numero specificato di celle dalla griglia per creare il puzzle
 */
void rimuovereNumeriDallaGriglia(Griglia *puntatoreGriglia, int dimensioneGriglia, int livelloDifficolta) {
    int numeroCelleDaRimuovere;
    int numeroCelleRimosse;
    int rigaCasuale;
    int colonnaCasuale;

    // Inizializzazione variabili
    numeroCelleRimosse = 0;

    // Determinazione del numero di celle da rimuovere in base alla difficoltà
    if (livelloDifficolta == DIMENSIONE_PICCOLA) {
        numeroCelleDaRimuovere = CELLE_RIMUOVERE_FACILE_4x4;
    } else if (livelloDifficolta == DIMENSIONE_MEDIA) {
        numeroCelleDaRimuovere = CELLE_RIMUOVERE_FACILE_9x9;
    } else if (livelloDifficolta == DIMENSIONE_GRANDE) {
        numeroCelleDaRimuovere = CELLE_RIMUOVERE_FACILE_16x16;
    }

    srand(time(NULL));

    // Rimozione casuale delle celle
    while (numeroCelleRimosse < numeroCelleDaRimuovere) {
        rigaCasuale = rand() % dimensioneGriglia;
        colonnaCasuale = rand() % dimensioneGriglia;

        if (leggereValGriglia(*puntatoreGriglia, rigaCasuale, colonnaCasuale) != 0) {
            scrivereValGriglia(puntatoreGriglia, rigaCasuale, colonnaCasuale, 0);
            numeroCelleRimosse = numeroCelleRimosse + 1;
        }
    }
}

/**
 * Verifica se una mossa è valida secondo le regole del Sudoku
 */
int verificareValiditaMossa(Griglia *puntatoreGriglia, int dimensioneGriglia, 
                           int rigaTarghet, int colonnaTarghet, int numeroInserito) {
    int indiceScorrimento;
    int risultatoValidazione;
    int dimensioneSottoquadrato;
    int rigaInizioSottoquadrato;
    int colonnaInizioSottoquadrato;
    int indiceRigaSottoquadrato;
    int indiceColonnaSottoquadrato;

    // Inizializzazione variabili
    indiceScorrimento = 0;
    risultatoValidazione = VERO;

    // Controllo validità nella riga
    while (indiceScorrimento < dimensioneGriglia && risultatoValidazione) {
        if (leggereValGriglia(*puntatoreGriglia, rigaTarghet, indiceScorrimento) == numeroInserito) {
            risultatoValidazione = FALSO;
        }
        indiceScorrimento = indiceScorrimento + 1;
    }

    // Controllo validità nella colonna
    indiceScorrimento = 0;
    while (indiceScorrimento < dimensioneGriglia && risultatoValidazione) {
        if (leggereValGriglia(*puntatoreGriglia, indiceScorrimento, colonnaTarghet) == numeroInserito) {
            risultatoValidazione = FALSO;
        }
        indiceScorrimento = indiceScorrimento + 1;
    }

    // Controllo validità nel sottoquadrato
    if (risultatoValidazione) {
        dimensioneSottoquadrato = (int)sqrt(dimensioneGriglia);
        rigaInizioSottoquadrato = rigaTarghet - rigaTarghet % dimensioneSottoquadrato;
        colonnaInizioSottoquadrato = colonnaTarghet - colonnaTarghet % dimensioneSottoquadrato;

        indiceRigaSottoquadrato = 0;
        while (indiceRigaSottoquadrato < dimensioneSottoquadrato && risultatoValidazione) {
            indiceColonnaSottoquadrato = 0;
            while (indiceColonnaSottoquadrato < dimensioneSottoquadrato && risultatoValidazione) {
                if (leggereValGriglia(*puntatoreGriglia, 
                                    indiceRigaSottoquadrato + rigaInizioSottoquadrato, 
                                    indiceColonnaSottoquadrato + colonnaInizioSottoquadrato) == numeroInserito) {
                    risultatoValidazione = FALSO;
                }
                indiceColonnaSottoquadrato = indiceColonnaSottoquadrato + 1;
            }
            indiceRigaSottoquadrato = indiceRigaSottoquadrato + 1;
        }
    }

    return risultatoValidazione;
}

/**
 * Riempie completamente la griglia usando l'algoritmo di backtracking
 */
int riempireCompletamenteLaGriglia(Griglia *puntatoreGriglia, int dimensioneGriglia) {
    int rigaCorrente;
    int colonnaCorrente;
    int cellaTrovata;
    int numeroTentativo;

    // Inizializzazione variabili
    rigaCorrente = 0;
    colonnaCorrente = 0;
    cellaTrovata = 0;

    // Ricerca della prima cella vuota
    while (rigaCorrente < dimensioneGriglia && !cellaTrovata) {
        colonnaCorrente = 0;
        while (colonnaCorrente < dimensioneGriglia && !cellaTrovata) {
            if (leggereValGriglia(*puntatoreGriglia, rigaCorrente, colonnaCorrente) == 0) {
                cellaTrovata = 1;
            } else {
                colonnaCorrente = colonnaCorrente + 1;
            }
        }
        if (!cellaTrovata) {
            rigaCorrente = rigaCorrente + 1;
        }
    }

    // Se non ci sono celle vuote, la griglia è completa
    if (rigaCorrente == dimensioneGriglia) {
        return VERO;
    }

    // Tentativo di inserimento numeri da 1 alla dimensione
    numeroTentativo = 1;
    while (numeroTentativo <= dimensioneGriglia) {
        if (verificareValiditaMossa(puntatoreGriglia, dimensioneGriglia, 
                                  rigaCorrente, colonnaCorrente, numeroTentativo)) {
            scrivereValGriglia(puntatoreGriglia, rigaCorrente, colonnaCorrente, numeroTentativo);

            // Ricorsione per riempire il resto della griglia
            if (riempireCompletamenteLaGriglia(puntatoreGriglia, dimensioneGriglia)) {
                return VERO;
            }

            // Backtrack: rimuove il numero se non porta a una soluzione
            scrivereValGriglia(puntatoreGriglia, rigaCorrente, colonnaCorrente, 0);
        }
        numeroTentativo = numeroTentativo + 1;
    }

    return FALSO;
}

/**
 * Genera un Sudoku completo e poi rimuove celle per creare il puzzle
 */
void generareSudoku(Partita *puntatorePartita, int dimensioneGriglia, int livelloDifficolta) {
    riempireCompletamenteLaGriglia(&puntatorePartita->grigliaPartita, dimensioneGriglia);
    rimuovereNumeriDallaGriglia(&puntatorePartita->grigliaPartita, dimensioneGriglia, livelloDifficolta);
}

/**
 * Stampa la griglia di gioco formattata
 */
void stampareGrigliaPartita(Partita *puntatorePartita) {
    int indiceRiga;
    int indiceColonna;
    int dimensioneSottoquadrato;
    Griglia grigliaCorrente;
    int dimensioneGriglia;
    int valoreCorrente;

    // Inizializzazione variabili
    grigliaCorrente = leggereGrigliaPartita(*puntatorePartita);
    dimensioneGriglia = leggereDimGriglia(grigliaCorrente);

    // Determinazione della dimensione del sottoquadrato
    if (dimensioneGriglia == DIMENSIONE_PICCOLA) {
        dimensioneSottoquadrato = 2;
    } else if (dimensioneGriglia == DIMENSIONE_MEDIA) {
        dimensioneSottoquadrato = 3;
    } else if (dimensioneGriglia == DIMENSIONE_GRANDE) {
        dimensioneSottoquadrato = 4;
    }

    // Stampa degli indici delle colonne
    indiceColonna = 0;
    while (indiceColonna < dimensioneGriglia) {
        printf("%4d", indiceColonna + 1);
        indiceColonna = indiceColonna + 1;
    }

    // Stampa della linea superiore
    printf("\n   +-");
    indiceColonna = 0;
    while (indiceColonna < dimensioneGriglia) {
        printf("--");
        if ((indiceColonna + 1) % dimensioneSottoquadrato == 0 && indiceColonna != dimensioneGriglia - 1) {
            printf("---");
        }
        indiceColonna = indiceColonna + 1;
    }
    printf("-+\n");

    // Stampa delle righe con i valori
    indiceRiga = 0;
    while (indiceRiga < dimensioneGriglia) {
        printf("%2d | ", indiceRiga + 1);
        
        indiceColonna = 0;
        while (indiceColonna < dimensioneGriglia) {
            valoreCorrente = leggereValGriglia(grigliaCorrente, indiceRiga, indiceColonna);
            if (valoreCorrente == 0) {
                printf("  ");
            } else {
                printf("%2d", valoreCorrente);
            }

            if ((indiceColonna + 1) % dimensioneSottoquadrato == 0 && indiceColonna != dimensioneGriglia - 1) {
                printf(" | ");
            } else {
                printf(" ");
            }
            indiceColonna = indiceColonna + 1;
        }
        printf("|\n");

        // Stampa delle linee di separazione tra i sottoquadrati
        if ((indiceRiga + 1) % dimensioneSottoquadrato == 0 && indiceRiga != dimensioneGriglia - 1) {
            printf("   +-");
            indiceColonna = 0;
            while (indiceColonna < dimensioneGriglia) {
                printf("--");
                if ((indiceColonna + 1) % dimensioneSottoquadrato == 0 && indiceColonna != dimensioneGriglia - 1) {
                    printf("-+-");
                }
                indiceColonna = indiceColonna + 1;
            }
            printf("-+\n");
        }
        indiceRiga = indiceRiga + 1;
    }

    // Stampa della linea inferiore
    printf("   +-");
    indiceColonna = 0;
    while (indiceColonna < dimensioneGriglia) {
        printf("--");
        if ((indiceColonna + 1) % dimensioneSottoquadrato == 0 && indiceColonna != dimensioneGriglia - 1) {
            printf("-+-");
        }
        indiceColonna = indiceColonna + 1;
    }
    printf("-+\n");
}

/**
 * Raccoglie l'input della riga dall'utente con validazione
 */
int raccogliereDatiRiga(Griglia *puntatoreGriglia, int *puntatoreInputRiga) {
    int inputValido;

    // Inizializzazione variabili
    inputValido = 0;

    while (!inputValido) {
        resetZonaInput(INPUT_RIGA_NUMERO_RIGA, INPUT_COLONNA_BASE);

        while (scanf("%d", puntatoreInputRiga) != 1) {
            pulireBuffer();
            resetZonaInput(INPUT_RIGA_NUMERO_RIGA, INPUT_COLONNA_BASE);
            mostrareMessaggioErrore("Digita un Numero", ERRORE_MESSAGGIO_RIGA + 2, ERRORE_MESSAGGIO_COLONNA);
            resetZonaInput(INPUT_RIGA_NUMERO_RIGA, INPUT_COLONNA_BASE);
        }

        pulireBuffer();

        if (*puntatoreInputRiga < 1 || *puntatoreInputRiga > leggereDimGriglia(*puntatoreGriglia)) {
            mostrareMessaggioErrore("Numero fuori intervallo", ERRORE_MESSAGGIO_RIGA + 2, ERRORE_MESSAGGIO_COLONNA);
            resetZonaInput(INPUT_RIGA_NUMERO_RIGA, INPUT_COLONNA_BASE);
        } else {
            inputValido = 1;
        }
    }
    return *puntatoreInputRiga;
}

/**
 * Raccoglie l'input della colonna dall'utente con validazione
 */
int raccogliereDatiColonna(Griglia *puntatoreGriglia, int *puntatoreInputColonna) {
    int inputValido;

    // Inizializzazione variabili
    inputValido = 0;

    while (!inputValido) {
        resetZonaInput(INPUT_RIGA_NUMERO_COLONNA, INPUT_COLONNA_BASE);

        while (scanf("%d", puntatoreInputColonna) != 1) {
            pulireBuffer();
            resetZonaInput(INPUT_RIGA_NUMERO_COLONNA, INPUT_COLONNA_BASE);
            mostrareMessaggioErrore("Digita un Numero", ERRORE_MESSAGGIO_RIGA + 2, ERRORE_MESSAGGIO_COLONNA);
            resetZonaInput(INPUT_RIGA_NUMERO_COLONNA, INPUT_COLONNA_BASE);
        }

        pulireBuffer();

        if (*puntatoreInputColonna < 1 || *puntatoreInputColonna > leggereDimGriglia(*puntatoreGriglia)) {
            mostrareMessaggioErrore("Numero fuori intervallo", ERRORE_MESSAGGIO_RIGA + 2, ERRORE_MESSAGGIO_COLONNA);
            resetZonaInput(INPUT_RIGA_NUMERO_COLONNA, INPUT_COLONNA_BASE);
        } else {
            inputValido = 1;
        }
    }
    return *puntatoreInputColonna;
}

/**
 * Raccoglie l'input del valore dall'utente con validazione
 */
int raccogliereDatiValore(Griglia *puntatoreGriglia, int *puntatoreInputValore) {
    int inputValido;

    // Inizializzazione variabili
    inputValido = 0;

    while (!inputValido) {
        resetZonaInput(INPUT_RIGA_NUMERO_VALORE, INPUT_COLONNA_BASE);

        while (scanf("%d", puntatoreInputValore) != 1) {
            pulireBuffer();
            resetZonaInput(INPUT_RIGA_NUMERO_VALORE, INPUT_COLONNA_BASE);
            mostrareMessaggioErrore("Digita un Numero", ERRORE_MESSAGGIO_RIGA + 2, ERRORE_MESSAGGIO_COLONNA);
            resetZonaInput(INPUT_RIGA_NUMERO_VALORE, INPUT_COLONNA_BASE);
        }

        pulireBuffer();

        if (*puntatoreInputValore < 1 || *puntatoreInputValore > leggereDimGriglia(*puntatoreGriglia)) {
            mostrareMessaggioErrore("Numero fuori intervallo", ERRORE_MESSAGGIO_RIGA + 2, ERRORE_MESSAGGIO_COLONNA);
            resetZonaInput(INPUT_RIGA_NUMERO_VALORE, INPUT_COLONNA_BASE);
        } else {
            inputValido = 1;
        }
    }
    return *puntatoreInputValore;
}

/**
 * Controlla se la griglia è completamente riempita
 */
int controllareSeLaGrigliaECompleta(Griglia grigliaCorrente) {
    int dimensioneGriglia;
    int indiceRiga;
    int indiceColonna;
    int grigliaCompleta;

    // Inizializzazione variabili
    dimensioneGriglia = leggereDimGriglia(grigliaCorrente);
    indiceRiga = 0;
    grigliaCompleta = VERO;

    while (indiceRiga < dimensioneGriglia && grigliaCompleta) {
        indiceColonna = 0;
        while (indiceColonna < dimensioneGriglia && grigliaCompleta) {
            if (leggereValGriglia(grigliaCorrente, indiceRiga, indiceColonna) == 0) {
                grigliaCompleta = FALSO;
            }
            indiceColonna = indiceColonna + 1;
        }
        indiceRiga = indiceRiga + 1;
    }
    
    return grigliaCompleta;
}
void loopPartita(int codiceDifficolta, int codiceDimensione);
