#pragma once
#include <string>
#include <iostream>

using namespace std;

class Rachunek {
protected:
    string numer_rachunku;
    double saldo;

    // Metoda weryfikujaca czy wprowadzona kwota jest dodatnia
    bool czyKwotaPoprawna(const double kwota) const;

public:
    Rachunek(const string& numer, const double poczatkowe_saldo);
    virtual ~Rachunek() = default;

    virtual void wplac(const double kwota);
    virtual void wyplac(const double kwota);
    virtual double pobierzSaldo() const;
    string pobierzNumer() const;

    // Przeciazenie operatora dla latwiejszego wypisywania w konsoli
    friend ostream& operator<<(ostream& os, const Rachunek& rachunek);
};