#include "KontoWalutowe.h"
#include <iostream>
#include <stdexcept>

using namespace std;

KontoWalutowe::KontoWalutowe(string numerRachunku, double poczatkoweSaldo, string waluta, double kursWymiany)
    : Rachunek(numerRachunku, poczatkoweSaldo, waluta), waluta(waluta), kursWymiany(kursWymiany) {
    if (kursWymiany <= 0.0) {
        throw std::invalid_argument("Kurs wymiany musi byc wiekszy od zera.");
    }
    if (waluta.empty()) {
        throw std::invalid_argument("Nazwa waluty nie moze byc pusta.");
    }
}

void KontoWalutowe::wykonajOperacjeOkresowa() {
    cout << "[Konto Walutowe " << pobierzNumer() << "] Zweryfikowano stabilnosc waluty " << waluta << ". Kurs: " << kursWymiany << " PLN.\n";
}

bool KontoWalutowe::wyplac(double kwota) {
    if (kwota <= 0.0) return false;
    return wyplacWalute(kwota);
}

bool KontoWalutowe::wplacWalute(double kwota) {
    if (kwota <= 0.0) return false;
    saldo += kwota;
    return true;
}

bool KontoWalutowe::wyplacWalute(double kwota) {
    if (kwota <= 0.0) return false;
    if (saldo < kwota) return false;

    saldo -= kwota;
    return true;
}

double KontoWalutowe::wymienNaPln(double kwotaWaluty) {
    if (kwotaWaluty <= 0.0) {
        throw std::invalid_argument("Kwota do przewalutowania musi byc dodatnia.");
    }
    if (saldo < kwotaWaluty) {
        throw std::runtime_error("Niewystarczajaco srodkow do przewalutowania.");
    }

    saldo -= kwotaWaluty;

    double wartoscBruttoPln = kwotaWaluty * kursWymiany;
    double prowizja = wartoscBruttoPln * (PROWIZJA_WYMIANY_PROCENT / 100.0);
    return wartoscBruttoPln - prowizja;
}

void KontoWalutowe::wyswietlSzczegoly() const {
    cout << *this;
}

std::ostream& operator<<(std::ostream& os, const KontoWalutowe& konto) {
    os << "--- Konto Walutowe ---\n"
        << "Numer: " << konto.pobierzNumer() << "\n"
        << "Saldo: " << konto.saldo << " " << konto.waluta << "\n"
        << "Obecny kurs wymiany (do PLN): " << konto.kursWymiany << "\n";
    return os;
}