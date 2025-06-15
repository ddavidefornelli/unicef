#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "interfaccia_util.h"
#include "tipiDiDato.h"
#include "partita.h"
#include "homepage.h"

#define INPUT_RIGA_RIGA  13
#define INPUT_RIGA_COLONNA 16
#define INPUT_RIGA_VALORE 19
#define INPUT_RIGA 28
#define INPUT_COLONNA 67
#define FALSO 0
#define VERO 1
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 27

void loopPartita(const char *nomePartita, int inputDifficolta, int inputDimensione) {
  Partita partita;
  int inputValore;
  int inputRiga;
  int inputColonna;
  int grigliaPiena = FALSO;
  int valido = FALSO;
  int errore = FALSO;

  inizializzareGrigliaPartita(&partita, inputDifficolta, inputDimensione);
  scrivereNomePartita(&partita, (char *)nomePartita);
  convertiDifficoltaEDimensione(&inputDifficolta, &inputDimensione);
  generareSudoku(&partita, inputDimensione, inputDifficolta);

  while (!grigliaPiena) {
    if (inputDimensione != 16) {
      stampareTitoloPartita();
    } else {
      pulireSchermo();
      printf("\n");
    }
    
    stampareGrigliaPartita(&partita);
    stampareAiutiInput();

    if (errore) {
      mostrareMessaggioErrore("Inserisci i valori richiesti", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      errore = FALSO;
    }

    Griglia griglia = leggereGrigliaPartita(partita); 

    collezionaRiga(&griglia, &inputRiga);
    if (inputRiga == 31) {
      char percorso[256];
      snprintf(percorso, sizeof(percorso), "database/partita_%s.txt", partita.nomePartita);
      salvaPartita(&partita, percorso);
      int tmp;
      tornareHomepage(&tmp, INPUT_RIGA + 5, 30);
      continue;
    }
    collezionaColonna(&griglia, &inputColonna);
    collezionaValore(&griglia, &inputValore);

    valido = verificaValidita(&griglia, inputDimensione, inputRiga - 1, inputColonna - 1, inputValore);
    if (valido) {
      scrivereValGrigliaPartita(&partita, inputValore, inputRiga - 1, inputColonna - 1);
      grigliaPiena = controllareGrigliaPiena(leggereGrigliaPartita(partita));
    } else {
      errore = VERO;
    }
  }

  stampareVittoria();
}

void stampareTitoloPartita() {
  pulireSchermo();
  printf("\n");
  stampareCentrato("                    _   _ _              ");
  stampareCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ");
  stampareCentrato("|___|  | . | .'|  _|  _| |  _| .'|  |___|");
  stampareCentrato("       |  _|__,|_| |_| |_|_| |__,|       ");
  stampareCentrato("       |_|                               ");
  printf("\n");
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

  tornareHomepage(&input, INPUT_RIGA - 10, 30);
}

void stampareAiutiInput() {
  int i = 0;
  
  spostareCursore(INPUT_RIGA_RIGA - 2 , INPUT_COLONNA - 2);
  printf("+------------+\n");
  spostareCursore(INPUT_RIGA_RIGA - 3 , INPUT_COLONNA - 2);
  printf("|   Input    |\n");
  spostareCursore(INPUT_RIGA_RIGA - 4 , INPUT_COLONNA - 2);
  printf("+------------+\n");
  while (i < 8) {
    spostareCursore(INPUT_RIGA_RIGA - 1 + i, INPUT_COLONNA - 2);
    printf("|            |\n");
    i = i + 1;
  }
  spostareCursore(INPUT_RIGA_RIGA + 7 , INPUT_COLONNA - 2);
  printf("+------------+\n");

  spostareCursore(INPUT_RIGA_RIGA - 1, INPUT_COLONNA + 1);
  printf("-Riga-");
  spostareCursore(INPUT_RIGA_COLONNA - 1, INPUT_COLONNA);
  printf("-Colonna-");
  spostareCursore(INPUT_RIGA_VALORE - 1, INPUT_COLONNA);
  printf("-Valore-");
  spostareCursore(25, 17);
  printf("\033[34mDIGITA 32 per HOMEPAGE   |   DIGITA 31 per SALVARE\033[0m");
}

void convertiDifficoltaEDimensione(int *inputDifficolta, int *inputDimensione) {
  if (*inputDifficolta == 1) {
    *inputDifficolta = 4;
  } else if (*inputDifficolta == 2) {
    *inputDifficolta = 9;
  } else if (*inputDifficolta == 3) {
    *inputDifficolta = 16;
  }

  if (*inputDimensione == 1) {
    *inputDimensione = 4;
  } else if (*inputDimensione == 2) {
    *inputDimensione = 9;
  } else if (*inputDimensione == 3) {
    *inputDimensione = 16;
  }
}

void rimuovereNumeri(Griglia *griglia, int dimensione, int difficolta) {
  int celleRimuovere;
  srand(time(NULL));

  if (difficolta == 4) { // Facile (dimensione 4)
    celleRimuovere = 6;
  } else if (difficolta == 9) { // Facile (dimensione 9)
    celleRimuovere = 40;
  } else if (difficolta == 16) { // Facile (dimensione 16)
    celleRimuovere = 150;
  }


  int rimosse = 0;
  while (rimosse < celleRimuovere) {
    int riga = rand() % dimensione;
    int colonna = rand() % dimensione;

    if (leggereValGriglia(*griglia, riga, colonna) != 0) {
      scrivereValGriglia(griglia, riga, colonna, 0);
      rimosse = rimosse + 1;
    }
  }
}

int verificaValidita(Griglia *griglia, int dimensione, int riga, int colonna, int numero) {
  int i = 0;
  int esito = VERO;

  // Controlla riga
  while (i < dimensione && esito) { // CORREZIONE: esce al primo conflitto
    if (leggereValGriglia(*griglia, riga, i) == numero) {
      esito = FALSO;
    }
    i = i + 1;
  }

  // Controlla colonna
  i = 0;
  while (i < dimensione && esito) { // CORREZIONE: esce al primo conflitto
    if (leggereValGriglia(*griglia, i, colonna) == numero) {
      esito = FALSO;
    }
    i = i + 1;
  }

  // Controlla sottoquadrato
  if (esito) { // CORREZIONE: controlla solo se ancora valido
    int dimensioneQuadrato = (int)sqrt(dimensione);
    int inizioRiga = riga - riga % dimensioneQuadrato;
    int inizioColonna = colonna - colonna % dimensioneQuadrato;

    i = 0;
    while (i < dimensioneQuadrato && esito) {
      int j = 0;
      while (j < dimensioneQuadrato && esito) {
        if (leggereValGriglia(*griglia, i + inizioRiga, j + inizioColonna) == numero) {
          esito = FALSO;
        }
        j = j + 1;
      }
      i = i + 1;
    }
  }
  return esito;
}

// Funzione per riempire completamente la griglia
int riempireGriglia(Griglia *griglia, int dimensione) {
  int riga = 0;
  int colonna = 0;
  int trovato = 0;

  // Trova la prima cella vuota
  while (riga < dimensione && !trovato) {
    colonna = 0;
    while (colonna < dimensione && !trovato) {
      if (leggereValGriglia(*griglia, riga, colonna) == 0) {
        trovato = 1;
      } else {
        colonna = colonna + 1;
      }
    }
    if (!trovato) {
      riga = riga + 1;
    }
  }

  // Se non ci sono celle vuote, la griglia è completa
  if (riga == dimensione) {
    return VERO;
  }

  // Prova numeri da 1 alla dimensione
  int numero = 1;
  while (numero <= dimensione) {
    if (verificaValidita(griglia, dimensione, riga, colonna, numero)) {
      scrivereValGriglia(griglia, riga, colonna, numero);

      // Ricorsione per riempire il resto
      if (riempireGriglia(griglia, dimensione)) {
        return VERO;
      }

      // Backtrack
      scrivereValGriglia(griglia, riga, colonna, 0);
    }
    numero = numero + 1;
  }

  return FALSO;
}

void generareSudoku(Partita *partita, int dimensione, int difficolta) {
  riempireGriglia(&partita->grigliaPartita, dimensione);
  rimuovereNumeri(&partita->grigliaPartita, dimensione, difficolta);
}

void stampareGrigliaPartita(Partita *partita) {
    int i;
    int j;
    int numeroSottoquadrato;
    Griglia griglia = leggereGrigliaPartita(*partita);
    int dimensione = leggereDimGriglia(griglia);
    
    // Determina la dimensione del sottoquadrato
    if(dimensione == 4) {
        numeroSottoquadrato = 2;
    } else if(dimensione == 9) {
        numeroSottoquadrato = 3;
    } else if(dimensione == 16) {
        numeroSottoquadrato = 4;
    }

    printf("    ");
    for (j = 0; j < dimensione; j++) {
        if (dimensione == 16 && j + 1 < 10) {
            printf("  %d", j + 1);  // Numeri a una cifra nella 16x16
        } else {
            printf("%3d", j + 1);
        }
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
            printf("  ");
        }
    }
    
    printf("\n");
    
    // Stampa la linea superiore
    printf("   +");
    for (j = 0; j < dimensione; j++) {
        if (dimensione == 16) {
            printf("---");
        } else {
            printf("---");
        }
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
            printf("-+");
        }
    }
    printf("-+\n");
    
    // Stampa le righe con i numeri
    for (i = 0; i < dimensione; i++) {
        // Stampa l'indice della riga
        if (dimensione == 16) {
            printf("%2d |", i + 1);
        } else {
            printf("%2d |", i + 1);
        }
        
        // Stampa i valori della riga
        for (j = 0; j < dimensione; j++) {
            int valore = leggereValGriglia(griglia, i, j);
            if (valore == 0) {
                if (dimensione == 16) {
                    printf("  .");
                } else {
                    printf("  .");
                }
            } else {
                if (dimensione == 16) {
                    printf("%3d", valore);
                } else {
                    printf("%3d", valore);
                }
            }
            
            // Stampa il separatore verticale tra sottoquadrati
            if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
                printf(" |");
            }
        }
        printf(" |\n");
        
        // Stampa la linea di separazione orizzontale tra sottoquadrati
        if ((i + 1) % numeroSottoquadrato == 0 && i != dimensione - 1) {
            printf("   +");
            for (j = 0; j < dimensione; j++) {
                if (dimensione == 16) {
                    printf("---");
                } else {
                    printf("---");
                }
                if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
                    printf("-+");
                }
            }
            printf("-+\n");
        }
    }
    
    // Stampa la linea inferiore
    printf("   +");
    for (j = 0; j < dimensione; j++) {
        if (dimensione == 16) {
            printf("---");
        } else {
            printf("---");
        }
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
            printf("-+");
        }
    }
    printf("-+\n");
}

