#include "Rachunek.h"

// Zastąpienie "magicznych liczb" stałą
constexpr double MIN_KWOTA = 0.0;

Rachunek::Rachunek(const string& numer, const double poczatkowe_saldo)
    : numer_rachunku(numer), saldo(poczatkowe_saldo > MIN_KWOTA ? poczatkowe_saldo : MIN_KWOTA) {
}

// Wydzielona metoda pomocnicza zgodnie z zasadą DRY
bool Rachunek::czyKwotaPoprawna(const double kwota) const {
    return kwota > MIN_KWOTA;
}

void Rachunek::wplac(const double kwota) {
    // Guard clause i walidacja warunków brzegowych
    if (!czyKwotaPoprawna(kwota)) return;

    saldo += kwota;
}

void Rachunek::wyplac(const double kwota) {
    // Guard clauses i walidacja warunków brzegowych
    if (!czyKwotaPoprawna(kwota)) return;
    if (saldo < kwota) return;

    saldo -= kwota;
}

double Rachunek::pobierzSaldo() const {
    return saldo;
}

string Rachunek::pobierzNumer() const {
    return numer_rachunku;
}