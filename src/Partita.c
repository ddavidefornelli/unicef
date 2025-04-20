#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partita.h"
#include "interfaccia_util.h"

#define INPUT_RIGA 23
#define INPUT_COLONNA 30

void loopPartita(){
  int input;
  system("clear || cls");
  stampaCentrato("                    _   _ _              ");
  stampaCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ");
  stampaCentrato("|___|  | . | .'|  _|  _| |  _| .'|  |___|");
  stampaCentrato("       |  _|__,|_| |_| |_|_| |__,|       ");
  stampaCentrato("       |_|                               ");
  tornareHompage(&input, INPUT_RIGA, INPUT_COLONNA);
}
 
//qui va messa la partita, griglia sudoku + tutto il resto della partita;
//generazione grilia, salvataggio griglia in file; e poi bho;
