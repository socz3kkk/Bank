#pragma once
#include "Rachunek.h"
#include <string>
#include <iostream>

class KontoWalutowe : public Rachunek {
private:
    std::string waluta;
    double kursWymiany;
    static constexpr double PROWIZJA_WYMIANY_PROCENT = 2.0;

public:
    KontoWalutowe(std::string numerRachunku, double poczatkoweSaldo, std::string waluta, double kursWymiany);
    void wyswietlSzczegoly() const override;
    void wykonajOperacjeOkresowa();
    bool wyplac(double kwota);
    bool wplacWalute(double kwota);
    bool wyplacWalute(double kwota);
    double wymienNaPln(double kwotaWaluty);

    friend std::ostream& operator<<(std::ostream& os, const KontoWalutowe& konto);

    string getTypKonta() const override { return "Walutowe"; }
    double getKurs() const { return kursWymiany; }
};