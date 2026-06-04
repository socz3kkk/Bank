#pragma once
#include "Rachunek.h"
#include <string>

class KontoWalutowe : public Rachunek {
private:
    std::string waluta;
    double kursWymiany;

public:
    KontoWalutowe(std::string numerRachunku, double poczatkoweSaldo, std::string waluta, double kursWymiany);

    void wyswietlInformacje() const override;
};