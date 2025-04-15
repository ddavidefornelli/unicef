#include "homepage.h"
#include "menu.h"
#include <stdio.h>

int main() 
{
  int scelta;
  stampareMenuPrincipale();
  collezionaInput(&scelta);
  getchar();
  return 0;
}

