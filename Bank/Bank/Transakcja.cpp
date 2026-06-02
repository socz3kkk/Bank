#include "Transakcja.h"

#include <string>

using namespace std;

Transakcja::Transakcja(
    string typOperacji,
    double kwota,
    string data,
    string idTransakcji)
{
    this->typOperacji = typOperacji;
    this->kwota = kwota;
    this->data = data;
    this->idTransakcji = idTransakcji;
}

string Transakcja::pobierzDaneTransakcji()
{
    return "ID: " + idTransakcji +
        ", Typ: " + typOperacji +
        ", Kwota: " + to_string(kwota) +
        ", Data: " + data;
}

string Transakcja::getTypOperacji() const
{
    return typOperacji;
}

double Transakcja::getKwota() const
{
    return kwota;
}

string Transakcja::getData() const
{
    return data;
}

string Transakcja::getIdTransakcji() const
{
    return idTransakcji;
}