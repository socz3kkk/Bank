#pragma once

#include <string>

using namespace std;

class Transakcja
{
private:
    string typOperacji;
    double kwota;
    string data;
    string idTransakcji;

public:
    Transakcja(
        const string& typOperacji,
        double kwota,
        const string& data,
        const string& idTransakcji
    );

    string pobierzDaneTransakcji() const;

    string getTypOperacji() const;
    double getKwota() const;
    string getData() const;
    string getIdTransakcji() const;
};