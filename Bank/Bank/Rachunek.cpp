#include "Rachunek.h"
#include <iostream>
#include <ctime>

string generujId() {
    static int licznik = 1000;
    return "TX-" + to_string(licznik++);
}

string pobierzDate() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    return to_string(1900 + ltm.tm_year) + "-" +
        to_string(1 + ltm.tm_mon) + "-" +
        to_string(ltm.tm_mday);
}

Rachunek::Rachunek(const string& numer, double poczatkoweSaldo, const string& waluta)
    : numerKonta(numer), saldo(poczatkoweSaldo > 0.0 ? poczatkoweSaldo : 0.0), walutaPodstawowa(waluta) {
}

void Rachunek::wplac(double kwota) {
    if (kwota > 0.0) {
        saldo += kwota;
        historia.push_back(Transakcja(generujId(), "Wplata Srodkow", kwota, pobierzDate()));
    }
}

bool Rachunek::wyplac(double kwota) {
    if (kwota > 0.0 && saldo >= kwota) {
        saldo -= kwota;
        historia.push_back(Transakcja(generujId(), "Wyplata Srodkow", kwota, pobierzDate()));
        return true;
    }
    return false;
}

bool Rachunek::wykonajPrzelew(Rachunek* cel, double kwota) {
    if (cel != nullptr && cel != this && this->wyplac(kwota)) {
        cel->wplac(kwota);
        historia.push_back(Transakcja(generujId(), "Przelew Wychodzacy", kwota, pobierzDate()));
        return true;
    }
    return false;
}

void Rachunek::wyswietlSzczegoly() const {
    cout << "Konto: " << numerKonta << " | Saldo: " << saldo << " " << walutaPodstawowa << "\n";
    if (!historia.empty()) {
        cout << "  Ostatnie transakcje na koncie:\n";
        for (const auto& tx : historia) {
            cout << "   -> " << tx << "\n";
        }
    }
}

string Rachunek::pobierzNumer() const {
    return numerKonta;
}

double Rachunek::pobierzSaldo() const {
    return saldo;
}