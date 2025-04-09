#ifndef HOMEPAGE_H
#define HOMEPAGE_H

typedef enum {
  LARGHEZZA_TERMINALE = 120,
  ALTEZZA_TERMINALE = 80
} terminale;

void stampaCentrato(const char *testo); /* centra una stringa quando viene stampata sul terminale. */
void stampaASinistra(const char *testo) ; /* Centra una stringa quando stampata sul terminale. */
void mostraMenu(); /* Stampa a video il menù di partenza */
void spostaCursore(int x, int y);
void collezionaInput(int *input); /* recupera un input da terminale inserito dall'utente */

#endif
