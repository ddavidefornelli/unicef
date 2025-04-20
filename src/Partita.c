#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partita.h"
#include "interfaccia_util.h"

#define INPUT_RIGA 23
#define INPUT_COLONNA 30

void loopPartita(){
  int input;
  pulireSchermo();
  stampareCentrato("                    _   _ _              ");
  stampareCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ");
  stampareCentrato("|___|  | . | .'|  _|  _| |  _| .'|  |___|");
  stampareCentrato("       |  _|__,|_| |_| |_|_| |__,|       ");
  stampareCentrato("       |_|                               ");
  tornareHompage(&input, INPUT_RIGA, INPUT_COLONNA);
}
 
//qui va messa la partita, griglia sudoku + tutto il resto della partita;
//generazione grilia, salvataggio griglia in file; e poi bho;
