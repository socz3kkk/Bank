#include "Rachunek.h"
#include <stdexcept>

constexpr double MIN_KWOTA = 0.0;

Rachunek::Rachunek(const string& numer, const double poczatkoweSaldo)
    : numerRachunku(numer), saldo(poczatkoweSaldo > MIN_KWOTA ? poczatkoweSaldo : MIN_KWOTA) {
}

bool Rachunek::czyKwotaPoprawna(const double kwota) const {
    return kwota > MIN_KWOTA;
}

void Rachunek::wplac(const double kwota) {
    if (!czyKwotaPoprawna(kwota)) {
        throw invalid_argument("Kwota operacji musi byc dodatnia.");
    }
    saldo += kwota;
}

void Rachunek::wyplac(const double kwota) {
    if (!czyKwotaPoprawna(kwota)) {
        throw invalid_argument("Kwota operacji musi byc dodatnia.");
    }
    if (saldo < kwota) {
        throw invalid_argument("Brak wystarczajacych srodkow na koncie.");
    }
    saldo -= kwota;
}

double Rachunek::pobierzSaldo() const {
    return saldo;
}

string Rachunek::pobierzNumer() const {
    return numerRachunku;
}

void Rachunek::wyswietlInformacje() const {
    cout << "Konto: " << numerRachunku << " | Saldo: " << saldo << " PLN\n";
}

void Rachunek::wykonajOperacjeOkresowa() {
}

ostream& operator<<(ostream& os, const Rachunek& rachunek) {
    os << "Konto: " << rachunek.numerRachunku << ", Saldo: " << rachunek.saldo;
    return os;
}