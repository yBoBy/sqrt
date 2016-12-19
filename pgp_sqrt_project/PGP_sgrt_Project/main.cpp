#include <stdio.h>
#include "Functions.h"



sqrt_obj userInput() {
	sqrt_obj tmp;
	printf("Bitte geben sie die Zahl ein deren Quadratwurzel berechnet werden soll:\n");
	scanf_s("%lf", &tmp.zahl);
	printf("Bitte geben sie die Genauigkeit ein, mit der die Quadratwurzel berechnet werden soll:\n");
	scanf_s("%lf", &tmp.genauigkeit);
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

	printf("Quadratwurzel: %lf\n Genauigkeit: %lf\n", so.ergebnis, so.genauigkeit);
	while (getchar() == '\n') {

	}
	

	return 0;
}

