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

  printf("\n");
  stampaCentrato(" ");
  stampaCentrato(" __           _       _           ");
  stampaCentrato("/ _\\_   _  __| | ___ | | ___   _  ");
  stampaCentrato("\\ \\| | | |/ _` |/ _ \\| |/ / | | | ");
  stampaCentrato("_\\ \\ |_| | (_| | (_) |   <| |_| | ");
  stampaCentrato("\\__/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_| ");
  stampaCentrato(" ");
  printf("\n");

  stampaCentrato("MODALITA':");
  printf("\n");
  stampaCentrato("~ Tutorial  ");
  stampaCentrato("~ Facile    ");
  stampaCentrato("~ Media     ");
  stampaCentrato("~ Difficile ");

}

