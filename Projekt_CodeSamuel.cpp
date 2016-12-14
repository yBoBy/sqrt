#include <iostream>
#include <cstdio>
#include <ctime>
#include <ratio>
#include <chrono>
#include <typeinfo>

using namespace std;
using namespace std::chrono;

const int ANZAHL_TESTZYKLEN = 999999;

/*
 * berechneWurzelIterativ(zahl, breiteErsterWert, eps)
 * zahl - Die Zahl deren Quadratwurzel berechnet werden soll
 * breiteErsterWert - die Funktion braucht einen ersten Wert fuer die Breite
 * eps - Die Genauigkeit mit der die Zahl berechnet werden soll
 */
double berechneWurzelIterativ(double zahl, double breiteErsterWert, double eps){
    double differenz = zahl-breiteErsterWert;
    // Abfrage damit ein beliebiger Wert beim Aufrufen eingesetzt werden kann
    if (zahl<breiteErsterWert) differenz =breiteErsterWert-zahl;
    double laenge = zahl;
    double breite = breiteErsterWert;
    while (differenz>eps){
        laenge=(laenge+breite)/2;
        breite = zahl/laenge;
        if(laenge>breite){
            differenz= laenge-breite;
        } else differenz = breite-laenge;
    }
    return laenge;
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
 */
double berechneWurzelRekursiv(double zahl, double eps, double laenge, double breite, double differenz){
    if (differenz < eps){
        return laenge;
    } else{
        laenge=(laenge+breite)/2;
        breite = zahl/laenge;
        if (laenge>breite) {
            return berechneWurzelRekursiv(zahl, eps, laenge, breite, laenge - breite);
        } else return berechneWurzelRekursiv(zahl, eps, laenge, breite, breite-laenge);
    }
}

void zahlUndGenauigkeitEinlesen(double *zahl, double *eps){
    printf("Bitte Zahl fuer die Quadratwurzelberchnung eingeben: \n");
    scanf("%lf", zahl);
    printf("Bitte die geforderte Genauigkeit eingeben \n");
    scanf("%lf", eps);
}

void ausgabeErgebnis(double zahl, double eps){
    printf("----------------------------------------------------------");
    const auto t3 = high_resolution_clock::now();
    for(size_t i = 0; i != ANZAHL_TESTZYKLEN; i++)
    {
        berechneWurzelIterativ(zahl, 1, eps);
    }
    printf("\nErgebnis iterativ: %f\n", berechneWurzelIterativ(zahl, 1, eps));
    const auto t4 = high_resolution_clock::now();
    cout << ANZAHL_TESTZYKLEN << " mal iterativ:\n"
         << duration_cast<milliseconds>(t4 - t3).count() << " Millisekunden\n";
    printf("----------------------------------------------------------");

    printf("----------------------------------------------------------");
    const auto t1 = high_resolution_clock::now();
    for(size_t i = 0; i != ANZAHL_TESTZYKLEN; i++)
    {
        berechneWurzelRekursiv(zahl, eps, zahl, 1, zahl-1);
    }
    printf("\nErgebnis rekursiv: %f\n", berechneWurzelRekursiv(zahl, eps, zahl, 1, zahl-1));
    const auto t2 = high_resolution_clock::now();
    cout << ANZAHL_TESTZYKLEN << " mal rekursiv:\n"
         << duration_cast<milliseconds>(t2 - t1).count() << " Millisekunden\n";
    printf("----------------------------------------------------------");
}

int main() {

    double zahl = 77.44; //Zahl deren Quadratwurzel berechnet werden soll
    double eps=0.000001; //Genauigkeit mit der die Quadratwurzel berechnet werden soll

    zahlUndGenauigkeitEinlesen(&zahl, &eps);
    ausgabeErgebnis(zahl, eps);

    return 0;
}