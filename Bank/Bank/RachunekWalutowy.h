#pragma once
#include "Rachunek.h"
#include <string>

using namespace std;

class RachunekWalutowy : public Rachunek {
public:
    RachunekWalutowy(string numer = "BRAK", string waluta = "EUR");

    void wyswietlSzczegoly() const override;
};