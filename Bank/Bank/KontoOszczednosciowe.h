#pragma once
#include "Rachunek.h" 
#include <string>

class KontoOszczednosciowe : public Rachunek {
private:
    double oprocentowanie;

public:
    KontoOszczednosciowe(std::string numerRachunku, double poczatkoweSaldo, double oprocentowanie);

    void naliczOdsetki();

    void wyswietlInformacje() const override;
};