#include "Functions.h"

#include <iostream>
#include <cstdio>
#include <ctime>
#include <ratio>
#include <chrono>
#include <typeinfo>

using namespace std;
using namespace std::chrono;
const int ANZAHL_TESTZYKLEN = 9999999;



sqrt_obj userInput() {
	sqrt_obj tmp;
	printf("Bitte geben sie die Zahl ein deren Quadratwurzel berechnet werden soll:\n");
	scanf("%lf", &tmp.zahl);
	printf("Bitte geben sie die Genauigkeit ein, mit der die Quadratwurzel berechnet werden soll:\n");
	scanf("%lf", &tmp.genauigkeit);
	tmp.ergebnis = 0;
	return tmp;
}




void heron(heron_obj *ho, sqrt_obj *so) {
	while (ho->differenz > so->genauigkeit) {
		ho-> laenge = (ho->laenge + ho->breite)/2;
		ho->breite = so->zahl / ho->laenge;
		double differenz = ho->laenge - ho->breite;
		if (differenz >= 0) {
			ho->differenz = differenz;
		}
		else {
			ho->differenz = differenz * (-1);
		}

		so->ergebnis = ho->laenge;
	}
}

/*
* Verfahren nach Heron:
* Ein Rechteck wird sukzessiv quadratischer und die Form behält jedesmal seinen Flaecheninhalt.
* Wobei der Flaecheninhalt die Zahl ist, deren Quadratwurzel wir suchen.
* Die Seitenlaenge (man kann sich eine aussuchen) ist dann unsere Annäherung an die Quadratwurzel.
* Und die Differenz der beiden Seitenlaengen (die sich immer mehr annähern) ist unsere Genauigkeit.
*
* zahl - Die Zahl deren Quadratwurzel berechnet werden soll
* eps - Die Genauigkeit mit der die Zahl berechnet werden soll
* laenge - Eine Seite des Rechtecks
* breite - Die zweite Seite eines Rechtecks ACHTUNG - die breite muss beim ersten Aufruf kleiner als die zahl sein!
* double zahl, double eps, double laenge, double breite, double differenz
* ho - laenge, breite, differenz
* so - zahl genauigkeit ergebnis
*/

double berechneWurzelRekursiv(heron_obj *ho, sqrt_obj *so) {
	if ((ho->laenge - ho->breite) < so->genauigkeit) {
		return ho->laenge;
	}
	else {
		ho->laenge = (ho->laenge + ho->breite) / 2;
		ho->breite = so->zahl / ho->laenge;
		if (ho->laenge>ho->breite) {
			return berechneWurzelRekursiv(ho, so);
		}
		else return berechneWurzelRekursiv(ho, so);
	}
}


void zeitMessung(heron_obj *ho, sqrt_obj *so) {

	printf("\n---------------------------------------------------------------");
	const auto t3 = high_resolution_clock::now();
	for (size_t i = 0; i != ANZAHL_TESTZYKLEN; i++)
	{
		ho->laenge = so->zahl;
		ho->breite = 1;
		ho->differenz = 1;
		heron(ho, so);
	}
	const auto t4 = high_resolution_clock::now();
	printf("\n%i mal iteratriv: %li Millisekunden", 
		ANZAHL_TESTZYKLEN, duration_cast<milliseconds>(t4 - t3).count());
	printf("\n---------------------------------------------------------------");

	const auto t1 = high_resolution_clock::now();
	for (size_t i = 0; i != ANZAHL_TESTZYKLEN; i++)
	{
		ho->laenge = so->zahl;
		ho->breite = 1;
		ho->differenz = 1;
		berechneWurzelRekursiv(ho, so);
	}
	const auto t2 = high_resolution_clock::now();
	printf("\n%i mal rekursiv: %li Millisekunden",
		ANZAHL_TESTZYKLEN, duration_cast<milliseconds>(t2 - t1).count());
	printf("\n---------------------------------------------------------------");
}


int main() {
	sqrt_obj so = userInput();
	heron_obj ho;
	ho.laenge = so.zahl;
	ho.breite = 1;
	ho.differenz = 1;
	
	heron(&ho, &so);
	printf("---------------------------------------------------------------\n");
	printf("Heron iterativ: Quadratwurzel: %lf Genauigkeit: %lf\n", so.ergebnis, so.genauigkeit);

	ho.laenge = so.zahl;
	ho.breite = 1;
	ho.differenz = 1;
	printf("---------------------------------------------------------------\n");
	printf("Heron rekursiv: Quadratwurzel: %lf Genauigkeit: %lf\n", berechneWurzelRekursiv(&ho, &so), so.genauigkeit);

	zeitMessung(&ho, &so);

	getchar(); getchar();
	return 0;
}

