#include "KontoOszczednosciowe.h"
#include <iostream>
#include <stdexcept>

using namespace std;

KontoOszczednosciowe::KontoOszczednosciowe(string numerRachunku, double poczatkoweSaldo, double oprocentowanie)
    : Rachunek(numerRachunku, poczatkoweSaldo), oprocentowanie(oprocentowanie), liczbaWyplat(0) {
    if (oprocentowanie < 0) {
        throw std::invalid_argument("Oprocentowanie nie moze byc ujemne.");
    }
}

void KontoOszczednosciowe::wykonajOperacjeOkresowa() {
    if (saldo <= 0.0) return;

    double odsetki = saldo * (oprocentowanie / 100.0);
    saldo += odsetki;
    cout << "[Konto Oszczednosciowe " << numer_rachunku << "] Automatycznie naliczono odsetki: " << odsetki << " PLN.\n";
}

void KontoOszczednosciowe::wyplac(const double kwota) {
    if (kwota <= 0.0) {
        throw std::invalid_argument("Kwota wyplaty musi byc dodatnia.");
    }

    double calkowityKoszt = kwota;
    if (liczbaWyplat >= MAX_DARMOWYCH_WYPLAT) {
        calkowityKoszt += OPLATA_ZA_WYPLATE;
    }

    if (saldo < calkowityKoszt) {
        throw std::runtime_error("Brak wystarczajacych srodkow na koncie oszczednosciowym (uwzgledniajac prowizje " + to_string(OPLATA_ZA_WYPLATE) + " PLN).");
    }

    saldo -= calkowityKoszt;
    liczbaWyplat++;
}

void KontoOszczednosciowe::wyswietlInformacje() const {
    cout << *this;
}

std::ostream& operator<<(std::ostream& os, const KontoOszczednosciowe& konto) {
    os << "--- Konto Oszczednosciowe ---\n"
        << "Numer: " << konto.numer_rachunku << "\n"
        << "Saldo: " << konto.saldo << " PLN\n"
        << "Oprocentowanie: " << konto.oprocentowanie << "%\n"
        << "Wykonane wyplaty: " << konto.liczbaWyplat << "\n";
    return os;
}