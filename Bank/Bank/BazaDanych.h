#pragma once

#include <vector>
#include <memory>
#include <string>

using namespace std;

class Uzytkownik;

/**
 * @class BazaDanych
 * @brief Odpowiada za zapis i odczyt danych systemu bankowego.
 */
class BazaDanych
{
private:
    string nazwaPliku;

public:

    /**
     * @brief Tworzy obiekt bazy danych.
     * @param plik Nazwa pliku JSON.
     */
    BazaDanych(const string& plik);

    /**
     * @brief Zapisuje dane uzytkownikow do pliku.
     * @param uzytkownicy Lista uzytkownikow systemu.
     * @throws std::runtime_error Gdy nie mozna otworzyc pliku.
     */
    void zapiszDane(
        const vector<unique_ptr<Uzytkownik>>& uzytkownicy);

    /**
     * @brief Wczytuje dane uzytkownikow z pliku.
     * @param uzytkownicy Kontener na wczytanych uzytkownikow.
     */
    void wczytajDane(
        vector<unique_ptr<Uzytkownik>>& uzytkownicy);
};