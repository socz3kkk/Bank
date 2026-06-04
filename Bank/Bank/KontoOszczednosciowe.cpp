#include "KontoOszczednosciowe.h"
#include <iostream>

using namespace std;

KontoOszczednosciowe::KontoOszczednosciowe(string numerRachunku, double poczatkoweSaldo, double oprocentowanie)
    : Rachunek(numerRachunku, poczatkoweSaldo), oprocentowanie(oprocentowanie) {
}

void KontoOszczednosciowe::naliczOdsetki() {
    double odsetki = saldo * (oprocentowanie / 100.0);
    saldo += odsetki;
    cout << "Naliczono odsetki: " << odsetki << " PLN.\n";
}

void KontoOszczednosciowe::wyswietlInformacje() const {
    cout << "--- Konto Oszczędnościowe ---\n";
    cout << "Numer: " << numerRachunku << "\n";
    cout << "Saldo: " << saldo << " PLN\n";
    cout << "Oprocentowanie: " << oprocentowanie << "%\n";
}