#include "Kredytowy.h"
#include <stdexcept>

Kredytowy::Kredytowy(const string& numer, const double poczatkowe_saldo, const double limit)
    : Rachunek(numer, poczatkowe_saldo), limit_kredytowy(limit) {
}

void Kredytowy::wyplac(const double kwota) {
    if (!czyKwotaPoprawna(kwota)) {
        throw std::invalid_argument("Kwota wyplaty musi byc dodatnia.");
    }
    if (saldo + limit_kredytowy < kwota) {
        throw std::invalid_argument("Przekroczono limit kredytowy.");
    }
    saldo -= kwota;
}