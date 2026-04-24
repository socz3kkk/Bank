#include "Rachunek.h"
#include <iostream>

using namespace std;

Rachunek::Rachunek(string numer, string waluta) {
    this->numerKonta = numer;
    this->walutaPodstawowa = waluta;
    this->saldo = 0.0;
    cout << "[Rachunek] Utworzono rachunek nr: " << numerKonta << " (" << walutaPodstawowa << ")" << endl;
}

Rachunek::~Rachunek() {
    cout << "[Rachunek] Zamknieto rachunek nr: " << numerKonta << endl;
}

void Rachunek::wplac(double kwota) {
    cout << "[Rachunek] Wplata kwoty " << kwota << " na rachunek " << numerKonta << endl;
}

void Rachunek::wyswietlSzczegoly() {
    cout << "[Rachunek] Szczegoly konta " << numerKonta << " | Saldo: " << saldo << " " << walutaPodstawowa << endl;
}

bool Rachunek::wykonajPrzelew(Rachunek* cel, double kwota) {
    cout << "[Rachunek] Zlecono przelew z konta " << numerKonta << " na kwote: " << kwota << endl;
    return false;
}

bool Rachunek::wyplac(double kwota) {
    cout << "[Rachunek] Wyplata " << kwota << " z rachunku " << numerKonta << endl;
    return false;
}

string Rachunek::getNumerKonta() const {
    return numerKonta;
}