#include "KontoOszczednosciowe.h"
#include <iostream>

using namespace std;

KontoOszczednosciowe::KontoOszczednosciowe(string numerRachunku, double poczatkoweSaldo, double oprocentowanie)
    : Rachunek(numerRachunku, poczatkoweSaldo), oprocentowanie(oprocentowanie), liczbaWyplat(0) {
}

void KontoOszczednosciowe::naliczOdsetki() {
    if (saldo <= 0.0) return;

    double odsetki = saldo * (oprocentowanie / 100.0);
    saldo += odsetki;
    cout << "Naliczono odsetki: " << odsetki << " PLN.\n";
}

bool KontoOszczednosciowe::wplac(double kwota) {
    if (kwota <= 0.0) return false;

    saldo += kwota;
    return true;
}

bool KontoOszczednosciowe::wyplac(double kwota) {
    if (kwota <= 0.0) return false;

    double calkowityKoszt = kwota;
    if (liczbaWyplat >= MAX_DARMOWYCH_WYPLAT) {
        calkowityKoszt += OPLATA_ZA_WYPLATE;
    }

    if (saldo < calkowityKoszt) {
        cout << "Blad: Brak wystarczajacych srodkow (uwzgledniajac potencjalne oplaty).\n";
        return false;
    }

    saldo -= calkowityKoszt;
    liczbaWyplat++;
    return true;
}

void KontoOszczednosciowe::wyswietlInformacje() const {
    cout << "--- Konto Oszczednosciowe ---\n";
    cout << "Numer: " << numerRachunku << "\n";
    cout << "Saldo: " << saldo << " PLN\n";
    cout << "Oprocentowanie: " << oprocentowanie << "%\n";
    cout << "Liczba wykonanych wyplat: " << liczbaWyplat << "\n";
}