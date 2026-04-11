#pragma once
#include <string>
#include <vector>
#include "Rachunek.h"

using namespace std;

class Uzytkownik {
private:
    string imie;
    string nazwisko;
    string pesel;
    string nrTelefonu;
    string panienskieMatki;
    string adresZameldowania;
    string haslo;

    vector<Rachunek*> mojeKonta;

public:
    Uzytkownik(string im, string naz, string p, string tel,
        string pan, string adres, string h);

    ~Uzytkownik();

    string getPesel() const;
    bool sprawdzHaslo(string podaneHaslo) const;

    void wybierzKonto(string numerKonta);
    void otworzNoweKonto(Rachunek* noweKonto);
};