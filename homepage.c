#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stampaCentrato(const char *TESTO);
void mostraMenu();

int main() {
  mostraMenu();
  getchar();
  return 0;
}

void stampaCentrato(const char *TESTO) {
  const int LARGHEZZA = 120;
  int len;
  int spazi; 
  int i;

  len = strlen(TESTO);
  spazi = (LARGHEZZA - len) / 2;

  if (spazi < 0) spazi = 0;

  i = 0;
  while(i < spazi){
    printf(" ");
    i = i + 1;
  }
  printf("%s\n", TESTO);
}

void mostraMenu() {
  int sceltaUtente;
  printf("\n");
  stampaCentrato(" ");
  stampaCentrato(" __           _       _           ");
  stampaCentrato("/ _\\_   _  __| | ___ | | ___   _  ");
  stampaCentrato("\\ \\| | | |/ _` |/ _ \\| |/ / | | | ");
  stampaCentrato("_\\ \\ |_| | (_| | (_) |   <| |_| | ");
  stampaCentrato("\\__/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_| ");
  stampaCentrato(" ");
  printf("\n");

  stampaCentrato("digita un numero per selezionare la modalita' di gioco e premi invio per confermare:");
  printf("\n");
  stampaCentrato("1) Tutorial  ");
  stampaCentrato("2) Facile    ");
  stampaCentrato("3) Media     ");
  stampaCentrato("4) Difficile ");
  /*scanf("%d", &sceltaUtente);*/
  /*printf("%d", sceltaUtente);*/
}

