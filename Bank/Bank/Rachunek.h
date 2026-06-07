#pragma once
#include <string>
#include <iostream>

using namespace std;

class Rachunek {
protected:
    string numerRachunku;
    double saldo;

    bool czyKwotaPoprawna(const double kwota) const;

public:
    Rachunek(const string& numer, const double poczatkoweSaldo);
    virtual ~Rachunek() = default;

    virtual void wplac(const double kwota);
    virtual void wyplac(const double kwota);
    virtual double pobierzSaldo() const;
    string pobierzNumer() const;

    virtual void wyswietlInformacje() const;
    virtual void wykonajOperacjeOkresowa();

    friend ostream& operator<<(ostream& os, const Rachunek& rachunek);
};