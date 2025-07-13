/*
AUTORI: Onofrio de Robertis
        Michele Amato
        DavideFornelli
        Giuliano Antoniciello

DATA INIZIO: 27/05/2025

NOME FILE: tipiDiDato.c

Scopo delle funzioni presenti:
- leggereDimGriglia: restituisce la dimensione della griglia.
- leggereValGriglia: restituisce il valore in una cella specifica della griglia.
- scrivereDimGriglia: imposta la dimensione della griglia.
- scrivereValGriglia: imposta un valore in una cella specifica della griglia.
- leggereDifficoltaImp: restituisce il campo difficoltà di Impostazioni.
- leggereDimGrigliaImp: restituisce il campo dimensione della griglia di Impostazioni.
- scrivereDifficoltaImp: imposta il campo difficoltà di Impostazioni.
- scrivereDimensioneImp: imposta il cmapo dimensione della griglia di Impostazioni.
- leggereImpPartita: restituisce il campo Impostazioni da una Partita.
- leggereGrigliaPartita: restituisce il campo Griglia di Partita.
- leggereNomePartita: restituisce il nome della partita.
- scrivereImpPartita: imposta i campi difficoltà e dimensione del campo impostazioni di Partita.
- scrivereNomePartita: imposta il nome della partita.
- scrivereDimGrigliaPartita: imposta il campo dimensione della griglia del campo Griglia di Partita.
- scrivereValGrigliaPartita: imposta un valore in una cella della Griglia di Partita.
- inizializzareGrigliaPartita: alloca e inizializza a zero la griglia di gioco con dimensione scelta.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tipiDiDato.h"
#include "../include/partita.h"

// Funzioni per Griglia
int leggereDimGriglia(Griglia griglia) {
    int valoreLetto;

    valoreLetto = griglia.dimensioneGriglia;
    return valoreLetto;
}

int leggereValGriglia(Griglia griglia, int riga, int colonna) {
    int valoreLetto;
    valoreLetto = griglia.valoriGriglia[riga][colonna];
    return valoreLetto;
}

void scrivereDimGriglia(Griglia *griglia, int valore) {
    griglia->dimensioneGriglia = valore;
}

void scrivereValGriglia(Griglia *griglia, int riga, int colonna, int valore) {
    griglia->valoriGriglia[riga][colonna] = valore;
}

// Funzioni per Impostazioni
int leggereDimGrigliaImp(Impostazioni imp) {
    int valoreLetto;

    valoreLetto = imp.dimensioneGriglia;
    return valoreLetto; 
}

int leggereDifficoltaImp(Impostazioni imp) {
    int valoreLetto;

    valoreLetto = imp.difficolta;
    return valoreLetto; 
}

void scrivereDifficoltaImp(Impostazioni *imp, int valore) {
    imp->difficolta = valore;
}

void scrivereDimensioneImp(Impostazioni *imp, int valore) {
    imp->dimensioneGriglia = valore;
}

// Funzioni per Partita
Impostazioni leggereImpPartita(Partita partita) {
    Impostazioni valoreLetto;

    valoreLetto = partita.impostazioniPartita;
    return valoreLetto;
}

Griglia leggereGrigliaPartita(Partita *partita) {
    Griglia grigliaLetta;

    grigliaLetta = partita->grigliaPartita;
    return grigliaLetta;
}

char* leggereNomePartita(Partita *partita) {
    char* nomeLetto;
    nomeLetto = partita->nomePartita;
    return nomeLetto;
}

void scrivereImpPartita(Partita *partita, int difficolta, int dimensione) {
    scrivereDifficoltaImp(&partita->impostazioniPartita, difficolta);
    scrivereDimensioneImp(&partita->impostazioniPartita, dimensione);
}

void scrivereNomePartita(Partita *partita, char nome[50]) {
    strcpy(partita->nomePartita, nome);
}

void scrivereDimGrigliaPartita(Partita *partita, int valore) {
    scrivereDimGriglia(&partita->grigliaPartita, valore);
}

void scrivereValGrigliaPartita(Partita *partita, int valore, int riga, int colonna) {
    scrivereValGriglia(&partita->grigliaPartita, riga, colonna, valore);
}


void inizializzareGrigliaPartita(Partita *partita, int dimensione) {
    int riga; // righe della griglia
    int colonna; // colonne della griglia 

    convertireDimensione(&dimensione);
    scrivereDimGrigliaPartita(partita, dimensione);
         
    partita->grigliaPartita.valoriGriglia = malloc(dimensione * sizeof(int *));
    
    riga = 0;
    while (riga < dimensione) {
        partita->grigliaPartita.valoriGriglia[riga] = malloc(dimensione * sizeof(int));
        colonna = 0;  
        while (colonna < dimensione) {
            partita->grigliaPartita.valoriGriglia[riga][colonna] = 0; // Inizializza a zero
            colonna = colonna + 1;
        }
        riga = riga + 1;
    }
}



// nel codice non utilizziamo il tipo di dato file e il tipo di dato cartella
// perche' ci danno problemi con l' esecuzione del programma...
// qui commentato c'e comunuque il codice dei tipi di dato + funzioni di accesso
//
//typedef struct {
//    char nomeFile[100];        
//   unsigned int posizione;    
//   char caratteri[MAX_CARATTERI];  
//} File;

//const char* leggereNomeFile(File file) {
//   return file.nomeFile;
//}

//unsigned int posLeggereFile(File file) {
//   return file.posizione;
//}

//void incPosizioneFile(File* file) {
//   file->posizione += 1;
//}

//char leggereCarattereFile(File* file) {
//    char valoreLetto = file->caratteri[file->posizione];
//    incPosizioneFile(file);
//    return valoreLetto;
//}

//void scrivereNomeFile(File* file, const char* nuovoNome) {
//    strncpy(file->nomeFile, nuovoNome, sizeof(file->nomeFile) - 1);
//    file->nomeFile[sizeof(file->nomeFile) - 1] = '\0'; 
//}

//void scrivereCarattereFile(File* file, char nuovoValore, unsigned int pos) {
//    if (pos < MAX_CARATTERI) {
//        file->caratteri[pos] = nuovoValore;
//        incPosizioneFile(file);
//    }
//}
//
// typedef struct {
//   File voci[MAX_VOCI]; 
//   unsigned int posizione; 
// Cartella;}
//
// File leggereProssimaVoce(Cartella* cartella) {
// File voceLetta = cartella->voci[cartella->posizione];
//    incPosizioneCartella(cartella);
//    return voceLetta;
//}
//
//char* ottenereNomeFile(File voce) {
//   return voce.nomeFile;
//}
//
//void incPosizioneCartella(Cartella* cartella) {
//   cartella->posizione += 1;
//}

//void scrivereVoce(Cartella* cartella, File voce) {
//   cartella->voci[cartella->posizione] = voce;
//   incPosizioneCartella(cartella);
//}


