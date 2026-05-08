#include "Rachunek.h"
#include <iostream>

using namespace std;

Rachunek::Rachunek(string numer, TypRachunku typ, string waluta) {
    this->numerKonta = numer;
    this->typKonta = typ;
    this->walutaPodstawowa = waluta;
    this->saldo = 0.0;
    cout << "[Rachunek] Utworzono rachunek nr: " << numerKonta << " (Typ: " << getTypString() << ", " << walutaPodstawowa << ")" << endl;
}

Rachunek::~Rachunek() {
    cout << "[Rachunek] Zamknieto rachunek nr: " << numerKonta << endl;
}

void Rachunek::wplac(double kwota) {
    if (kwota <= 0) {
        cout << "[Blad] Kwota wplaty musi byc dodatnia." << endl;
        return;
    }
    saldo += kwota;
    cout << "[Rachunek] Wplata kwoty " << kwota << " " << walutaPodstawowa << " na rachunek " << numerKonta << endl;
}

void Rachunek::wyswietlSzczegoly() const {
    cout << "--- Szczegoly konta ---" << endl;
    cout << "Numer:  " << numerKonta << endl;
    cout << "Typ:    " << getTypString() << endl;
    cout << "Waluta: " << walutaPodstawowa << endl;
    cout << "Saldo:  " << saldo << " " << walutaPodstawowa << endl;
    cout << "-----------------------" << endl;
}

bool Rachunek::wykonajPrzelew(Rachunek* cel, double kwota) {
    if (kwota <= 0 || kwota > saldo) {
        cout << "[Blad] Brak srodkow lub niepoprawna kwota do przelewu." << endl;
        return false;
    }
    saldo -= kwota;
    cout << "[Rachunek] Zlecono przelew z konta " << numerKonta << " na kwote: " << kwota << " " << walutaPodstawowa << endl;
    return true;
}

bool Rachunek::wyplac(double kwota) {
    if (kwota <= 0 || kwota > saldo) {
        cout << "[Blad] Niewystarczajace srodki na wyplate." << endl;
        return false;
    }
    saldo -= kwota;
    cout << "[Rachunek] Wyplata " << kwota << " " << walutaPodstawowa << " z rachunku " << numerKonta << endl;
    return true;
}

string Rachunek::getNumerKonta() const {
    return numerKonta;
}

string Rachunek::getTypString() const {
    switch (typKonta) {
    case TypRachunku::NORMALNE: return "Normalne";
    case TypRachunku::OSZCZEDNOSCIOWE: return "Oszczednosciowe";
    case TypRachunku::WALUTOWE: return "Walutowe";
    default: return "Nieznane";
    }
}