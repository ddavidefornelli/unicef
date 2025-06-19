#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "interfaccia_util.h"
#include "tipiDiDato.h"
#include "partita.h"
#include "homepage.h"

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

#define BLU "\033[34m"
#define RESET "\033[0m"

void avviarePartita(const char *inputNome, int inputDifficolta, int inputDimensione) {
    Partita partita;
    int valDaInserire, riga, colonna;
    int grigliaPiena = FALSO;

    /*indica se l'input dell'utente è errato*/
    int valido = FALSO;
    
    /*indica se l'input dell'utente è errato*/
    int errore = FALSO;
    
    /*valore inserito dall'utente(31 per salvare la partita, 32 per uscire dalla partita)*/
    int inputSpeciale = FALSO;

    inizializzareGrigliaPartita(&partita, inputDimensione);
    scrivereNomePartita(&partita, (char *)inputNome);
    convertiDimensione(&inputDimensione);
    generareSudoku(&partita, inputDimensione, inputDifficolta);

    while (grigliaPiena == FALSO) {
        mostraSchermo(inputDimensione);
        stampareGrigliaPartita(&partita);
        stampareTabellaInput();

        if (errore == VERO) {
            mostrareMessaggioErrore("Inserisci valori corretti", RIGA_ERRORE + 2, COLONNA_ERRORE);
            errore = FALSO;
        }

        Griglia griglia = leggereGrigliaPartita(partita);
        inputSpeciale = FALSO;

        collezionaRiga(&griglia, &riga);
        if (riga == SALVA_PARTITA || colonna == SALVA_PARTITA || valDaInserire == SALVA_PARTITA) {
            salvarePartitaCorrente(&partita);
            inputSpeciale = VERO;
        }
        
        if (inputSpeciale == FALSO) {
            collezionaColonna(&griglia, &colonna);
            collezionaValore(&griglia, &valDaInserire);

            valido = verificareValidita(&griglia, inputDimensione, riga - 1, colonna - 1, valDaInserire);
            if (valido == VERO) {
                scrivereValGrigliaPartita(&partita, valDaInserire, riga - 1, colonna - 1);
                grigliaPiena = controllareGrigliaPiena(leggereGrigliaPartita(partita));
            } else {
                errore = VERO;
            }
        }


    }
    stampareVittoria();
}

void mostraSchermo(int dimensione) {
    if (dimensione != 16) {
        stampareTitoloPartita();
    } else {
        pulireSchermo();
        printf("\n");
    }
}

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
    printf("\n\n\n\n\n");
    stampareCentrato("gruppo 29 al rogo");

    tornareHomepage(&input, RIGA_INPUT - 10, 30);
}

void stampareTabellaInput() {
    disegnareCornice();
    
    spostareCursore(RIGA_INPUT_RIGA - 1, COLONNA_INPUT + 1);
    printf("-Riga-");
    spostareCursore(RIGA_INPUT_COLONNA - 1, COLONNA_INPUT);
    printf("-Colonna-");
    spostareCursore(RIGA_INPUT_VALORE - 1, COLONNA_INPUT);
    printf("-Valore-");
    spostareCursore(25, 17);
    printf("\033[34mDIGITA 32 per HOMEPAGE   |   DIGITA 31 per SALVARE\033[0m");
}

void disegnareCornice() {
    int i = 0;
    
    spostareCursore(RIGA_INPUT_RIGA - 2, COLONNA_INPUT - 2);
    printf("+------------+\n");
    spostareCursore(RIGA_INPUT_RIGA - 3, COLONNA_INPUT - 2);
    printf("|   Input    |\n");
    spostareCursore(RIGA_INPUT_RIGA - 4, COLONNA_INPUT - 2);
    printf("+------------+\n");
    
    while (i < 8) {
        spostareCursore(RIGA_INPUT_RIGA - 1 + i, COLONNA_INPUT - 2);
        printf("|            |\n");
        i = i + 1;
    }
    
    spostareCursore(RIGA_INPUT_RIGA + 7, COLONNA_INPUT - 2);
    printf("+------------+\n");
}

