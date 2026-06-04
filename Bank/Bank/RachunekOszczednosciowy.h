#pragma once
#include "Rachunek.h"

class RachunekOszczednosciowy : public Rachunek {
private:
    double oprocentowanie;

public:
    RachunekOszczednosciowy(string numer = "BRAK", double opr = 0.02);

    void naliczOdsetki();
    void wyswietlSzczegoly() const override;
};