#include "interfaccia_util.h"
#include "partita.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

int raccogliPartiteSalvate(char *nomiPartite[], int massimePartite) {
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

void liberaPartite(char *nomiPartite[], int numero) {
  int i = 0;
  while (i < numero) {
    if (nomiPartite[i] != NULL) {
      free(nomiPartite[i]);
    }
    i = i + 1;
  }
}

const char *trovaFile(char *nomiPartite[], int numero, const char *input) {
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

void stampareMenuCaricaPartita(){
  char *nomiPartite[100];
  int numeroPartite;
  char nomeScelto[128];
  int i;

  pulireSchermo();
  stampareCentrato("CARICA PARTITA");

  numeroPartite = raccogliPartiteSalvate(nomiPartite, 100);

  if (numeroPartite == 0) {
    printf("Nessuna partita salvata.\n");
    getchar();
    return;
  }

  i = 0;
  while (i < numeroPartite) {
    printf("[%d] %s\n", i + 1, nomiPartite[i]);
    i = i + 1;
  }

  printf("Digita numero o nome (0 per uscire): ");

  int continua = 1;
  while (continua) {
    if (fgets(nomeScelto, 128, stdin) != NULL) {
      nomeScelto[strlen(nomeScelto) - 1] = '\0';

      if (strcmp(nomeScelto, "0") == 0) {
        continua = 0;
      } else {
        const char *file = trovaFile(nomiPartite, numeroPartite, nomeScelto);
        if (file != NULL) {
          char percorso[256];
          Partita partita;
          sprintf(percorso, "database/%s", file);
          
          if (caricaPartita(&partita, percorso)) {
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
            loopPartitaContinuata(&partita);
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

  liberaPartite(nomiPartite, numeroPartite);
}
