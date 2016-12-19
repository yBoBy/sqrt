#include "Functions.h"


int main() {
	sqrt_obj so = userInput();
	heron_obj ho;
	initHeronObject(&ho, so.zahl);

	heron(&ho, &so);
	printf("---------------------------------------------------------------\n");
	printf("Heron iterativ: Quadratwurzel: %lf Genauigkeit: %f\n", so.ergebnis, so.genauigkeit);

	initHeronObject(&ho, so.zahl);
	printf("---------------------------------------------------------------\n");
	printf("Heron rekursiv: Quadratwurzel: %lf Genauigkeit: %f", berechneWurzelRekursiv(&ho, &so), so.genauigkeit);

	zeitmessung(&ho, &so);

	getchar(); getchar();
	return 0;
}

void initHeronObject(heron_obj *ho, int zahl) {
	ho->laenge =zahl;
	ho->breite =1;
	ho->differenz = ho->laenge- ho->breite;
}

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
	ho->differenz = ho->laenge - ho->breite;
	if (ho->differenz >= 0) {
		ho->differenz *=1;
	}
	else {
		ho->differenz *=-1;
	}

	while (ho->differenz > so->genauigkeit) {
		ho-> laenge = (ho->laenge + ho->breite)/2;
		ho->breite = so->zahl / ho->laenge;
		ho->differenz = ho->laenge - ho->breite;
		if (ho->differenz >= 0) {
			ho->differenz *= 1;
		}
		else {
			ho->differenz *= -1;
		}

		so->ergebnis = ho->laenge;
	}
}


double berechneWurzelRekursiv(heron_obj *ho, sqrt_obj *so) {
	if (ho->laenge - ho->breite >= 0) {
		ho->differenz = ho->laenge - ho->breite;
	}
	else {
		ho->differenz = ho->breite - ho->laenge;
	}

	if ((ho->differenz) < so->genauigkeit) {
		return ho->laenge;
	}
	else {
		ho->laenge = (ho->laenge + ho->breite) / 2;
		ho->breite = so->zahl / ho->laenge;

		return berechneWurzelRekursiv(ho, so);
	}
}


void zeitmessung(heron_obj *ho, sqrt_obj *so) {
	printf("\n---------------------------------------------------------------");
	const auto t3 = high_resolution_clock::now(); // Zeitpunkt vor der Test-Schleife
	for (size_t i = 0; i != ANZAHL_TESTZYKLEN; i++)
	{
		initHeronObject(ho, so->zahl);
		heron(ho, so);
	}
	const auto t4 = high_resolution_clock::now(); // Zeitpunkt nach der Test-Schleife
	printf("\n%i mal iteratriv: %li Nanosekunden", 
		ANZAHL_TESTZYKLEN, duration_cast<nanoseconds>(t4 - t3).count());
	printf("\n---------------------------------------------------------------");

	const auto t1 = high_resolution_clock::now(); // Zeitpunkt vor der Test-Schleife
	for (size_t i = 0; i != ANZAHL_TESTZYKLEN; i++)
	{
		initHeronObject(ho, so->zahl);
		berechneWurzelRekursiv(ho, so);
	}
	const auto t2 = high_resolution_clock::now(); // Zeitpunkt nach der Test-Schleife
	printf("\n%i mal rekursiv: %li Nanosekunden",
		ANZAHL_TESTZYKLEN, duration_cast<nanoseconds>(t2 - t1).count());
	printf("\n---------------------------------------------------------------");
}