int collezionaRiga(Griglia *griglia, int *inputRiga) {
  int valida = 0;

  while(!valida) {
    resetZonaInput(INPUT_RIGA_RIGA, INPUT_COLONNA);

    while(scanf("%d", inputRiga) != 1) {
      pulireBuffer();
      resetZonaInput(INPUT_RIGA_RIGA, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA_RIGA, INPUT_COLONNA);
    }

    pulireBuffer();

    if((*inputRiga < 1 || *inputRiga > leggereDimGriglia(*griglia)) && (*inputRiga != 32 && *inputRiga != 31)) {
      mostrareMessaggioErrore("Numero fuori intervallo", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA_RIGA, INPUT_COLONNA);
    } else if (*inputRiga == 32) {
      loopMenuPrincipale();
    } else { 
      valida = 1;
    }
  }
  return *inputRiga;
}

int collezionaColonna(Griglia *griglia, int *inputColonna) {
  int valida = 0;

  while(!valida) {
    resetZonaInput(INPUT_RIGA_COLONNA, INPUT_COLONNA);

    while(scanf("%d", inputColonna) != 1) {
      pulireBuffer();
      resetZonaInput(INPUT_RIGA_COLONNA, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA_COLONNA, INPUT_COLONNA);
    }

    pulireBuffer();

    if((*inputColonna < 1 || *inputColonna > leggereDimGriglia(*griglia)) && (*inputColonna != 32)) {
      mostrareMessaggioErrore("Numero fuori intervallo", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA_COLONNA, INPUT_COLONNA);
    } else if (*inputColonna == 32) {
      loopMenuPrincipale();
    } else { 
      valida = 1;
    }
  }
  return *inputColonna;
}

