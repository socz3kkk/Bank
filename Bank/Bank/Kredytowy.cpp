#include "Kredytowy.h"

Kredytowy::Kredytowy(const string& numer, const double poczatkowe_saldo, const double limit)
    : Rachunek(numer, poczatkowe_saldo), limit_kredytowy(limit) {
}

void Kredytowy::wyplac(const double kwota) {
    if (!czyKwotaPoprawna(kwota)) return;

    if (saldo + limit_kredytowy >= kwota) {
        saldo -= kwota;
    }
}