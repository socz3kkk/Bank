#include "Transakcja.h"

Transakcja::Transakcja()
    : idTransakcji(""), typOperacji(""), kwota(0.0), data("") {
}

Transakcja::Transakcja(const string& id, const string& typ, double kwota, const string& data)
    : idTransakcji(id), typOperacji(typ), kwota(kwota), data(data) {
}

string Transakcja::getIdTransakcji() const { return idTransakcji; }
string Transakcja::getTypOperacji() const { return typOperacji; }
double Transakcja::getKwota() const { return kwota; }
string Transakcja::getData() const { return data; }

ostream& operator<<(ostream& os, const Transakcja& tx) {
    os << "[" << tx.data << "] " << tx.typOperacji
        << " na kwote: " << tx.kwota << " (ID: " << tx.idTransakcji << ")";
    return os;
}