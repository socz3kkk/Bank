#include "BazaDanych.h"
#include "Uzytkownik.h"

#include <fstream>
#include <sstream>

using namespace std;

BazaDanych::BazaDanych(string sciezka)
{
    sciezkaPliku = sciezka;
}

void BazaDanych::zapiszDane(const vector<Uzytkownik*>& baza)
{
    ofstream plik(sciezkaPliku);

    if (!plik.is_open())
        return;

    for (Uzytkownik* u : baza)
    {
        plik
            << u->getImie() << ";"
            << u->getNazwisko() << ";"
            << u->getPesel() << ";"
            << u->getHaslo()
            << endl;
    }

    plik.close();
}

vector<Uzytkownik*> BazaDanych::wczytajDane()
{
    vector<Uzytkownik*> wynik;

    ifstream plik(sciezkaPliku);

    if (!plik.is_open())
        return wynik;

    string linia;

    while (getline(plik, linia))
    {
        stringstream ss(linia);

        string imie;
        string nazwisko;
        string pesel;
        string haslo;

        getline(ss, imie, ';');
        getline(ss, nazwisko, ';');
        getline(ss, pesel, ';');
        getline(ss, haslo, ';');

        wynik.push_back(
            new Uzytkownik(
                imie,
                nazwisko,
                pesel,
                haslo
            )
        );
    }

    return wynik;
}
