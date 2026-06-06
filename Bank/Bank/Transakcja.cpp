#include "Transakcja.h"

Transakcja::Transakcja(
    const string& typOperacji,
    double kwota,
    const string& data,
    const string& idTransakcji)
{
    this->typOperacji = typOperacji;
    this->kwota = kwota;
    this->data = data;
    this->idTransakcji = idTransakcji;
}

string Transakcja::pobierzDaneTransakcji() const
{
    return "ID: " + idTransakcji +
        " | Typ: " + typOperacji +
        " | Kwota: " + to_string(kwota) +
        " | Data: " + data;
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