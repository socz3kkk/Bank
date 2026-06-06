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
        string typOperacji,
        double kwota,
        string data,
        string idTransakcji
    );

    string pobierzDaneTransakcji();

    string getTypOperacji() const;
    double getKwota() const;
    string getData() const;
    string getIdTransakcji() const;
};