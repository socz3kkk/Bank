#pragma once
#include "Rachunek.h"
#include <string>

class KontoWalutowe : public Rachunek {
private:
    std::string waluta;
    double kursWymiany; 

    static constexpr double PROWIZJA_WYMIANY_PROCENT = 2.0;

public:
    KontoWalutowe(std::string numerRachunku, double poczatkoweSaldo, std::string waluta, double kursWymiany);

    bool wplacWalute(double kwota);
    bool wyplacWalute(double kwota);

    double wymienNaPln(double kwotaWaluty);

    void wyswietlInformacje() const override;
};