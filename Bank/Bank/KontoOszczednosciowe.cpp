#include "KontoOszczednosciowe.h"
#include <iostream>
#include <stdexcept> // Do obsługi wyjątków zgodnie ze stylem klasy Kredytowy

using namespace std;

KontoOszczednosciowe::KontoOszczednosciowe(string numerRachunku, double poczatkoweSaldo, double oprocentowanie)
    : Rachunek(numerRachunku, poczatkoweSaldo), oprocentowanie(oprocentowanie), liczbaWyplat(0) {
}

void KontoOszczednosciowe::wykonajOperacjeOkresowa() {
    if (saldo <= 0.0) return;

    double odsetki = saldo * (oprocentowanie / 100.0);
    saldo += odsetki;
    cout << "[Konto Oszczednosciowe " << numerRachunku << "] Automatycznie naliczono odsetki: " << odsetki << " PLN.\n";
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
        throw std::invalid_argument("Brak wystarczajacych srodkow na koncie oszczednosciowym (uwzgledniajac prowizje).");
    }

    saldo -= calkowityKoszt;
    liczbaWyplat++;
}

void KontoOszczednosciowe::wyswietlInformacje() const {
    cout << "--- Konto Oszczednosciowe ---\n";
    cout << "Numer: " << numerRachunku << "\n";
    cout << "Saldo: " << saldo << " PLN\n";
    cout << "Oprocentowanie: " << oprocentowanie << "%\n";
    cout << "Wykonane wyplaty: " << liczbaWyplat << "\n";
}