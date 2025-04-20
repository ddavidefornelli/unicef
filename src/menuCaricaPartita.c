#include "interfaccia_util.h"
#include <stdio.h>
#include <stdlib.h>

#define INPUT_RIGA 23
#define INPUT_COLONNA 30

void stampareMenuCaricaPartita(){
  int input;
  system("clear || cls");
  stampaCentrato("                    _   _ _                  _         _              ");
  stampaCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ___| |_ _ ___| |_ ___    ___ ");
  stampaCentrato("|___|  | . | .'|  _|  _| |  _| -_|  |_ -| .'| | | | .'|  _| -_|  |___|");
  stampaCentrato("       |  _|__,|_| |_| |_|_| |___|  |___|__,|_|\\_/|__,|_| |___|       ");
  stampaCentrato("       |_|                                                            ");
  tornareHompage(&input, INPUT_RIGA, INPUT_COLONNA);
}
