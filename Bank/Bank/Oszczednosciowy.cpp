#include "Oszczednosciowy.h"

Oszczednosciowy::Oszczednosciowy(const string& numer, const double poczatkowe_saldo, const double procent)
    : Rachunek(numer, poczatkowe_saldo), oprocentowanie(procent) {
}

void Oszczednosciowy::wplac(const double kwota) {
    if (!czyKwotaPoprawna(kwota)) return;
    saldo += (kwota + 1.0);
}

void Oszczednosciowy::naliczOdsetki() {
    if (saldo > 0) {
        saldo += saldo * oprocentowanie;
    }
}