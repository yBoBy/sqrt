#ifndef FUNCTIONS
#define FUNCTIONS
#include <cstdio>
#include <chrono>
using namespace std::chrono;

const int ANZAHL_TESTZYKLEN = 1000000;

typedef struct sqrt_obj {
	double zahl;
	double genauigkeit;
	double ergebnis_iterativ;
	double ergebnis_rekursiv;
	int zeit_iterativ;
	int zeit_rekursiv;
};



typedef struct heron_obj {
	double laenge;
	double breite;
	double differenz;
};

/*nähert laenge und breite einander an ohne das Produkt der beiden zu verändern*/
void berechneWurzelIterativ(heron_obj *ho, sqrt_obj *so);

/*
* Verfahren nach Heron:
* Ein Rechteck wird sukzessiv quadratischer und die Form behält jedesmal seinen Flaecheninhalt.
* Wobei der Flaecheninhalt die Zahl ist, deren Quadratwurzel wir suchen.
* Die Seitenlaenge (man kann sich eine aussuchen) ist dann unsere Annäherung an die Quadratwurzel.
* Und die Differenz der beiden Seitenlaengen (die sich immer mehr annähern) ist unsere Genauigkeit.
*
* Struct ho : laenge, breite, differenz
* Struct so : zahl, genauigkeit, ergebnis, zeit_rekursiv, zeit_iterativ
* zahl - Die Zahl deren Quadratwurzel berechnet werden soll
* genauigkeit - Die Genauigkeit mit der die Zahl berechnet werden soll
* ergebnis - wird fuer die Rekursion nicht benoetigt - das Ergebnis ist die Rückgabe der Methode
* laenge - Eine Seite des Rechtecks
* breite - Die zweite Seite eines Rechtecks ACHTUNG - die breite muss beim ersten Aufruf kleiner als die zahl sein!
* differenz - der Unterschied der beiden Seitenlaengen
*/
double berechneWurzelRekursiv(heron_obj *ho, sqrt_obj *so);

/*
* Zeitmessung der rekursiven und der iterativen Funktion
* zur Berechnung der Quadratwurzel
* Ausgabe der Zeitmessung in der Konsole.
*/
void zeitmessung(heron_obj *ho, sqrt_obj *so);

/*Bringt das Heron-Objekt in den Ausgangs Zustand*/
void initHeronObject(heron_obj *ho, int zahl);

/*Fragt vom Nutzer die Daten zu Berechnung ab und gibt sie als sqrt_obj zurück*/
sqrt_obj userInput();

/*Gibt die errechneten Wwert formatiert in die Konsole aus*/
void ergebnisAusgabe(heron_obj *ho, sqrt_obj *so);

void addToList(sqrt_obj so);

#endif

