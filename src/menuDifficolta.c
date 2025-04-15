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
  printf("ciao sono nel menu Difficolta");
}
void collezionaInputMenuDifficolta(int *input){
  return;
}

