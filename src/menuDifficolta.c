#include "interfaccia_util.h"
#include "menudifficolta.h"
#include <stdio.h>
#include <stdlib.h>

void loopMenuDifficolta(){
  int input;
  collezionaInputMenuDifficolta(&input);
  stampareMenuDifficolta();
}
void stampareMenuDifficolta(){
  system("clear || cls");
  spostaCursore(9, 0);
  stampaCentrato("- MENU DIFFICOLTA-");
  spostaCursore(11, 50);
  printf("[1] Facile");
  spostaCursore(12, 50);
  printf("[2] Intermedia");
  spostaCursore(13, 50);
  printf("[3] Difficile");
  spostaCursore(14, 50);
  printf("\033[31m[4] Esci \033[0m");
  spostaCursore(16, 48);
  printf("Inserisci una scelta (1 - 4)");
}
void collezionaInputMenuDifficolta(int *input){
  return;
}

