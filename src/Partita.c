#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partita.h"
#include "interfaccia_util.h"

void loopPartita(){
  system("clear || cls");
  stampaCentrato("                    _   _ _              ");
  stampaCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ");
  stampaCentrato("|___|  | . | .'|  _|  _| |  _| .'|  |___|");
  stampaCentrato("       |  _|__,|_| |_| |_|_| |__,|       ");
  stampaCentrato("       |_|                               ");
}
 
//qui va messa la partita, griglia sudoku + tutto il resto della partita;
//generazione grilia, salvataggio griglia in file; e poi bho;
