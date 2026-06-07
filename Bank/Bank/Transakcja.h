#pragma once

#include <string>
#include <iostream>

using namespace std;

/**
 * @class Transakcja
 * @brief Klasa przechowujaca informacje o operacji wykonanej na rachunku.
 */
class Transakcja
{
private:
    string idTransakcji;
    string typOperacji;
    double kwota;
    string data;

public:

    /**
     * @brief Tworzy pusta transakcje.
     */
    Transakcja();

    /**
     * @brief Tworzy transakcje z podanymi danymi.
     * @param id Identyfikator transakcji.
     * @param typ Typ operacji.
     * @param kwota Kwota operacji.
     * @param data Data wykonania transakcji.
     */
    Transakcja(
        const string& id,
        const string& typ,
        double kwota,
        const string& data);

    string getIdTransakcji() const;
    string getTypOperacji() const;
    double getKwota() const;
    string getData() const;

    friend ostream& operator<<(
        ostream& os,
        const Transakcja& transakcja);
};