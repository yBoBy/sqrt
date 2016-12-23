#include "Functions.h"


sqrt_obj resultList[10]; //Liste fuer 10 Ergebnisse

int main() {
	printf("Willkommen zur Wurzelberechnung nach dem Heron-Verfahren!\n");
	sqrt_obj so;
	heron_obj ho;
	char befehl[30];

	do {
		so = userInput(); //Werte zur Berechnung im sqrt_Object speichern
		initHeronObject(&ho, so.zahl); //Werte im Heron Objekt zur Berechnung setzen
		berechneWurzelIterativ(&ho, &so);
		initHeronObject(&ho, so.zahl); //Werte im Heron Objekt zur erneuten Berechnung zuruecksetzen
		so.ergebnis_rekursiv = berechneWurzelRekursiv(&ho, &so);
		zeitmessung(&ho, &so); //Zeitmessung durchfuehren
		ergebnisAusgabe(&ho, &so);
		ausgabeLetzte10Ergebnisse();
		addToList(so);
		printf("Enter /exit to exit or any key to continue: ");
		scanf_s("%30s", befehl, _countof(befehl));
	} while (0 != strcmp("/exit", befehl));

	return 0;
}

void initHeronObject(heron_obj *ho, int zahl) {
	ho->laenge =zahl;
	ho->breite =1;
	ho->differenz = ho->laenge- ho->breite;
}

sqrt_obj userInput() {
	sqrt_obj tmp;
	printf("\n\nBitte geben sie die Zahl ein deren Quadratwurzel berechnet werden soll:\n");
	scanf_s("%lf", &tmp.zahl);
	printf("Bitte geben sie die Genauigkeit ein, mit der die Quadratwurzel berechnet werden soll:\n");
	scanf_s("%lf", &tmp.genauigkeit);
	tmp.ergebnis_iterativ = 0;
	tmp.ergebnis_rekursiv = 0;
	tmp.zeit_iterativ = 0;
	tmp.zeit_rekursiv = 0;
	return tmp;
}


void berechneWurzelIterativ(heron_obj *ho, sqrt_obj *so) {
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

		so->ergebnis_iterativ = ho->laenge;
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
		//Rekursionsanker, hier bricht die Rekursion ab
		return ho->laenge; 
	}
	else {
		ho->laenge = (ho->laenge + ho->breite) / 2;
		ho->breite = so->zahl / ho->laenge;
		//Erneuter Aufruf der Funktion mit veraenderten Werten
		return berechneWurzelRekursiv(ho, so); 
	}
}


void zeitmessung(heron_obj *ho, sqrt_obj *so) {
	//Zeitberechnung fuer Iterative Methode
	const auto t3 = high_resolution_clock::now(); // t3 = Zeitpunkt vor der Test-Schleife (iterativ)
	for (size_t i = 0; i != ANZAHL_TESTZYKLEN; i++){
		initHeronObject(ho, so->zahl);
		berechneWurzelIterativ(ho, so);
	}
	const auto t4 = high_resolution_clock::now(); //t4 = Zeitpunkt nach der Test-Schleife (iterativ)
	so->zeit_iterativ = duration_cast<nanoseconds>(t4 - t3).count() / ANZAHL_TESTZYKLEN;


	//Zeitberechnung fuer Rekursive Methode
	const auto t1 = high_resolution_clock::now(); // t1 = Zeitpunkt vor der Test-Schleife (rekursiv)
	for (size_t i = 0; i != ANZAHL_TESTZYKLEN; i++){
		initHeronObject(ho, so->zahl);
		berechneWurzelRekursiv(ho, so);
	}
	const auto t2 = high_resolution_clock::now(); // t2 = Zeitpunkt nach der Test-Schleife (rekursiv)
	so->zeit_rekursiv = duration_cast<nanoseconds>(t2 - t1).count() / ANZAHL_TESTZYKLEN;
}

void ergebnisAusgabe(heron_obj *ho, sqrt_obj *so) {
	printf("---------------------------------------------------------------\n");

	printf("Berechnung fuer Zahl: %lf >>>> Genauigkeit: %lf", so->zahl, so->genauigkeit);

	printf("\nIterativ\n	Quadratwurzel: %lf \n	Zeit: %li Nanosekunden\n",
		so->ergebnis_iterativ, so->zeit_iterativ);

	printf("\n---------------------------------------------------------------\n");

	printf("Rekursiv\n	Quadratwurzel: %lf \n	Zeit: %li Nanosekunden",
		so->ergebnis_rekursiv, so->zeit_rekursiv);
	
	printf("\n---------------------------------------------------------------\n\n");

}


void ausgabeLetzte10Ergebnisse(){
	//Ausgabe letzten 10 Berechnungen
	printf("Die letzten 10 Berechnungen:\n");
	for (int i = 0; i < 10; i++) {
		if (resultList[i].zahl != 0)//Nur Eintraege aus der Liste ausgeben die ein Ergebnis haben
			printf("Zahl %7.2lf Ergebnis: %6.2lf interativ in %4.li ns, rekursiv in %4.li ns\n",
				resultList[i].zahl,
				resultList[i].ergebnis_iterativ, resultList[i].zeit_iterativ,
				resultList[i].zeit_rekursiv);
	}
}

void addToList(sqrt_obj so) {
	for (int i = 9; i>0; i--) {
		//Alles in der Liste eins nach hinten schieben, das letzte Element faellt raus
		resultList[i] = resultList[i-1];
	}
	//NeusteBerechnung hinzufuegen
	resultList[0] = so;
}