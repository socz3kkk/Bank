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
    vector<Transakcja*> historia;  // ZMIANA: wskaźniki zamiast obiektów

protected:
    string walutaPodstawowa;
    double saldo;

public:
    // Konstruktor wspierający typ i domyślną walutę
    Rachunek(string numer, TypRachunku typ, string waluta = "PLN");
    virtual ~Rachunek();

    void wplac(double kwota);
    virtual void wyswietlSzczegoly() const;
    bool wykonajPrzelew(Rachunek* cel, double kwota);
    bool wyplac(double kwota);

    string getNumerKonta() const;
    string getTypString() const;
};