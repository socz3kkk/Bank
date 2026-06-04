#pragma once
#include "Rachunek.h"

class Kredytowy : public Rachunek {
private:
    double limit_kredytowy;

public:
    Kredytowy(const string& numer, const double poczatkowe_saldo, const double limit);
    void wyplac(const double kwota) override;
};