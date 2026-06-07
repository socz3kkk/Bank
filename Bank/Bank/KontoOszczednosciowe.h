#pragma once
#include "Rachunek.h" 
#include <string>
#include <iostream>

class KontoOszczednosciowe : public Rachunek {
private:
    double oprocentowanie;
    int liczbaWyplat;
    static constexpr int MAX_DARMOWYCH_WYPLAT = 1;
    static constexpr double OPLATA_ZA_WYPLATE = 10.0;

public:
    KontoOszczednosciowe(std::string numerRachunku, double poczatkoweSaldo, double oprocentowanie);

    void wyswietlSzczegoly() const override;

    void wykonajOperacjeOkresowa();
    bool wyplac(double kwota);

    friend std::ostream& operator<<(std::ostream& os, const KontoOszczednosciowe& konto);
};