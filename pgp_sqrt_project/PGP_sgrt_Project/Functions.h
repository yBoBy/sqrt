#ifndef FUNCTIONS
#define FUNCTIONS

typedef struct sqrt_obj {
	double zahl;
	double genauigkeit;
	double ergebnis;
};

typedef struct heron_obj {
	double laenge;
	double breite;
	double differenz;
};

//n�hert laenge und breite einander an ohne das Produkt der beiden zu ver�ndern
void heron(heron_obj *ho, sqrt_obj *so);

//Fragt vom Nutzer die Daten zu Berechnung ab und gibt sie als sqrt_obj zur�ck
sqrt_obj userInput();

#endif

