#include "Rachunek.h"
#include <stdexcept>

constexpr double MIN_KWOTA = 0.0;

Rachunek::Rachunek(const string& numer, const double poczatkowe_saldo)
    : numer_rachunku(numer), saldo(poczatkowe_saldo > MIN_KWOTA ? poczatkowe_saldo : MIN_KWOTA) {
}

bool Rachunek::czyKwotaPoprawna(const double kwota) const {
    return kwota > MIN_KWOTA;
}

void Rachunek::wplac(const double kwota) {
    if (!czyKwotaPoprawna(kwota)) {
        throw invalid_argument("Kwota operacji musi byc dodatnia.");
    }
    saldo += kwota;
}

void Rachunek::wyplac(const double kwota) {
    if (!czyKwotaPoprawna(kwota)) {
        throw invalid_argument("Kwota operacji musi byc dodatnia.");
    }
    if (saldo < kwota) {
        throw invalid_argument("Brak wystarczajacych srodkow na koncie.");
    }
    saldo -= kwota;
}

double Rachunek::pobierzSaldo() const {
    return saldo;
}

string Rachunek::pobierzNumer() const {
    return numer_rachunku;
}

ostream& operator<<(ostream& os, const Rachunek& rachunek) {
    os << "Konto nr: " << rachunek.numer_rachunku << " | Saldo: " << rachunek.saldo << " PLN";
    return os;
}