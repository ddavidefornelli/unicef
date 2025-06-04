#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "partita.h"
#include "interfaccia_util.h"

#define INPUT_RIGA 23
#define INPUT_COLONNA 30
#define CELLA_VUOTA 0
#define PERCENTUALE_FACILE 0.3
#define PERCENTUALE_MEDIA 0.5
#define PERCENTUALE_DIFFICILE 0.7

// Enum per difficoltà
typedef enum {
    FACILE = 1,
    MEDIA = 2,
    DIFFICILE = 3
} Difficolta;

// Strutture dati
typedef struct {
    int dimensioneGriglia;
    int **valoriGriglia;
} Griglia;

typedef struct {
    int difficolta;
    int dimensione;
} Impostazioni;

typedef struct {
    Impostazioni impPartita;
    Griglia grigliaPartita;
    char nomePartita[50];
} Partita;

// ============ FUNZIONI DI ACCESSO ============

Impostazioni leggereImpPartita(Partita partita) {
    return partita.impPartita;
}

int leggereDifficoltaImp(Impostazioni imp) {
    return imp.difficolta;
}

Griglia leggereGrigliaPartita(Partita partita) {
    return partita.grigliaPartita;
}

int leggereDimGriglia(Griglia griglia) {
    return griglia.dimensioneGriglia;
}

char* leggereNomePartita(Partita partita) {
    return partita.nomePartita;
}

int leggereValGriglia(Griglia griglia, int riga, int colonna) {
    return griglia.valoriGriglia[riga][colonna];
}

void scrivereImpPartita(Partita *partita, int difficolta, int dimensione) {
    partita->impPartita.difficolta = difficolta;
    partita->impPartita.dimensione = dimensione;
}

void scrivereNomePartita(Partita *partita, char *nome) {
    strcpy(partita->nomePartita, nome);
}

void scrivereGrigliaPartita(Partita *partita, int valore, int riga, int colonna) {
    partita->grigliaPartita.valoriGriglia[riga][colonna] = valore;
}

// ============ FUNZIONI UTILITY ============

int leggereDaTastiera() {
    int valore;
    scanf("%d", &valore);
    return valore;
}

int generareNumeroCasuale(int dimensioneMassima) {
    return (rand() % dimensioneMassima) + 1;
}

// ============ FUNZIONI PRINCIPALI ============

int cercarePartita(Partita partita) {
    FILE *file;
    char nomeFile[60];
    sprintf(nomeFile, "%s.txt", partita.nomePartita);
    
    file = fopen(nomeFile, "r");
    if (file != NULL) {
        fclose(file);
        return 1; // VERO
    }
    return 0; // FALSO
}

Partita caricarePartita(char *nomeFile) {
    Partita partita;
    FILE *file = fopen(nomeFile, "r");
    
    if (file != NULL) {
        fscanf(file, "%d %d", &partita.impPartita.difficolta, &partita.impPartita.dimensione);
        fscanf(file, "%s", partita.nomePartita);
        
        int dim = partita.impPartita.dimensione;
        partita.grigliaPartita.dimensioneGriglia = dim;
        partita.grigliaPartita.valoriGriglia = (int **)malloc(dim * sizeof(int *));
        
        for (int i = 0; i < dim; i++) {
            partita.grigliaPartita.valoriGriglia[i] = (int *)malloc(dim * sizeof(int));
            for (int j = 0; j < dim; j++) {
                fscanf(file, "%d", &partita.grigliaPartita.valoriGriglia[i][j]);
            }
        }
        fclose(file);
    }
    
    return partita;
}

