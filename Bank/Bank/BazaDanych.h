#pragma once

#include <vector>
#include <memory>
#include <string>

class Uzytkownik;

class BazaDanych
{
private:
    string nazwaPliku;

public:
    BazaDanych(const string& plik);

    void zapiszDane(
        const vector<unique_ptr<Uzytkownik>>& uzytkownicy);

    void wczytajDane(
        vector<unique_ptr<Uzytkownik>>& uzytkownicy);
};