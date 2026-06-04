#include "Rachunek.h"
#include "Transakcja.h"
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
    for (auto t : historia) {
        delete t;
    }
    historia.clear();
    cout << "[Rachunek] Zamknieto rachunek nr: " << numerKonta << endl;
}

void Rachunek::wplac(double kwota) {
    saldo += kwota;
    dodajTransakcje(new Transakcja(kwota, "Wplata"));
    cout << "[Rachunek] Wplata kwoty " << kwota << " " << walutaPodstawowa << " na rachunek " << numerKonta << endl;
}

void Rachunek::wyswietlSzczegoly() const {
    cout << "--- Szczegoly konta ---" << endl;
    cout << "Numer:  " << numerKonta << endl;
    cout << "Typ:    " << getTypString() << endl;
    cout << "Waluta: " << walutaPodstawowa << endl;
    cout << "Saldo:  " << saldo << " " << walutaPodstawowa << endl;

    if (!historia.empty()) {
        cout << "--- Historia Transakcji ---" << endl;
        for (auto t : historia) {
            t->wyswietlTransakcje();
        }
    }
    cout << "-----------------------" << endl;
}

bool Rachunek::wykonajPrzelew(Rachunek* cel, double kwota) {
    saldo -= kwota;
    cel->wplac(kwota);
    dodajTransakcje(new Transakcja(-kwota, "Przelew wychodzacy"));
    cout << "[Rachunek] Zlecono przelew z konta " << numerKonta << " na kwote: " << kwota << " " << walutaPodstawowa << endl;
    return true;
}

bool Rachunek::wyplac(double kwota) {
    saldo -= kwota;
    dodajTransakcje(new Transakcja(-kwota, "Wyplata"));
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

void Rachunek::dodajTransakcje(Transakcja* t) {
    historia.push_back(t);
}