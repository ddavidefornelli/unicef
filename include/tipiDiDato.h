#ifndef TIPIDIDATO_H
#define TIPIDIDATO_H
// Definizione della struttura Griglia
typedef struct {
    int **valoriGriglia;
    int dimensioneGriglia;
} Griglia;

// Definizione della struttura Impostazioni
typedef struct {
    int difficolta;
    int dimensioneGriglia;
} Impostazioni;

// Definizione della struttura Partita
typedef struct {
    Griglia grigliaPartita;
    Impostazioni *impostazioniPartita;
    char nomePartita[50];
} Partita;

// Dichiarazioni delle funzioni per Griglia
int leggereDimGriglia(Griglia griglia);
int leggereValGriglia(Griglia griglia, int riga, int colonna);
void scrivereDimGriglia(Griglia *griglia, int valore);
void scrivereValGriglia(Griglia *griglia, int i, int j, int valore);

// Dichiarazioni delle funzioni per Impostazioni
int leggereDifficoltaImp(Impostazioni imp);
int leggereDimGrigliaImp(Impostazioni imp);
void scrivereDifficoltaImp(Impostazioni *imp, int *valore);
void scrivereDimensioneImp(Impostazioni *imp, int valore);

// Dichiarazioni delle funzioni per Partita
Impostazioni *leggereImpPartita(Partita *partita);
Griglia leggereGrigliaPartita(Partita *partita);
char* leggereNomePartita(Partita *partita);
void scrivereImpPartita(Partita *partita, int difficolta, int dimensione);
void scrivereNomePartita(Partita *partita, char nome[50]);
void scrivereDimGrigliaPartita(Partita *partita, int valore);
void scrivereValGrigliaPartita(Partita *partita, int valore, int riga, int colonna);
void inizializzareGrigliaPartita(Partita *partita, int inputDimensione);

#endif