void convertiDimensione(int *dimensione) {
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

void rimuovereNumeri(Griglia *griglia, int dimensione, int difficolta) {
    int cellaGriglia = dimensione * dimensione;
    int celleDaRimuovere = cellaGriglia * calcolareCelleDaRimuovere(difficolta) / 100;
    int rimosse = 0;
    int riga, colonna;
    
    srand(time(NULL));

    while (rimosse < celleDaRimuovere) {
        riga = rand() % dimensione;
        colonna = rand() % dimensione;

        if (leggereValGriglia(*griglia, riga, colonna) != CELLA_VUOTA) {
            scrivereValGriglia(griglia, riga, colonna, CELLA_VUOTA);
            rimosse = rimosse + 1;
        }
    }
}

int calcolareCelleDaRimuovere(int difficolta) {
    int risultato;
    if(difficolta == DIFFICOLTA_FACILE)  {
        risultato = 20;
    } else if (difficolta == DIFFICOLTA_MEDIA) {
        risultato = 40;
    } else if (difficolta == DIFFICOLTA_DIFFICILE) {
        risultato = 70;
    }
    return risultato;
}

int verificareValidita(Griglia *griglia, int dimensione, int riga, int colonna, int numero) {
    int risultato = VERO;
    if (verificareRiga(griglia, dimensione, riga, numero) == FALSO) {
        risultato = FALSO;
    } else {
        if (verificareColonna(griglia, dimensione, colonna, numero) == FALSO) {
            risultato = FALSO;
        } else {
            if (verificareSottoquadrato(griglia, dimensione, riga, colonna, numero) == FALSO) {
                risultato = FALSO;
            }
        }
    }
    
    return risultato;
}

int verificareRiga(Griglia *griglia, int dimensione, int riga, int numero) {
    int i = 0;
    int risultato = VERO;
    
    while (i < dimensione && risultato == VERO) {
        if (leggereValGriglia(*griglia, riga, i) == numero) {
            risultato = FALSO;
        } else {
            i = i + 1;
        }
    }
    
    return risultato;
}

int verificareColonna(Griglia *griglia, int dimensione, int colonna, int numero) {
    int i = 0;
    int risultato = VERO;
    
    while (i < dimensione && risultato == VERO) {
        if (leggereValGriglia(*griglia, i, colonna) == numero) {
            risultato = FALSO;
        } else {
            i = i + 1;
        }
    }
    
    return risultato;
}

int verificareSottoquadrato(Griglia *griglia, int dimensione, int riga, int colonna, int numero) {
    int dimensioneQuadrato = (int)sqrt(dimensione);
    int inizioRiga = riga - riga % dimensioneQuadrato;
    int inizioColonna = colonna - colonna % dimensioneQuadrato;
    int i = 0;
    int j = 0;
    int risultato = VERO;

    while (i < dimensioneQuadrato && risultato == VERO) {
        j = 0;
        while (j < dimensioneQuadrato && risultato == VERO) {
            if (leggereValGriglia(*griglia, i + inizioRiga, j + inizioColonna) == numero) {
                risultato = FALSO;
            } else {
                j = j + 1;
            }
        }
        if (risultato == VERO) {
            i = i + 1;
        }
    }
    
    return risultato;
}

int riempireGriglia(Griglia *griglia, int dimensione) {
    int riga = 0;
    int colonna = 0;
    /*indica se all'interno della griglia ci sono celle vuote*/
    int cellaVuota;
    
    /*valore da inserire all'interno della griglia*/
    int valDaInserire = 1;
    
    /*indica se la griglia è piena*/
    int grigliaPiena = FALSO;

    cellaVuota = trovareCellaVuota(griglia, dimensione, &riga, &colonna);
    if (cellaVuota == FALSO) {
        grigliaPiena = VERO;
    } else {
        while (valDaInserire <= dimensione && grigliaPiena == FALSO) {
            if (verificareValidita(griglia, dimensione, riga, colonna, valDaInserire) == VERO) {
                scrivereValGriglia(griglia, riga, colonna, valDaInserire);

                if (riempireGriglia(griglia, dimensione) == VERO) {
                    grigliaPiena = VERO;
                } else {
                    /*pone la cella con valore non valido a 0 in modo tale che il nuovo valore verrà inserito in quella cella*/
                    scrivereValGriglia(griglia, riga, colonna, CELLA_VUOTA);
                }
            }
            if (grigliaPiena == FALSO) {
                valDaInserire = valDaInserire + 1;
            }
        }
    }
    return grigliaPiena;
}

int trovareCellaVuota(Griglia *griglia, int dimensione, int *riga, int *colonna) {
    int i = 0;
    int j;
    int trovato = FALSO;
    
    while (i < dimensione && trovato == FALSO) {
        j = 0;
        while (j < dimensione && trovato == FALSO) {
            if (leggereValGriglia(*griglia, i, j) == 0) {
                *riga = i;
                *colonna = j;
                trovato = VERO;
            } else {
                j = j + 1;
            }
        }
        if (trovato == FALSO) {
            i = i + 1;
        }
    }
    return trovato;
}

void generareSudoku(Partita *partita, int dimensione, int difficolta) {
    riempireGriglia(&partita->grigliaPartita, dimensione);
    rimuovereNumeri(&partita->grigliaPartita, dimensione, difficolta);
}

void stampareGrigliaPartita(Partita *partita) {
    Griglia griglia = leggereGrigliaPartita(*partita);
    int dimensione = leggereDimGriglia(griglia);
    int numeroSottoquadrato = calcolaSottoquadrato(dimensione);
    
    stampareIntestazioneColonne(dimensione, numeroSottoquadrato);
    stampareLineaOrizzontale(dimensione, numeroSottoquadrato);
    stampareRigheGriglia(griglia, dimensione, numeroSottoquadrato);
    stampareLineaOrizzontale(dimensione, numeroSottoquadrato);
}

int calcolaSottoquadrato(int dimensione) {
    int risultato = 2;
    if (dimensione == 9) {
        risultato = 3;
    } else {
        if (dimensione == 16) {
            risultato = 4;
        }
    }
    return risultato;
}

void stampareIntestazioneColonne(int dimensione, int numeroSottoquadrato) {
    int j = 0;
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

void stampareLineaOrizzontale(int dimensione, int numeroSottoquadrato) {
    int j = 0;
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

void stampareRigheGriglia(Griglia griglia, int dimensione, int numeroSottoquadrato) {
    int i = 0;
    while (i < dimensione) {
        stampareRigaGriglia(griglia, dimensione, numeroSottoquadrato, i);
        
        if ((i + 1) % numeroSottoquadrato == 0 && i != dimensione - 1) {
            stampareLineaOrizzontale(dimensione, numeroSottoquadrato);
        }
        i = i + 1;
    }
}

void stampareRigaGriglia(Griglia griglia, int dimensione, int numeroSottoquadrato, int riga) {
    int j = 0;
    int valore;
    
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

int collezionaInput(Griglia *griglia, int *inputRiga, int posRiga) {
    int valida = FALSO;
    int inputOk;

    while (valida == FALSO) {
        resetZonaInput(posRiga, COLONNA_INPUT);
        inputOk = FALSO;

        while (inputOk == FALSO) {
            if (scanf("%d", inputRiga) == 1) {
                inputOk = VERO;
            } else {
                pulireBuffer();
                resetZonaInput(posRiga, COLONNA_INPUT);
                mostrareMessaggioErrore("Digita un Numero", RIGA_ERRORE + 2, COLONNA_ERRORE);
                resetZonaInput(posRiga, COLONNA_INPUT);
            }
        }

        pulireBuffer();

        if ((*inputRiga < 1 || *inputRiga > leggereDimGriglia(*griglia)) && (*inputRiga != 32 && *inputRiga != 31)) {
            mostrareMessaggioErrore("Numero fuori intervallo", RIGA_ERRORE + 2, COLONNA_ERRORE);
            resetZonaInput(posRiga, COLONNA_INPUT);
        } else {
            if (*inputRiga == 32) {
                avviareMenuPrincipale();
            } else {
                valida = VERO;
            }
        }
    }
    
    return *inputRiga;
}

int collezionaRiga(Griglia *griglia, int *inputRiga) {
    return collezionaInput(griglia, inputRiga, RIGA_INPUT_RIGA);
}

int collezionaColonna(Griglia *griglia, int *inputColonna) {
    return collezionaInput(griglia, inputColonna, RIGA_INPUT_COLONNA);
}

int collezionaValore(Griglia *griglia, int *inputValore) {
    return collezionaInput(griglia, inputValore, RIGA_INPUT_VALORE);
}

int controllareGrigliaPiena(Griglia griglia) {
    int dimensione = leggereDimGriglia(griglia);
    int riga = 0;
    int colonna = 0;
    int esito = VERO;

    while (riga < dimensione && esito == VERO) {
        colonna = 0;
        while (colonna < dimensione && esito == VERO) {
            if (leggereValGriglia(griglia, riga, colonna) == 0) {
                esito = FALSO;
            } else {
                colonna = colonna + 1;
            }
        }
        if (esito == VERO) {
            riga = riga + 1;
        }
    }
    
    return esito;
}

void salvarePartitaCorrente(Partita *partita) {
    char percorso[100];
    snprintf(percorso, sizeof(percorso), "database/partita_%s.txt", partita->nomePartita);
    salvarePartita(partita, percorso);
}

int salvarePartita(Partita *partita, const char *percorso) {
    FILE *file = fopen(percorso, "w");
    int risultato = FALSO;
    
    if (file != NULL) {
        int dimensione = leggereDimGriglia(partita->grigliaPartita);
        int difficolta = leggereDimGrigliaImp(partita->impPartita);

        fprintf(file, "%d %d\n", dimensione, difficolta);
        salvareValoriGriglia(file, partita, dimensione);
        fclose(file);
        risultato = VERO;
    }
    
    return risultato;
}

void salvareValoriGriglia(FILE *file, Partita *partita, int dimensione) {
    int i = 0;
    int j;
    
    while (i < dimensione) {
        j = 0;
        while (j < dimensione) {
            fprintf(file, "%d ", leggereValGriglia(partita->grigliaPartita, i, j));
            j = j + 1;
        }
        fprintf(file, "\n");
        i = i + 1;
    }
}

int caricaPartita(Partita *partita, const char *percorso) {
    FILE *file = fopen(percorso, "r");
    int risultato = 0;
    int dimensione, difficolta;
    
    if (file != NULL) {
        if (fscanf(file, "%d %d", &dimensione, &difficolta) == 2) {
            inizializzareGrigliaPartita(partita, dimensione);
            
            if (caricaValoriGriglia(file, partita, dimensione) == VERO) {
                risultato = 1;
            }
        }
        fclose(file);
    }
    
    return risultato;
}

int caricaValoriGriglia(FILE *file, Partita *partita, int dimensione) {
    int i = 0;
    int j = 0;
    int val;
    int risultato = VERO;
    
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

void avviarePartitaContinuata(Partita *partita) {
    int dimensione = leggereDimGriglia(partita->grigliaPartita);
    int valore, riga, colonna;
    int grigliaPiena = FALSO;
    int valido = FALSO;
    int errore = FALSO;
    int inputSpeciale = FALSO;

    while (grigliaPiena == FALSO) {
        mostraSchermo(dimensione);
        stampareGrigliaPartita(partita);
        stampareTabellaInput();

        if (errore == VERO) {
            mostrareMessaggioErrore("Inserisci valori corretti", RIGA_ERRORE + 2, COLONNA_ERRORE);
            errore = FALSO;
        }

        Griglia griglia = leggereGrigliaPartita(*partita);
        inputSpeciale = FALSO;

        collezionaRiga(&griglia, &riga);
        if (riga == 31) {
            salvarePartitaCorrente(partita);
            inputSpeciale = VERO;
        }
        
        if (inputSpeciale == FALSO) {
            collezionaColonna(&griglia, &colonna);
            collezionaValore(&griglia, &valore);

            valido = verificareValidita(&griglia, dimensione, riga - 1, colonna - 1, valore);
            if (valido == VERO) {
                scrivereValGrigliaPartita(partita, valore, riga - 1, colonna - 1);
                grigliaPiena = controllareGrigliaPiena(leggereGrigliaPartita(*partita));
            } else {
                errore = VERO;
            }
        }
    }
    stampareVittoria();
}