Partita crearePartita(Partita partita, int inputDimensione, int inputDifficolta, char *inputNome) {
    scrivereImpPartita(&partita, inputDifficolta, inputDimensione);
    scrivereNomePartita(&partita, inputNome);
    
    // Alloca memoria per la griglia
    partita.grigliaPartita.dimensioneGriglia = inputDimensione;
    partita.grigliaPartita.valoriGriglia = (int **)malloc(inputDimensione * sizeof(int *));
    
    for (int cursRighe = 0; cursRighe < inputDimensione; cursRighe++) {
        partita.grigliaPartita.valoriGriglia[cursRighe] = (int *)malloc(inputDimensione * sizeof(int));
        for (int cursColonne = 0; cursColonne < inputDimensione; cursColonne++) {
            scrivereGrigliaPartita(&partita, CELLA_VUOTA, cursRighe, cursColonne);
        }
    }
    
    return partita;
}

int verificarePresenza(int cursRighe, int cursColonne, int raggioControllaRighe, 
                      int raggioControllaColonne, Griglia griglia, int valoreDaRicercare) {
    int esito = 0; // FALSO
    int tempColonne = cursColonne;
    
    while (cursRighe < raggioControllaRighe && esito == 0) {
        cursColonne = tempColonne;
        while (cursColonne < raggioControllaColonne && esito == 0) {
            int valDaVerificare = leggereValGriglia(griglia, cursRighe, cursColonne);
            if (valDaVerificare == valoreDaRicercare) {
                esito = 1; // VERO
            } else {
                cursColonne++;
            }
        }
        cursRighe++;
    }
    
    return esito;
}

int controllareQuadranteGriglia(Griglia griglia, int valoreDaRicercare, 
                               int rigaDiInizio, int colonnaDiInizio) {
    int dimensioneQuadrante = (int)sqrt(leggereDimGriglia(griglia));
    
    int cursRighe = (rigaDiInizio / dimensioneQuadrante) * dimensioneQuadrante;
    int raggioControllaRighe = cursRighe + dimensioneQuadrante;
    
    int cursColonne = (colonnaDiInizio / dimensioneQuadrante) * dimensioneQuadrante;
    int raggioControllaColonne = cursColonne + dimensioneQuadrante;
    
    return verificarePresenza(cursRighe, cursColonne, raggioControllaRighe, 
                             raggioControllaColonne, griglia, valoreDaRicercare);
}

int controllareRigEColGriglia(Griglia griglia, int valoreDaRicercare, 
                             int indiceRighe, int indiceColonne) {
    int esito = 0; // FALSO
    int curs = 0;
    
    while (curs < leggereDimGriglia(griglia) && esito == 0) {
        int x = leggereValGriglia(griglia, indiceRighe, curs);
        int y = leggereValGriglia(griglia, curs, indiceColonne);
        
        if (x == valoreDaRicercare || y == valoreDaRicercare) {
            esito = 1; // VERO
        }
        curs++;
    }
    
    return esito;
}

int verificareGrigliaPiena(Griglia griglia) {
    int cursRighe = 0;
    int esito = 1; // VERO
    
    while (cursRighe < leggereDimGriglia(griglia) && esito == 1) {
        int cursColonne = 0;
        while (cursColonne < leggereDimGriglia(griglia) && esito == 1) {
            if (leggereValGriglia(griglia, cursRighe, cursColonne) == 0) {
                esito = 0; // FALSO
            }
            cursColonne++;
        }
        cursRighe++;
    }
    
    return esito;
}

// Funzione ricorsiva per risolvere il Sudoku (backtracking)
int risolvereSudoku(Griglia *griglia, int riga, int colonna) {
    int dim = leggereDimGriglia(*griglia);
    
    if (riga == dim - 1 && colonna == dim) {
        return 1;
    }
    
    if (colonna == dim) {
        riga++;
        colonna = 0;
    }
    
    if (leggereValGriglia(*griglia, riga, colonna) > 0) {
        return risolvereSudoku(griglia, riga, colonna + 1);
    }
    
    for (int num = 1; num <= dim; num++) {
        int esitoRigheColonne = controllareRigEColGriglia(*griglia, num, riga, colonna);
        int esitoQuadrante = controllareQuadranteGriglia(*griglia, num, riga, colonna);
        
        if (esitoRigheColonne == 0 && esitoQuadrante == 0) {
            griglia->valoriGriglia[riga][colonna] = num;
            if (risolvereSudoku(griglia, riga, colonna + 1)) {
                return 1;
            }
            griglia->valoriGriglia[riga][colonna] = 0;
        }
    }
    return 0;
}

