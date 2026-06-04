#pragma once
#include <string>

using namespace std;

class Rachunek {
protected:
    string numer_rachunku;
    double saldo;

    // Metoda pomocnicza
    bool czyKwotaPoprawna(const double kwota) const;

public:
    Rachunek(const string& numer, const double poczatkowe_saldo);
    virtual ~Rachunek() = default;

    virtual void wplac(const double kwota);
    virtual void wyplac(const double kwota);
    virtual double pobierzSaldo() const;
    string pobierzNumer() const;
};