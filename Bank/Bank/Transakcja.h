#pragma once
#include <string>

using namespace std;

class Transakcja {
private:
    static int licznikId;
    int id;
    string data;
    double kwota;
    string typOperacji;

    string pobierzAktualnaDate() const;

public:
    Transakcja(double kwota, string typOperacji);
    void wyswietlTransakcje() const;
};