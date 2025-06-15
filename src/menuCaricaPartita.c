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

/*
 * Funzione di utilità per contare e memorizzare i nomi delle partite salvate
 * all'interno della cartella "database". Vengono considerati solamente i file
 * che iniziano con il prefisso "partita_".
 * Ritorna il numero di file trovati mentre riempie l'array nomiPartite con
 * i nomi dei file (allocati dinamicamente tramite strdup).
 */
static int raccogliPartiteSalvate(char *nomiPartite[], int maxPartite) {
  DIR *dir = opendir("database");
  struct dirent *entry;
  int conteggio = 0;

  if (dir == NULL) {
    return 0; /* cartella mancante o non accessibile */
  }

  while ((entry = readdir(dir)) != NULL && conteggio < maxPartite) {
    /* Considera solo i file che iniziano con "partita_" */
    if (strncmp(entry->d_name, "partita_", 8) == 0) {
      /* Alloca dinamicamente una copia del nome */
      size_t len = strlen(entry->d_name) + 1;
      char *copia = (char *)malloc(len);
      if (copia == NULL) {
        continue; /* out-of-memory -> salta */
      }
      memcpy(copia, entry->d_name, len);
      nomiPartite[conteggio++] = copia;
    }
  }
  closedir(dir);
  return conteggio;
}

static void liberaPartite(char *nomiPartite[], int numero) {
  for (int i = 0; i < numero; i++) {
    free(nomiPartite[i]);
  }
}

/* Rimuove il carattere di newline finale da una stringa ottenuta con fgets */
static void rimuoviNewline(char *str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}

/* Ritorna il nome del file corrispondente all'input utente.
 * L'utente può digitare:
 *   - l'indice numerico mostrato nella lista (1, 2, ...)
 *   - il nome completo del file (es. "partita_testo.txt")
 *   - il nome senza prefisso (es. "testo.txt" o "testo")
 *   - il nome senza prefisso e senza estensione (es. "testo")
 * Restituisce puntatore al nome del file presente in nomiPartite, o NULL se
 * nessuna corrispondenza. Non duplicare nuovamente la stringa. */
static const char *matchFile(char *nomiPartite[], int numero, const char *input) {
  /* Se l'input è un numero valido */
  char *endptr;
  long idx = strtol(input, &endptr, 10);
  if (*endptr == '\0' && idx >= 1 && idx <= numero) {
    return nomiPartite[idx - 1];
  }

  /* Normalizza l'input rimuovendo il prefisso eventuale */
  const char *nome = input;
  if (strncmp(nome, "partita_", 8) == 0) {
    nome += 8;
  }

  /* Rimuove eventuale ".txt" finale per confronto */
  char buffer[128];
  strncpy(buffer, nome, sizeof(buffer) - 1);
  buffer[sizeof(buffer) - 1] = '\0';
  size_t len = strlen(buffer);
  if (len > 4 && strcmp(buffer + len - 4, ".txt") == 0) {
    buffer[len - 4] = '\0';
  }

  /* Confronta con ogni file salvato */
  for (int i = 0; i < numero; ++i) {
    const char *fileSalvato = nomiPartite[i];

    /* Verifica uguaglianza completa */
    if (strcmp(input, fileSalvato) == 0) {
      return fileSalvato;
    }

    /* Rimuove prefisso ed estensione dal nome file per confronto */
    const char *base = fileSalvato;
    if (strncmp(base, "partita_", 8) == 0) {
      base += 8;
    }
    char temp[128];
    strncpy(temp, base, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';
    size_t l = strlen(temp);
    if (l > 4 && strcmp(temp + l - 4, ".txt") == 0) {
      temp[l - 4] = '\0';
    }

    if (strcmp(buffer, temp) == 0) {
      return fileSalvato;
    }
  }
  return NULL;
}

void stampareMenuCaricaPartita(){
  char *nomiPartite[100]; /* limite massimo di partite elencabili */
  int numeroPartite;
  char nomeScelto[128];
  int inputHomepage;

  /* --- OUTPUT GRAFICO DEL TITOLO --- */
  pulireSchermo();
  stampareCentrato("                    _   _ _                  _         _              ");
  stampareCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ___| |_ _ ___| |_ ___    ___ ");
  stampareCentrato("|___|  | . | .'|  _|  _| |  _| -_|  |_ -| .'| | | | .'|  _| -_|  |___|");
  stampareCentrato("       |  _|__,|_| |_| |_|_| |___|  |___|__,|_|\\_/|__,|_| |___|       ");
  stampareCentrato("       |_|                                                            ");

  /* --- RACCOLTA PARTITE SALVATE --- */
  numeroPartite = raccogliPartiteSalvate(nomiPartite, 100);

  if (numeroPartite == 0) {
    printf("\n\n");
    stampareCentrato("Nessuna partita salvata trovata.");
    tornareHomepage(&inputHomepage, INPUT_RIGA, INPUT_COLONNA);
    return;
  }

  /* --- STAMPA ELENCO PARTITE --- */
  for (int i = 0; i < numeroPartite; i++) {
    spostareCursore(OPZIONE_START_RIGA + i, OPZIONE_COLONNA);
    printf("[%d] %s", i + 1, nomiPartite[i]);
  }

  /* --- PROMPT DI INPUT PER IL NOME --- */
  spostareCursore(PROMPT_RIGA, PROMPT_COLONNA);
  printf("Digita il NUMERO o NOME della partita da caricare");

  int inMenuCarica = 1;
  while (inMenuCarica) {
    resetZonaInput(INPUT_RIGA, INPUT_COLONNA);

    /* Legge l'intera linea dall'utente */
    if (fgets(nomeScelto, sizeof(nomeScelto), stdin) == NULL) {
      continue; /* errore di lettura, riprova */
    }
    rimuoviNewline(nomeScelto);

    /* Consente all'utente di tornare indietro digitando 0 */
    if (strcmp(nomeScelto, "0") == 0) {
      tornareHomepage(&inputHomepage, INPUT_RIGA + 2, INPUT_COLONNA);
      break;
    }

    const char *fileMatch = matchFile(nomiPartite, numeroPartite, nomeScelto);
    if (fileMatch == NULL) {
      mostrareMessaggioErrore("Partita non trovata", ERR_MSG_RIGA, ERR_MSG_COLONNA);
      continue;
    }

    char percorso[256];
    snprintf(percorso, sizeof(percorso), "database/%s", fileMatch);

    /* Placeholder: caricamento effettivo */
    Partita partita;
    if (!caricaPartita(&partita, percorso)) {
      mostrareMessaggioErrore("Errore nel caricamento", ERR_MSG_RIGA, ERR_MSG_COLONNA);
      continue;
    }

    /* Estrai nome dal file path per memorizzarlo */
    const char *lastSlash = strrchr(fileMatch, '_');
    if (lastSlash) {
      scrivereNomePartita(&partita, (char *)(lastSlash + 1));
    }

    loopPartitaContinuata(&partita);
    inMenuCarica = 0;
  }

  liberaPartite(nomiPartite, numeroPartite);
}
