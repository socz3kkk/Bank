#include "KontoWalutowe.h"
#include <iostream>

using namespace std;

KontoWalutowe::KontoWalutowe(string numerRachunku, double poczatkoweSaldo, string waluta, double kursWymiany)
    : Rachunek(numerRachunku, poczatkoweSaldo), waluta(waluta), kursWymiany(kursWymiany) {
}

void KontoWalutowe::wyswietlInformacje() const {
    cout << "--- Konto Walutowe ---\n";
    cout << "Numer: " << numerRachunku << "\n";
    cout << "Saldo: " << saldo << " " << waluta << "\n";
    cout << "Obecny kurs wymiany (do PLN): " << kursWymiany << "\n";
}