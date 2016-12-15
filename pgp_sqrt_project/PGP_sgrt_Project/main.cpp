#include <stdio.h>
#include "Functions.h"



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
	if (ho->differenz < so->genauigkeit) {
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


int main() {
	sqrt_obj so = userInput();
	heron_obj ho;
	ho.laenge = so.zahl;
	ho.breite = 1;
	
	heron(&ho, &so);
	//führt Heron durch bis gewünschte Genauigkeit erreicht ist
	while (ho.differenz > so.genauigkeit) {
		heron(&ho, &so);
	}

	printf("Iterativ: Quadratwurzel: %lf\n Genauigkeit: %lf\n", so.ergebnis, so.genauigkeit);

	berechneWurzelRekursiv(&ho, &so);
	printf("Rekursiv: Quadratwurzel: %lf\n Genauigkeit: %lf\n", so.ergebnis, so.genauigkeit);


	while (getchar() == '\n') {

	}
	

	return 0;
}

