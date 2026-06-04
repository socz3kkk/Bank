#include "RachunekOszczednosciowy.h"
#include "Transakcja.h"
#include <iostream>

using namespace std;

RachunekOszczednosciowy::RachunekOszczednosciowy(string numer, double opr)
    : Rachunek(numer, TypRachunku::OSZCZEDNOSCIOWE, "PLN") {
    this->oprocentowanie = opr;
}

void RachunekOszczednosciowy::naliczOdsetki() {
    double odsetki = saldo * oprocentowanie;
    saldo += odsetki;
    dodajTransakcje(new Transakcja(odsetki, "Naliczenie odsetek"));
}

void RachunekOszczednosciowy::wyswietlSzczegoly() const {
    Rachunek::wyswietlSzczegoly();
    cout << "Oprocentowanie: " << (oprocentowanie * 100) << "%" << endl;
    cout << "-----------------------" << endl;
}