Partita caricareGriglia(int dimensioneGriglia, Griglia griglia, Partita partita) {
    // Prima risolve completamente la griglia
    risolvereSudoku(&partita.grigliaPartita, 0, 0);
    return partita;
}

Partita svuotareGriglia(Partita partita, int difficolta) {
    int totNumeroCelle = leggereDimGriglia(partita.grigliaPartita) * leggereDimGriglia(partita.grigliaPartita);
    int celleDaRimuovere;
    
    if (difficolta == FACILE) {
        celleDaRimuovere = totNumeroCelle * PERCENTUALE_FACILE;
    } else if (difficolta == MEDIA) {
        celleDaRimuovere = totNumeroCelle * PERCENTUALE_MEDIA;
    } else {
        celleDaRimuovere = totNumeroCelle * PERCENTUALE_DIFFICILE;
    }
    
    while (celleDaRimuovere > 0) {
        int riga = rand() % leggereDimGriglia(partita.grigliaPartita);
        int colonna = rand() % leggereDimGriglia(partita.grigliaPartita);
        
        if (leggereValGriglia(partita.grigliaPartita, riga, colonna) != CELLA_VUOTA) {
            scrivereGrigliaPartita(&partita, CELLA_VUOTA, riga, colonna);
            celleDaRimuovere--;
        }
    }
    
    return partita;
}

Partita inserireValoreGriglia(Partita partita, int valoreDaInserire, int cursRighe, int cursColonne) {
    int esitoRigheColonne = controllareRigEColGriglia(leggereGrigliaPartita(partita), 
                                                     valoreDaInserire, cursRighe, cursColonne);
    int esitoQuadrante = controllareQuadranteGriglia(leggereGrigliaPartita(partita), 
                                                    valoreDaInserire, cursRighe, cursColonne);
    
    if (esitoRigheColonne == 0 && esitoQuadrante == 0) {
        scrivereGrigliaPartita(&partita, valoreDaInserire, cursRighe, cursColonne);
    }
    
    return partita;
}

