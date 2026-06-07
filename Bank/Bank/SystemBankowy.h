#pragma once
#include <string>
#include <vector>
#include <memory> 
#include "Uzytkownik.h"
#include "BazaDanych.h"

using namespace std;

/**
 * @class SystemBankowy
 * @brief Centralny system przechowujacy baze klientow banku.
 */
class SystemBankowy {
private:
    string nazwaBanku;
    vector<unique_ptr<Uzytkownik>> bazaKlientow;
    BazaDanych menedzerPlikow;

public:
    SystemBankowy(const string& nazwa);
    virtual ~SystemBankowy();

    /**
     * @brief Loguje uzytkownika na podstawie podanych danych.
     * @param pesel Numer PESEL uzytkownika.
     * @param haslo Haslo uzytkownika.
     * @return Uzytkownik* Wskaznik do zalogowanego profilu.
     * @throws std::invalid_argument w przypadku zlych danych logowania.
     */
    Uzytkownik* zaloguj(const string& pesel, const string& haslo) const;

    /**
     * @brief Rejestruje nowego uzytkownika w systemie bankowym.
     * @param imie Imie klienta.
     * @param nazwisko Nazwisko klienta.
     * @param pesel Numer PESEL.
     * @param haslo Haslo dostepu.
     * @return Uzytkownik* Wskaznik do nowo zarejestrowanego profilu.
     * @throws std::invalid_argument w przypadku gdy PESEL istnieje lub ma zla dlugosc.
     */
    Uzytkownik* zarejestrujKlienta(const string& imie, const string& nazwisko, const string& pesel, const string& haslo);

    void zapiszStanSystemu();
};