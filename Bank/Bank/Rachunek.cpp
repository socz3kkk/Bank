#include "Rachunek.h"
#include <iostream>

Rachunek::Rachunek(const string& numer, double poczatkoweSaldo, const string& waluta)
    : numerKonta(numer), saldo(poczatkoweSaldo > 0.0 ? poczatkoweSaldo : 0.0), walutaPodstawowa(waluta) {
}

void Rachunek::wplac(double kwota) {
    if (kwota > 0.0) {
        saldo += kwota;
    }
}

bool Rachunek::wyplac(double kwota) {
    if (kwota > 0.0 && saldo >= kwota) {
        saldo -= kwota;
        return true;
    }
    return false;
}

bool Rachunek::wykonajPrzelew(Rachunek* cel, double kwota) {
    if (cel != nullptr && cel != this && this->wyplac(kwota)) {
        cel->wplac(kwota);
        return true;
    }
    return false;
}

void Rachunek::wyswietlSzczegoly() const {
    cout << "Konto: " << numerKonta << " | Saldo: " << saldo << " " << walutaPodstawowa << "\n";
}

string Rachunek::pobierzNumer() const {
    return numerKonta;
}

double Rachunek::pobierzSaldo() const {
    return saldo;
}