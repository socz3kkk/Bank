#pragma once
#include <string>
#include <vector>

using namespace std;

class Transakcja;

enum class TypRachunku { NORMALNE, OSZCZEDNOSCIOWE, WALUTOWE };

class Rachunek {
private:
    string numerKonta;
    TypRachunku typKonta;
    vector<Transakcja*> historia;

protected:
    string walutaPodstawowa;
    double saldo;

public:
    Rachunek(string numer = "BRAK", TypRachunku typ = TypRachunku::NORMALNE, string waluta = "PLN");
    virtual ~Rachunek();

    virtual void wplac(double kwota);
    virtual void wyswietlSzczegoly() const;
    virtual bool wykonajPrzelew(Rachunek* cel, double kwota);
    virtual bool wyplac(double kwota);

    string getNumerKonta() const;
    string getTypString() const;
    void dodajTransakcje(Transakcja* t);
};