#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "interfaccia_util.h"
#include "tipiDiDato.h"
#include "partita.h"

#define INPUT_RIGA_RIGA 10
#define INPUT_RIGA_COLONNA 13
#define INPUT_RIGA_VALORE 16
#define INPUT_RIGA 23
#define INPUT_COLONNA 57
#define FALSO 0
#define VERO 1
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 32

void loopPartita(int inputDifficolta, int inputDimensione) {
  int input;
  Partita partita;
  int inputValore;
  int inputRiga;
  int inputColonna;
  int grigliaPiena = FALSO;
  int valido = FALSO;
  int errore = FALSO;

  inizializzareGrigliaPartita(&partita, inputDifficolta, inputDimensione);
  convertiDifficoltaEDimensione(&inputDifficolta, &inputDimensione);
  generareSudoku(&partita, inputDimensione, inputDifficolta);

  while (!grigliaPiena) {
    stampareTitoloPartita();
    stampareGrigliaPartita(&partita);
    stampareAiutiInput();

    if (errore) {
      mostrareMessaggioErrore("Inserisci i valori richiesti", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      errore = FALSO;
    }

    Griglia griglia = leggereGrigliaPartita(partita); 

    collezionaRiga(&griglia, &inputRiga);
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
  pulireSchermo()
  printf("\n");
  stampareCentrato("                    _   _ _              ");
  stampareCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ");
  stampareCentrato("|___|  | . | .'|  _|  _| |  _| .'|  |___|");
  stampareCentrato("       |  _|__,|_| |_| |_|_| |__,|       ");
  stampareCentrato("       |_|                               ");
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

  tornareHomepage(&input, INPUT_RIGA, 30);

}

void stampareAiutiInput() {
  spostareCursore(INPUT_RIGA_RIGA - 1, INPUT_COLONNA + 1);
  printf("-Riga-");
  spostareCursore(INPUT_RIGA_COLONNA - 1, INPUT_COLONNA);
  printf("-Colonna-");
  spostareCursore(INPUT_RIGA_VALORE - 1, INPUT_COLONNA);
  printf("-Valore-");
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

  if (difficolta == 4) { // Facile (dimensione 4)
    celleRimuovere = 6;
  } else if (difficolta == 9) { // Facile (dimensione 9)
    celleRimuovere = 40;
  } else if (difficolta == 16) { // Facile (dimensione 16)
    celleRimuovere = 150;
  }

  srand(time(NULL));

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
  // La griglia dovrebbe essere già inizializzata
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

  // Stampa la linea superiore
  j = 0;
  while (j < dimensione) {
    printf("%4d", j + 1);
    j = j + 1;
  }

  j = 0;
  printf("\n  +-");
  while (j < dimensione) {
    printf("--");
    if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
      printf("---");
    }
    j = j + 1;
  }
  printf("-+\n");

  // Stampa le righe con i numeri
  i = 0;
  while (i < dimensione) {

    printf("%d | ", i + 1);
    j = 0;
    while (j < dimensione) {
      int valore = leggereValGriglia(griglia, i, j);
      if (valore == 0) {
        printf("  ");
      } else {
        printf("%2d", valore);
      }

      if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
        printf(" | ");
      } else {
        printf(" ");
      }
      j = j + 1;
    }
    printf("|\n");

    // Stampa la linea di separazione tra i sottoquadrati
    if ((i + 1) % numeroSottoquadrato == 0 && i != dimensione - 1) {
      printf("+-");
      j = 0;
      while (j < dimensione) {
        printf("--");
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
          printf("-+-");
        }
        j = j + 1;
      }
      printf("-+\n");
    }
    i = i + 1;
  }

  // Stampa la linea inferiore
  printf("+-");
  j = 0;
  while (j < dimensione) {
    printf("--");
    if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
      printf("-+-");
    }
    j = j + 1;
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

    if(*inputRiga < 1 || *inputRiga > leggereDimGriglia(*griglia)) {
      mostrareMessaggioErrore("Numero fuori intervallo", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA - 5);
      resetZonaInput(INPUT_RIGA_RIGA, INPUT_COLONNA);
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

    if(*inputColonna < 1 || *inputColonna > leggereDimGriglia(*griglia)) {
      mostrareMessaggioErrore("Numero fuori intervallo", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA - 5);
      resetZonaInput(INPUT_RIGA_COLONNA, INPUT_COLONNA);
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

    if(*inputValore < 1 || *inputValore > leggereDimGriglia(*griglia)) {
      mostrareMessaggioErrore("Numero fuori intervallo", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA - 5);
      resetZonaInput(INPUT_RIGA_VALORE, INPUT_COLONNA);
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
  while (riga < dimensione && esito) { // CORREZIONE: esce al primo 0 trovato
    colonna = 0;
    while (colonna < dimensione && esito) { // CORREZIONE: esce al primo 0 trovato
      if (leggereValGriglia(griglia, riga, colonna) == 0) {
        esito = FALSO; // Trovata una cella vuota
      }
      colonna = colonna + 1; // CORREZIONE: incrementa colonna
    }
    riga = riga + 1; // CORREZIONE: incrementa riga
  }
  return esito;
}
