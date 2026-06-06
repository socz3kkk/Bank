#pragma once

#include <string>

using namespace std;

class Transakcja
{
private:
    string idTransakcji;
    string typOperacji;
    double kwota;
    string data;

public:
    Transakcja();

    Transakcja(
        const string& id,
        const string& typ,
        double kwota,
        const string& data);

    string getIdTransakcji() const;
    string getTypOperacji() const;
    double getKwota() const;
    string getData() const;
};