#pragma once
#include <string>

using namespace std;

class Rachunek {
protected:
    string numerRachunku;
    double saldo;

public:
    Rachunek(string numer, double poczatkoweSaldo);
    virtual ~Rachunek() = default;

    virtual void wplac(double kwota);
    virtual void wyplac(double kwota);
    virtual double pobierzSaldo() const;
    string pobierzNumer() const;
};