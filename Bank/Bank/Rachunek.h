#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Transakcja.h"

using namespace std;

class Rachunek {
private:
    string numerKonta;
    vector<Transakcja> historia;

protected:
    string walutaPodstawowa;
    double saldo;

public:
    Rachunek(const string& numer, double poczatkoweSaldo = 0.0, const string& waluta = "PLN");
    virtual ~Rachunek() = default;

    void wplac(double kwota);
    bool wyplac(double kwota);
    bool wykonajPrzelew(Rachunek* cel, double kwota);
    virtual void wyswietlSzczegoly() const;

    string pobierzNumer() const;
    double pobierzSaldo() const;
};