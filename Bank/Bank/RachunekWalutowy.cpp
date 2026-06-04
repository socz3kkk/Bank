#include "RachunekWalutowy.h"
#include <iostream>

using namespace std;

RachunekWalutowy::RachunekWalutowy(string numer, string waluta)
    : Rachunek(numer, TypRachunku::WALUTOWE, waluta) {
}

void RachunekWalutowy::wyswietlSzczegoly() const {
    Rachunek::wyswietlSzczegoly();
}