void salvarePartita(Partita partita, char *nomePartita) {
    FILE *file;
    char nomeFile[60];
    sprintf(nomeFile, "%s.txt", nomePartita);
    
    file = fopen(nomeFile, "w");
    if (file != NULL) {
        fprintf(file, "%d %d\n", partita.impPartita.difficolta, partita.impPartita.dimensione);
        fprintf(file, "%s\n", partita.nomePartita);
        
        int dim = leggereDimGriglia(partita.grigliaPartita);
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                fprintf(file, "%d ", leggereValGriglia(partita.grigliaPartita, i, j));
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
}

void stampaGriglia(Griglia griglia) {
    int dim = leggereDimGriglia(griglia);
    int sottoDim = (int)sqrt(dim);

    printf("\n");

    int i = 0;
    while (i < dim) {
        if (i % sottoDim == 0) {
            int k = 0;
            while (k < dim + sottoDim + 4) {
                printf("--");
                k++;
            }
            printf("\n");
        }

        int j = 0;
        while (j < dim) {
            if (j % sottoDim == 0) {
                printf("| ");
            }

            int val = leggereValGriglia(griglia, i, j);
            if (val == CELLA_VUOTA) {
                printf(" . ");
            } else {
                printf("%2d ", val);
            }

            j++;
        }
        printf("|\n");
        i++;
    }

    int k = 0;
    while (k < dim + sottoDim + 1) {
        printf("--");
        k++;
    }
    printf("\n\n");
}


Partita avviarePartita(int inputDimensione, int inputDifficolta, char *inputNome, char *file) {
    int esciPartita = 0; // FALSO
    int grigliaPiena = 0; // FALSO
    Partita partita;
    
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));
    
    strcpy(partita.nomePartita, inputNome);
    int partitaTrovata = cercarePartita(partita);
    
    if (partitaTrovata == 1) { // VERO
        partita = caricarePartita(file);
    } else {
        partita = crearePartita(partita, inputDimensione, inputDifficolta, inputNome);
        partita = caricareGriglia(inputDimensione, partita.grigliaPartita, partita);
        partita = svuotareGriglia(partita, inputDifficolta);
    }
    
    int dimensioneGriglia = leggereDimGriglia(leggereGrigliaPartita(partita));
    grigliaPiena = verificareGrigliaPiena(leggereGrigliaPartita(partita));
    
    while (esciPartita == 0 && grigliaPiena == 0) {
        pulireSchermo();
        stampareCentrato("                    _   _ _              ");
        stampareCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ");
        stampareCentrato("|___|  | . | .'|  _|  _| |  _| .'|  |___|");
        stampareCentrato("       |  _|__,|_| |_| |_|_| |__,|       ");
        stampareCentrato("       |_|                               ");
        stampaGriglia(leggereGrigliaPartita(partita));
        
        printf("Inserisci riga (1-%d): ", dimensioneGriglia-1);
        int cursRighe = leggereDaTastiera();
        
        printf("Inserisci colonna (0-%d): ", dimensioneGriglia-1);
        int cursColonne = leggereDaTastiera();
        
        printf("Inserisci valore (1-%d): ", dimensioneGriglia);
        int valDaInserire = leggereDaTastiera();
        
        if ((cursRighe >= 0 && cursRighe < dimensioneGriglia) && 
            (cursColonne >= 0 && cursColonne < dimensioneGriglia)) {
            
            if (leggereValGriglia(partita.grigliaPartita, cursRighe, cursColonne) == CELLA_VUOTA) {
                partita = inserireValoreGriglia(partita, valDaInserire, cursRighe, cursColonne);
                grigliaPiena = verificareGrigliaPiena(leggereGrigliaPartita(partita));
            } else {
                printf("Cella già occupata! Premi un tasto per continuare...");
                getchar();
            }
        } else {
            printf("Coordinate non valide! Premi un tasto per continuare...");
            getchar();
        }
        
        if (grigliaPiena == 0) {
            printf("Vuoi continuare a giocare? (1=Sì, 0=No): ");
            esciPartita = (leggereDaTastiera() == 0) ? 1 : 0;
        }
    }
    
    if (grigliaPiena == 1) {
        printf("\nComplimenti! Hai completato il Sudoku!\n");
    }
    
    salvarePartita(partita, leggereNomePartita(partita));
    
    return partita;
}

void loopPartita(int inputDifficolta, int inputDimensione){
    int input;
    char nomePartita[50];
    int dimensioneGriglia;

    if (inputDimensione == 1) {
      dimensioneGriglia = 4;
    }
    else if (inputDimensione == 2) {
      dimensioneGriglia = 9; 
    }
    else if (inputDimensione == 3) {
      dimensioneGriglia = 16; 
    }
    
    pulireSchermo();
    spostareCursore(12, 0);
    stampareCentrato("Inserisci il nome della partita: ");
    resetZonaInput(13, 35);
    scanf("%s", nomePartita);
    
    Partita partita = avviarePartita(dimensioneGriglia, inputDifficolta, nomePartita, nomePartita);
    
    // Libera memoria
    int dim = leggereDimGriglia(partita.grigliaPartita);
    for (int i = 0; i < dim; i++) {
        free(partita.grigliaPartita.valoriGriglia[i]);
    }
    free(partita.grigliaPartita.valoriGriglia);
    
    tornareHomepage(&input, INPUT_RIGA, INPUT_COLONNA);
}
