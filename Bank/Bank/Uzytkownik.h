#pragma once
#include <string>
#include <vector>
#include <memory> 
#include <iostream>
#include "Rachunek.h"

using namespace std;

/**
 * @class Uzytkownik
 * @brief Klasa reprezentujaca klienta banku i zarzadzajaca jego rachunkami.
 */
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

    /**
     * @brief Otwiera nowe konto dla uzytkownika.
     * @param typKonta Typ konta (Standardowe lub Kredytowe).
     * @throws std::length_error jesli osiagnieto limit kont.
     * @throws std::invalid_argument jesli podano nieznany typ konta.
     */
    void otworzKonto(const string& typKonta);

    /**
     * @brief Wyswietla wszystkie otwarte konta uzytkownika wraz z ich stanem.
     */
    void wyswietlKonta() const;

    /**
     * @brief Zamyka wskazane konto uzytkownika.
     * @param numerKonta Numer rachunku do zamkniecia.
     */
    void zamknijKonto(const string& numerKonta);

    /**
     * @brief Pobiera wskaznik do rachunku o zadanym indeksie.
     * @param indeks Indeks konta na liscie (domyslnie 0).
     * @return Rachunek* Wskaznik na obiekt rachunku.
     * @throws std::out_of_range jesli indeks jest nieprawidlowy lub brak kont.
     */
    Rachunek* pobierzRachunek(int indeks = 0);

    string getPesel() const;
    string getHaslo() const;

    /**
     * @brief Przeciazenie operatora wypisywania strumieniowego.
     */
    friend ostream& operator<<(ostream& os, const Uzytkownik& u);
};