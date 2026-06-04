#pragma once
#include <string>

using namespace std;

enum class TypRachunku { NORMALNE, OSZCZEDNOSCIOWE, WALUTOWE };

class Rachunek {
protected:
    string numerKonta;
    TypRachunku typKonta;
    string walutaPodstawowa;
    double saldo;

public:
    Rachunek(string numer, TypRachunku typ, string waluta);
    virtual ~Rachunek();

    virtual void wplac(double kwota);
    virtual bool wyplac(double kwota);
    virtual bool wykonajPrzelew(Rachunek* cel, double kwota);
    virtual void wyswietlSzczegoly() const;

    string getNumerKonta() const;
    string getTypString() const;
};