#pragma once
#include <string>
#include <vector>

using namespace std;

class Transakcja;

class Rachunek {
private:
    string numerKonta;
    vector<Transakcja*> historia;  // ZMIANA: wskaźniki zamiast obiektów

protected:
    string walutaPodstawowa;
    double saldo;

public:
    Rachunek(string numer, string waluta);
    virtual ~Rachunek();

    void wplac(double kwota);
    virtual void wyswietlSzczegoly();
    bool wykonajPrzelew(Rachunek* cel, double kwota);
    bool wyplac(double kwota);

    string getNumerKonta() const;
};