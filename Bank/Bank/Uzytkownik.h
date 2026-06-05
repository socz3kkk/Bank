#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Rachunek.h"

using namespace std;

class Uzytkownik {
private:
    string imie;
    string nazwisko;
    string pesel;
    string haslo;
    vector<unique_ptr<Rachunek>> mojeKonta;

public:
    Uzytkownik(const string& imie, const string& nazwisko, const string& pesel, const string& haslo);
    virtual ~Uzytkownik();

    void otworzKonto(const string& typKonta);
    void wyswietlKonta() const;
    void zamknijKonto(const string& numerKonta);
    Rachunek* pobierzRachunek(int indeks = 0);

    string getPesel() const;
    string getHaslo() const;
};