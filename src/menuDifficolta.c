#include "interfaccia_util.h"
#include "menudifficolta.h"
#include "partita.h"
#include <stdio.h>
#include <stdlib.h>

int inMenuDifficolta = 1;

void loopMenuDifficolta(){
  int input;
  stampareMenuDifficolta();
  collezionaInputMenuDifficolta(&input);
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
  while(inMenuDifficolta) {
    spostaCursore(17, 55);
    printf(">>            ");
    spostaCursore(17, 58);

    while(scanf("%d", input) != 1) {
      while(getchar() != '\n'); // pulisce il buffer

      spostaCursore(17, 55);
      printf(">>            ");

      spostaCursore(19, 50);
      printf("\033[31m Digita un Numero. \033[0m");
      spostaCursore(17, 58);
    }

    while(getchar() != '\n'); // <-- pulisce anche dopo un input valido
    if(*input < 1 || *input > 4) {
      spostaCursore(19, 50);
      printf("\033[31m      Riprova.     \033[0m");
      spostaCursore(17, 58);
    }

    else if (*input == 1) {
      loopPartita();
      inMenuDifficolta = 0;
    }
    else if (*input == 2) {
      loopPartita();
      inMenuDifficolta = 0;
    }
    else if (*input == 3) {
      loopPartita();
      inMenuDifficolta = 0;
    }
    else if (*input == 4) {
      exit(0);
    }
  }
}

