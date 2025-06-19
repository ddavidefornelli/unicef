#include "homepage.h"
#include "partita.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "caricaPartita.h"
#include "interfaccia_util.h"

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

void liberarePartite(char *nomiPartite[], int numero) {
  int i = 0;
  while (i < numero) {
    if (nomiPartite[i] != NULL) {
      free(nomiPartite[i]);
    }
    i = i + 1;
  }
}

const char *trovareFile(char *nomiPartite[], int numero, const char *input) {
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
        const char *file = trovareFile(nomiPartite, numeroPartite, nomeScelto);
        if (file != NULL) {
          char percorso[256];
          Partita partita;
          sprintf(percorso, "database/%s", file);
          
          if (caricarePartita(&partita, percorso)) {
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
  liberarePartite(nomiPartite, numeroPartite);
}


