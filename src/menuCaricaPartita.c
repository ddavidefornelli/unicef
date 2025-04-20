#include "interfaccia_util.h"
#include <stdio.h>
#include <stdlib.h>

#define INPUT_RIGA 23
#define INPUT_COLONNA 30

void stampareMenuCaricaPartita(){
  int input;

  pulireSchermo();
  stampareCentrato("                    _   _ _                  _         _              ");
  stampareCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ___| |_ _ ___| |_ ___    ___ ");
  stampareCentrato("|___|  | . | .'|  _|  _| |  _| -_|  |_ -| .'| | | | .'|  _| -_|  |___|");
  stampareCentrato("       |  _|__,|_| |_| |_|_| |___|  |___|__,|_|\\_/|__,|_| |___|       ");
  stampareCentrato("       |_|                                                            ");

  tornareHompage(&input, INPUT_RIGA, INPUT_COLONNA);
}
