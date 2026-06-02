#pragma once

#include <string>
#include <vector>

class Uzytkownik;

class BazaDanych
{
private:
    std::string sciezkaPliku;

public:
    BazaDanych(const std::string& sciezka);

    void zapiszDane(const std::vector<Uzytkownik*>& baza);

    std::vector<Uzytkownik*> wczytajDane();
};
