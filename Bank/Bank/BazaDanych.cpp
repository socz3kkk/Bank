#include "BazaDanych.h"
#include "Uzytkownik.h"
#include "Rachunek.h"
#include "Transakcja.h"

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

    for (auto* uzytkownik : baza)
    {
        plik << "UZYTKOWNIK;"
            << uzytkownik->getImie() << ";"
            << uzytkownik->getNazwisko() << ";"
            << uzytkownik->getPesel() << ";"
            << uzytkownik->getHaslo()
            << endl;

        for (auto* rachunek : uzytkownik->getKonta())
        {
            plik << "RACHUNEK;"
                << rachunek->getNumerKonta() << ";"
                << rachunek->getWaluta() << ";"
                << rachunek->getSaldo()
                << endl;

            for (const auto& transakcja : rachunek->getHistoria())
            {
                plik << "TRANSAKCJA;"
                    << transakcja.getIdTransakcji() << ";"
                    << transakcja.getTypOperacji() << ";"
                    << transakcja.getKwota() << ";"
                    << transakcja.getData()
                    << endl;
            }

            plik << "KONIEC_RACHUNKU" << endl;
        }

        plik << "KONIEC_UZYTKOWNIKA" << endl;
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
        if (linia.rfind("UZYTKOWNIK;", 0) == 0)
        {
            stringstream ss(linia);

            string typ;
            string imie;
            string nazwisko;
            string pesel;
            string haslo;

            getline(ss, typ, ';');
            getline(ss, imie, ';');
            getline(ss, nazwisko, ';');
            getline(ss, pesel, ';');
            getline(ss, haslo, ';');

            Uzytkownik* u =
                new Uzytkownik(
                    imie,
                    nazwisko,
                    pesel,
                    haslo
                );

            wynik.push_back(u);
        }
    }

    plik.close();

    return wynik;
}