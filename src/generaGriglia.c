#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIMENSIONEMASSIMA (12)

int dimensioneGriglia;
int dimensioneSottogriglia;

// Funzione per stampare la griglia Sudoku
void stampaGrigliaSudoku(int griglia[DIMENSIONEMASSIMA][DIMENSIONEMASSIMA]) {
    int i;
    int j;

    i = 0;
    while (i < dimensioneGriglia) {
        j = 0;
        while (j < dimensioneGriglia) {
            printf("%d ", griglia[i][j]);
            j = j + 1;
        }
        printf("\n");
        i = i + 1;
    }
}

// Funzione per verificare se un numero può essere inserito nella posizione (riga, colonna)
int eValido(int griglia[DIMENSIONEMASSIMA][DIMENSIONEMASSIMA], int riga, int colonna, int valore) {
    int i;
    int j;
    int esito;
    int rigaDiPartenza;
    int colonnaDiPartenza;

    // Controlla la riga
    j = 0;
    while (i < dimensioneGriglia && esito != 0) {
        if (griglia[riga][j] == valore) {
            esito = 0;
        }
        i = i + 1;
    }

    // Controlla la colonna
    i = 0;
    while (i < dimensioneGriglia && esito != 0) {
        if (griglia[i][colonna] == valore) {
            esito = 0;
        }
        i = i + 1;
    }

    // Calcola l'inizio della sottogriglia
    rigaDiPartenza = (riga / dimensioneSottogriglia) * dimensioneSottogriglia;
    colonnaDiPartenza = (colonna / dimensioneSottogriglia) * dimensioneSottogriglia;

    // Controlla la sottogriglia
    i = 0;
    while (i < dimensioneSottogriglia && esito != 0) {
        j = 0;
        while (j < dimensioneSottogriglia) {
            if (griglia[rigaDiPartenza + i][colonnaDiPartenza + j] == valore) {
                esito = 0;
            }
            j = j + 1;
        }
        i = i + 1;
    }

    return esito;
}

// Trova la prossima cella vuota nella griglia
int trovaCellaVuota(int griglia[DIMENSIONEMASSIMA][DIMENSIONEMASSIMA], int *riga, int *colonna) {
    int i;
    int j;
    int esito = 0;

    i = 0;
    while (i < dimensioneGriglia && esito == 0) {
        j = 0;
        while (j < dimensioneGriglia) {
            if (griglia[i][j] == 0) {
                *riga = i;
                *colonna = j;
                esito = 1;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    return esito;
}

// Funzione per inserire alcuni numeri casuali nella griglia
void inserisciNumeriCasuali(int griglia[DIMENSIONEMASSIMA][DIMENSIONEMASSIMA]) {
    int i;
    int numeriDaInserire;
    int riga;
    int colonna;
    int valore;
    int tentativi;
    
    // Determina quanti numeri casuali inserire - circa 1/5 della griglia
    numeriDaInserire = (dimensioneGriglia * dimensioneGriglia) / 5;
    
    i = 0;
    while (i < numeriDaInserire) {
        tentativi = 0;
        // Trova una posizione casuale valida
        while (tentativi < 50) { // Limita i tentativi per evitare loop infiniti
            riga = rand() % dimensioneGriglia;
            colonna = rand() % dimensioneGriglia;
            
            // Controlla se la cella è vuota
            if (griglia[riga][colonna] == 0) {
                // Genera un valore casuale tra 1 e dimensioneGriglia
                valore = (rand() % dimensioneGriglia) + 1;
                
                // Verifica se il valore è valido
                if (eValido(griglia, riga, colonna, valore)) {
                    griglia[riga][colonna] = valore;
                    i = i + 1;
                    break;
                }
            }
            tentativi = tentativi + 1;
        }
        
        // Se troppi tentativi falliti, interrompi
        if (tentativi >= 50) {
            break;
        }
    }
}

// Funzione per generare la griglia Sudoku con backtracking non ricorsivo
int generaSudoku(int griglia[DIMENSIONEMASSIMA][DIMENSIONEMASSIMA]) {
    int pila[DIMENSIONEMASSIMA * DIMENSIONEMASSIMA][4]; // [riga, colonna, valore, prossimo_valore]
    int indicePila;
    int riga;
    int colonna;
    int valoreTrovato;
    int valore;
    int i;
    int j;

    // Inizializza la griglia
    i = 0;
    while (i < dimensioneGriglia) {
        j = 0;
        while (j < dimensioneGriglia) {
            griglia[i][j] = 0;
            j = j + 1;
        }
        i = i + 1;
    }
    
    // Inserisci alcuni numeri casuali nella griglia
    inserisciNumeriCasuali(griglia);

    indicePila = 0;

    // Trova la prima cella vuota per iniziare
    if (trovaCellaVuota(griglia, &riga, &colonna) == 0) {
        return 1; // La griglia è già completa (molto improbabile)
    }
    
    valore = 0;
    while (1) {
        valoreTrovato = 0;
        valore = valore + 1;

        while (valore <= dimensioneGriglia && valoreTrovato == 0) {
            if (eValido(griglia, riga, colonna, valore)) {
                griglia[riga][colonna] = valore;
                pila[indicePila][0] = riga;
                pila[indicePila][1] = colonna;
                pila[indicePila][2] = valore;
                pila[indicePila][3] = valore;
                indicePila = indicePila + 1;
                
                if (trovaCellaVuota(griglia, &riga, &colonna) == 0) {
                    return 1; // Soluzione trovata
                }
                
                valoreTrovato = 1;
                valore = 0; // Resetta il valore per la nuova cella
            } else {
                valore = valore + 1;
            }
        }

        if (valoreTrovato == 0) {
            if (indicePila == 0) {
                return 0; // Nessuna soluzione
            }
            
            indicePila = indicePila - 1;
            riga = pila[indicePila][0];
            colonna = pila[indicePila][1];
            valore = pila[indicePila][3]; // Riprendi dall'ultimo valore provato
            griglia[riga][colonna] = 0;   // Azzera la cella
        }
    }
}

// Funzione principale
int main() {
    int griglia[DIMENSIONEMASSIMA][DIMENSIONEMASSIMA];
    int esito;
    esito = 0;
    
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));

    printf("Inserisci la dimensione della griglia (6, 9): ");
    scanf("%d", &dimensioneGriglia);

    if (dimensioneGriglia == 6) {
        dimensioneSottogriglia = 2; // 2x3
    } else if (dimensioneGriglia == 9) {
        dimensioneSottogriglia = 3; // 3x3
    } else {
        printf("Dimensione non valida!\n");
        return 1;
    }

    esito = generaSudoku(griglia);
    if (esito == 1) {
        printf("Griglia Sudoku generata correttamente:\n");
        stampaGrigliaSudoku(griglia);
    } else {
        printf("Errore: impossibile generare la griglia Sudoku.\n");
    }

    getchar();
    getchar();
    return 0;
}
