#include "BazaDanych.h"
#include "Uzytkownik.h"

#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

BazaDanych::BazaDanych(const string& plik)
    : nazwaPliku(plik)
{
}

void BazaDanych::zapiszDane(
    const vector<unique_ptr<Uzytkownik>>& uzytkownicy)
{
    json dane;

    dane["uzytkownicy"] = json::array();

    for (const auto& uzytkownik : uzytkownicy)
    {
        json klient;

        klient["imie"] =
            uzytkownik->getImie();

        klient["nazwisko"] =
            uzytkownik->getNazwisko();

        klient["pesel"] =
            uzytkownik->getPesel();

        klient["haslo"] =
            uzytkownik->getHaslo();

        dane["uzytkownicy"].push_back(
            klient);
    }

    ofstream plik(nazwaPliku);

    if (!plik.is_open())
    {
        return;
    }

    plik << dane.dump(4);

    plik.close();
}

void BazaDanych::wczytajDane(
    vector<unique_ptr<Uzytkownik>>& uzytkownicy)
{
    ifstream plik(nazwaPliku);

    if (!plik.is_open())
    {
        return;
    }

    json dane;

    plik >> dane;

    if (!dane.contains("uzytkownicy"))
    {
        return;
    }

    for (const auto& klient : dane["uzytkownicy"])
    {
        auto nowyUzytkownik =
            make_unique<Uzytkownik>(
                klient["imie"],
                klient["nazwisko"],
                klient["pesel"],
                klient["haslo"]);

        uzytkownicy.push_back(
            move(nowyUzytkownik));
    }

    plik.close();
}