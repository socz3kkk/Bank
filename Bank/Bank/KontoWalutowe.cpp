#include "KontoWalutowe.h"
#include <iostream>
#include <stdexcept>

using namespace std;

KontoWalutowe::KontoWalutowe(string numerRachunku, double poczatkoweSaldo, string waluta, double kursWymiany)
    : Rachunek(numerRachunku, poczatkoweSaldo), waluta(waluta), kursWymiany(kursWymiany) {
}

void KontoWalutowe::wykonajOperacjeOkresowa() {
    cout << "[Konto Walutowe " << numerRachunku << "] Zweryfikowano stabilnosc waluty " << waluta << ". Kurs: " << kursWymiany << " PLN.\n";
}

void KontoWalutowe::wyplac(const double kwota) {
    if (!wyplacWalute(kwota)) {
        throw std::invalid_argument("Blad wyplaty: niepoprawna kwota lub brak srodkow w walucie " + waluta);
    }
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
    if (kwotaWaluty <= 0.0) return 0.0;
    if (saldo < kwotaWaluty) {
        cout << "Blad: Niewystarczajaco srodkow do przewalutowania.\n";
        return 0.0;
    }

    saldo -= kwotaWaluty;

    double wartoscBruttoPln = kwotaWaluty * kursWymiany;
    double prowizja = wartoscBruttoPln * (PROWIZJA_WYMIANY_PROCENT / 100.0);
    return wartoscBruttoPln - prowizja;
}

void KontoWalutowe::wyswietlInformacje() const {
    cout << "--- Konto Walutowe ---\n";
    cout << "Numer: " << numerRachunku << "\n";
    cout << "Saldo: " << saldo << " " << waluta << "\n";
    cout << "Obecny kurs wymiany (do PLN): " << kursWymiany << "\n";
}