int collezionaValore(Griglia *griglia, int *inputValore) {
  int valida = 0;

  while(!valida) {
    resetZonaInput(INPUT_RIGA_VALORE, INPUT_COLONNA);

    while(scanf("%d", inputValore) != 1) {
      pulireBuffer();
      resetZonaInput(INPUT_RIGA_VALORE, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      resetZonaInput(INPUT_RIGA_VALORE, INPUT_COLONNA);
    }

    pulireBuffer();

    if((*inputValore < 1 || *inputValore > leggereDimGriglia(*griglia)) && (*inputValore != 32)) {
      mostrareMessaggioErrore("Numero fuori intervallo", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA );
      resetZonaInput(INPUT_RIGA_VALORE, INPUT_COLONNA);
    } else if (*inputValore == 32) {
      loopMenuPrincipale();
    } else { 
      valida = 1;
    }
  }
  return *inputValore;
}

int controllareGrigliaPiena(Griglia griglia) {
  int dimensione = leggereDimGriglia(griglia);
  int riga, colonna;
  int esito = VERO;

  riga = 0;
  while (riga < dimensione && esito) { 
    colonna = 0;
    while (colonna < dimensione && esito) { 
      if (leggereValGriglia(griglia, riga, colonna) == 0) {
        esito = FALSO; 
      }
      colonna = colonna + 1;
    }
    riga = riga + 1; 
  }
  return esito;
}

/* Salva la partita in formato testuale semplice */
int salvaPartita(Partita *partita, const char *percorso) {
  FILE *file = fopen(percorso, "w");
  if (!file) return 0;

  int dimensione = leggereDimGriglia(partita->grigliaPartita);
  int difficolta = leggereDimGrigliaImp(partita->impPartita); /* reuse dimension diff value */

  fprintf(file, "%d %d\n", dimensione, difficolta);
  /* salva valori griglia */
  for (int i = 0; i < dimensione; i++) {
    for (int j = 0; j < dimensione; j++) {
      fprintf(file, "%d ", leggereValGriglia(partita->grigliaPartita, i, j));
    }
    fprintf(file, "\n");
  }
  fclose(file);
  return 1;
}

/* Carica la partita */
int caricaPartita(Partita *partita, const char *percorso) {
  FILE *file = fopen(percorso, "r");
  if (!file) return 0;
  int dimensione, difficolta;
  if (fscanf(file, "%d %d", &dimensione, &difficolta) != 2) { fclose(file); return 0; }

  /* inizializza struttura */
  inizializzareGrigliaPartita(partita, difficolta, dimensione); // dimensione convertita dentro

  /* leggi griglia */
  for (int i = 0; i < dimensione; i++) {
    for (int j = 0; j < dimensione; j++) {
      int val;
      if (fscanf(file, "%d", &val) != 1) { fclose(file); return 0; }
      scrivereValGrigliaPartita(partita, val, i, j);
    }
  }
  fclose(file);
  return 1;
}

void loopPartitaContinuata(Partita *partita) {
  int dimensione = leggereDimGriglia(partita->grigliaPartita);
  int inputValore, inputRiga, inputColonna;
  int grigliaPiena = FALSO;
  int valido = FALSO;
  int errore = FALSO;

  while (!grigliaPiena) {
    if (dimensione != 16) {
      stampareTitoloPartita();
    } else {
      pulireSchermo();
      printf("\n");
    }

    stampareGrigliaPartita(partita);
    stampareAiutiInput();

    if (errore) {
      mostrareMessaggioErrore("Inserisci i valori richiesti", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      errore = FALSO;
    }

    Griglia griglia = leggereGrigliaPartita(*partita);

    collezionaRiga(&griglia, &inputRiga);
    if (inputRiga == 31) {
      char percorso[256];
      snprintf(percorso, sizeof(percorso), "database/partita_%s.txt", partita->nomePartita);
      salvaPartita(partita, percorso);
      int tmp; tornareHomepage(&tmp, INPUT_RIGA + 5, 30);
      continue;
    }
    collezionaColonna(&griglia, &inputColonna);
    collezionaValore(&griglia, &inputValore);

    valido = verificaValidita(&griglia, dimensione, inputRiga - 1, inputColonna - 1, inputValore);
    if (valido) {
      scrivereValGrigliaPartita(partita, inputValore, inputRiga - 1, inputColonna - 1);
      grigliaPiena = controllareGrigliaPiena(leggereGrigliaPartita(*partita));
    } else {
      errore = VERO;
    }
  }

  stampareVittoria();
}
