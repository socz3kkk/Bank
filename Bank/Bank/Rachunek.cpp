#include "Rachunek.h"
#include <iostream>

using namespace std;

Rachunek::Rachunek(string numer, TypRachunku typ, string waluta) {
    numerKonta = numer;
    typKonta = typ;
    walutaPodstawowa = waluta;
    saldo = 0.0;
}

Rachunek::~Rachunek() {
}

void Rachunek::wplac(double kwota) {
    saldo += kwota;
}

bool Rachunek::wyplac(double kwota) {
    saldo -= kwota;
    return true;
}

bool Rachunek::wykonajPrzelew(Rachunek* cel, double kwota) {
    saldo -= kwota;
    cel->wplac(kwota);
    return true;
}

void Rachunek::wyswietlSzczegoly() const {
    cout << numerKonta << "\n";
    cout << getTypString() << "\n";
    cout << walutaPodstawowa << "\n";
    cout << saldo << "\n";
}

string Rachunek::getNumerKonta() const {
    return numerKonta;
}

string Rachunek::getTypString() const {
    if (typKonta == TypRachunku::NORMALNE) return "Normalne";
    if (typKonta == TypRachunku::OSZCZEDNOSCIOWE) return "Oszczednosciowe";
    if (typKonta == TypRachunku::WALUTOWE) return "Walutowe";
    return "Nieznane";
}