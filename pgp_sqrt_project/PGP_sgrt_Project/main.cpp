#include "Functions.h"


const int lengthResultList = 10;

int main() {
	printf("Willkommen zur Wurzelberechnung nach dem Heron-Verfahren!\n");
	sqrt_obj so;
	heron_obj ho;
	/*Das Char Array nimmt Befehle des Benutzers auf.
	Anhand der Befehle wird entschieden ob das Programm verlassen werden soll*/
	char befehl[30];
	/*resultList - Platz fuer (lengthResultList) Berechnungen um diese
	später als eine Art Historie auf der Konsole auszugeben*/
	sqrt_obj resultList[lengthResultList];

	initResultArray(resultList);
	

	do {
		userInput(&so); //Werte zur Berechnung im sqrt_Object speichern
		initHeronObject(&ho, so.number); //Werte im Heron Objekt zur Berechnung setzen
		sqrtIterativ(&ho, &so);
		initHeronObject(&ho, so.number); //Werte im Heron Objekt zur erneuten Berechnung zuruecksetzen
		so.resultRecursive = sqrtRecursive(&ho, &so);
		takeTimeRecursivVsIterativSqrt(&ho, &so); //Zeitmessung durchfuehren
		ergebnisAusgabe(&ho, &so);
		printLastTenResults(resultList);
		addToList(so, resultList);
		printf("Enter 'exit' or any number to continue: ");
		scanf_s("%30s", befehl, _countof(befehl));
	} while (0 != strcmp("exit", befehl));
	
	return 0;
}

/*Startwerte festlegen die fuer die Berechnungen notwendig sind*/
void initHeronObject(heron_obj *ho, int zahl) {
	ho->length =zahl;
	ho->width =1;
	ho->difference = ho->length- ho->width;
}

void initResultArray(sqrt_obj *pointerToResultArray) {
	for (int i = 0; i < lengthResultList; i++) {
		pointerToResultArray->number = 0;
		pointerToResultArray++;
	}
}

/*Die Zahl deren Quadratwurzel berechnet werden soll einlesen
und die Genauigkeit mit der die Quadratwurzel berechnet werden soll einlesen*/
void userInput(sqrt_obj *so) {
	bool success = false;

	while (!success) {
		int c;
		printf("\n\nBitte geben sie die Zahl ein deren Quadratwurzel berechnet werden soll:\n");
		int statusScanNumber = scanf_s("%lf", &so->number);
		if (statusScanNumber == 0) {
			do c = getchar(); while (c!='\n'); //Fehleingaben abfangen
			printf("Bitte nur reele Zahlen eingeben. Neustart.\n");
			continue;
		}

		printf("Bitte geben sie die Genauigkeit ein, mit der die Quadratwurzel berechnet werden soll:\n");
		int statusScanPrecision = scanf_s("%lf", &so->precision);
		if (statusScanPrecision == 0) {
			do c = getchar(); while (c != '\n'); //Fehleingaben abfangen;
			printf("Bitte nur reele Zahlen eingeben. Neustart.\n");
			continue;
		}
		// Die restlichen Werte initalisieren
		so->resultIterativ = 0;
		so->resultRecursive = 0;
		so->timeIterativ = 0;
		so->timeRecursiv = 0;
		success = true;
	}
}


void sqrtIterativ(heron_obj *ho, sqrt_obj *so) {
	ho->difference = ho->length - ho->width;
	if (ho->difference >= 0) {
		ho->difference *=1;
	}
	else {
		ho->difference *=-1;
	}

	while (ho->difference > so->precision) {
		ho-> length = (ho->length + ho->width)/2;
		ho->width = so->number / ho->length;
		ho->difference = ho->length - ho->width;
		if (ho->difference >= 0) {
			ho->difference *= 1;
		}
		else {
			ho->difference *= -1;
		}
		so->resultIterativ = ho->length;
	}
}


double sqrtRecursive(heron_obj *ho, sqrt_obj *so) {
	if (ho->length - ho->width >= 0) {
		ho->difference = ho->length - ho->width;
	}
	else {
		ho->difference = ho->width - ho->length;
	}

	if ((ho->difference) < so->precision) {
		//Rekursionsanker, hier bricht die Rekursion ab
		return ho->length; 
	}
	else {
		ho->length = (ho->length + ho->width) / 2;
		ho->width = so->number / ho->length;
		//Erneuter Aufruf der Funktion mit veraenderten Werten
		return sqrtRecursive(ho, so); 
	}
}




void takeTimeRecursivVsIterativSqrt(heron_obj *ho, sqrt_obj *so) {
	//Zeitberechnung fuer Iterative Methode
	const auto t3 = high_resolution_clock::now(); // t3 = Zeitpunkt vor der Test-Schleife (iterativ)
	for (size_t i = 0; i != TEST_ITERATION_COUNT; i++){
		initHeronObject(ho, so->number);
		sqrtIterativ(ho, so);
	}
	const auto t4 = high_resolution_clock::now(); //t4 = Zeitpunkt nach der Test-Schleife (iterativ)
	so->timeIterativ = duration_cast<nanoseconds>(t4 - t3).count() / TEST_ITERATION_COUNT;


	//Zeitberechnung fuer Rekursive Methode
	const auto t1 = high_resolution_clock::now(); // t1 = Zeitpunkt vor der Test-Schleife (rekursiv)
	for (size_t i = 0; i != TEST_ITERATION_COUNT; i++){
		initHeronObject(ho, so->number);
		sqrtRecursive(ho, so);
	}
	const auto t2 = high_resolution_clock::now(); // t2 = Zeitpunkt nach der Test-Schleife (rekursiv)
	so->timeRecursiv = duration_cast<nanoseconds>(t2 - t1).count() / TEST_ITERATION_COUNT;
}

void ergebnisAusgabe(heron_obj *ho, sqrt_obj *so) {
	printf("---------------------------------------------------------------\n");

	printf("Berechnung fuer Zahl: %lf >>>> Genauigkeit: %lf", so->number, so->precision);

	printf("\nIterativ\n	Quadratwurzel: %lf \n	Zeit: %li Nanosekunden\n",
		so->resultIterativ, so->timeIterativ);

	printf("\n---------------------------------------------------------------\n");

	printf("Rekursiv\n	Quadratwurzel: %lf \n	Zeit: %li Nanosekunden",
		so->resultRecursive, so->timeRecursiv);
	
	printf("\n---------------------------------------------------------------\n\n");

}


void printLastTenResults(sqrt_obj pointerResultList[]){
	printf("Die letzten Berechnungen:\n");
	for (int i = 0; i < lengthResultList; i++) {
		if (pointerResultList->number != 0)//Nur Eintraege aus der Liste ausgeben die ein Ergebnis haben
			printf("Zahl %7.2lf Ergebnis: %6.2lf interativ in %4.li ns, rekursiv in %4.li ns\n",
				pointerResultList->number,
				pointerResultList->resultIterativ, pointerResultList->timeIterativ,
				pointerResultList->timeRecursiv);
		pointerResultList++;
	}
	
}

void addToList(sqrt_obj so, sqrt_obj pointerToResultList[]) {
	for (int i = lengthResultList-1; i>=0; i--) {
		//Alles in der Liste eins nach hinten schieben, das letzte Element faellt raus
		pointerToResultList[i] = pointerToResultList[i-1];
	}
	//NeusteBerechnung hinzufuegen
	pointerToResultList[0] = so;
}