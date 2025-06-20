/*
AUTORI: Onofrio de Robertis
        Michele Amato

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
#include "tipiDiDato.h"
#include "partita.h"

// Funzioni per Griglia
int leggereDimGriglia(Griglia griglia) {
    return griglia.dimensioneGriglia;
}

int leggereValGriglia(Griglia griglia, int riga, int colonna) {
    return griglia.valoriGriglia[riga][colonna];
}

void scrivereDimGriglia(Griglia *griglia, int valore) {
    griglia->dimensioneGriglia = valore;
}

void scrivereValGriglia(Griglia *griglia, int i, int j, int valore) {
    griglia->valoriGriglia[i][j] = valore;
}

// Funzioni per Impostazioni
int leggereDifficoltaImp(Impostazioni imp) {
    return imp.difficolta;
}

int leggereDimGrigliaImp(Impostazioni imp) {
    return imp.dimensioneGriglia;
}

void scrivereDifficoltaImp(Impostazioni *imp, int valore) {
    imp->difficolta = valore;
}

void scrivereDimensioneImp(Impostazioni *imp, int valore) {
    imp->dimensioneGriglia = valore;
}

// Funzioni per Partita
Impostazioni leggereImpPartita(Partita partita) {
    return partita.impPartita;
}

Griglia leggereGrigliaPartita(Partita partita) {
    return partita.grigliaPartita;
}

char* leggereNomePartita(Partita *partita) {
    return partita->nomePartita;
}

void scrivereImpPartita(Partita *partita, int difficolta, int dimensione) {
    scrivereDifficoltaImp(&partita->impPartita, difficolta);
    scrivereDimensioneImp(&partita->impPartita, dimensione);
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

// Dichiarazione della funzione esterna
void convertiDifficoltaEDimensione(int *inputDifficolta, int *inputDimensione);

void inizializzareGrigliaPartita(Partita *partita, int inputDimensione) {
    int i = 0;  // Inizializza i
    int j;
    
    // Converti i valori prima di usarli
    convertiDimensione(&inputDimensione);
    
    scrivereDimGrigliaPartita(partita, inputDimensione);
         
    partita->grigliaPartita.valoriGriglia = malloc(inputDimensione * sizeof(int *));
    
    while (i < inputDimensione) {
        partita->grigliaPartita.valoriGriglia[i] = malloc(inputDimensione * sizeof(int));
        j = 0;  // Inizializza j per ogni riga
        while (j < inputDimensione) {
            partita->grigliaPartita.valoriGriglia[i][j] = 0; // Inizializza a zero
            j = j + 1;
        }
        i = i + 1;
    }
}