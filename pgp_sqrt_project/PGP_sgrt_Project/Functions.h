#ifndef FUNCTIONS
#define FUNCTIONS
#include <cstdio>
#include <chrono>
using namespace std::chrono;

const int TEST_ITERATION_COUNT = 1000000;

struct sqrt_obj {
	double number;
	double precision;
	double resultIterativ;
	double resultRecursive;
	int timeIterativ;
	int timeRecursiv;
};

struct heron_obj {
	double length;
	double width;
	double difference;
};

/*nähert laenge und breite einander an ohne das Produkt der beiden zu verändern*/
void sqrtIterativ(heron_obj *ho, sqrt_obj *so);

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
double sqrtRecursive(heron_obj *ho, sqrt_obj *so);

/*
* Zeitmessung der rekursiven und der iterativen Funktion
* zur Berechnung der Quadratwurzel
* Ausgabe der Zeitmessung in der Konsole.
*/
void takeTimeRecursivVsIterativSqrt(heron_obj *ho, sqrt_obj *so);

/*Bringt das Heron-Objekt in den Ausgangs Zustand*/
void initHeronObject(heron_obj *ho, int zahl);

/*Fragt vom Nutzer die Daten zu Berechnung ab und gibt sie als sqrt_obj zurück*/
void userInput(sqrt_obj *so);

/*Gibt die errechneten Wwert formatiert in die Konsole aus*/
void ergebnisAusgabe(heron_obj *ho, sqrt_obj *so);

void addToList(sqrt_obj so, sqrt_obj *pointerToResultList);

void printLastTenResults(sqrt_obj *so);

void initResultArray(sqrt_obj *pointerToResultArray);

#endif

