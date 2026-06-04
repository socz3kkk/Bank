#include "Rachunek.h"

Rachunek::Rachunek(string numer, double poczatkoweSaldo) {
    numerRachunku = numer;
    saldo = poczatkoweSaldo;
}

void Rachunek::wplac(double kwota) {
    saldo += kwota;
}

void Rachunek::wyplac(double kwota) {
    saldo -= kwota;
}

double Rachunek::pobierzSaldo() const {
    return saldo;
}

string Rachunek::pobierzNumer() const {
    return numerRachunku;
}