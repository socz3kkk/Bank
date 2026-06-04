#include "Rachunek.h"

Rachunek::Rachunek(const string& numer, const double poczatkowe_saldo)
    : numer_rachunku(numer), saldo(poczatkowe_saldo) {
}

void Rachunek::wplac(const double kwota) {
    saldo += kwota;
}

void Rachunek::wyplac(const double kwota) {
    saldo -= kwota;
}

double Rachunek::pobierzSaldo() const {
    return saldo;
}

string Rachunek::pobierzNumer() const {
    return numer_rachunku;
}