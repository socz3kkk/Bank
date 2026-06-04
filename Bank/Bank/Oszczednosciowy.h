#pragma once
#include "Rachunek.h"

class Oszczednosciowy : public Rachunek {
private:
    double oprocentowanie;

public:
    Oszczednosciowy(const string& numer, const double poczatkowe_saldo, const double procent);
    void wplac(const double kwota) override;
    void naliczOdsetki();
};