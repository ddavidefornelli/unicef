#ifndef MENU_H
#define MENU_H

typedef enum {
  LARGHEZZA_TERMINALE = 120,
  ALTEZZA_TERMINALE = 80
} terminale;

void stampaCentrato(const char *testo); /* centra una stringa quando viene stampata sul terminale. */
void stampaASinistra(const char *testo) ; /* Centra una stringa quando stampata sul terminale. */
void spostaCursore(int x, int y);
 
void stampareMenuPrincipale(); /* Stampa a video il menù di partenza */
void stampareMenuStatistiche();
void stampareMenuCaricaPartita();
void stampareMenuPrincipale();
void stampareMenuDifficolta();

#endif
