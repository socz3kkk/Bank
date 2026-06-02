#pragma once

#include <vector>
#include <string>

using namespace std;

class Uzytkownik;

class BazaDanych {
private:
    string sciezkaPliku;

public:
    BazaDanych(string sciezka);

    void zapiszDane(const vector<Uzytkownik*>& baza);

    vector<Uzytkownik*> wczytajDane();
};
