#pragma once
#include "Rachunek.h" 
#include <string>

class KontoOszczednosciowe : public Rachunek {
private:
    double oprocentowanie;
    int liczbaWyplat;

    static constexpr int MAX_DARMOWYCH_WYPLAT = 1;
    static constexpr double OPLATA_ZA_WYPLATE = 10.0;

public:
    KontoOszczednosciowe(std::string numerRachunku, double poczatkoweSaldo, double oprocentowanie);

    void naliczOdsetki();
    bool wplac(double kwota);
    bool wyplac(double kwota);

    void wyswietlInformacje() const override;
};