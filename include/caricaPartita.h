#ifndef CARICAPARTITA_H 
#define CARICAPARTITA_H

#include "interfaccia_util.h"

int raccoglierePartiteSalvate(char *nomiPartite[], int massimePartite);
void liberarePartite(char *nomiPartite[], int numero);
void stampareTitoloCaricaPartita();
void stampareZonaInput(); 
void stampareMenuCaricaPartita();

#endif

