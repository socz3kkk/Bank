#define _CRT_SECURE_NO_WARNINGS
#include "Transakcja.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

int Transakcja::licznikId = 1;

string Transakcja::pobierzAktualnaDate() const {
    time_t czas = time(nullptr);
    tm* aktualnyCzas = localtime(&czas);
    stringstream strumien;
    if (aktualnyCzas) {
        strumien << setfill('0') << setw(2) << aktualnyCzas->tm_mday << "-"
            << setfill('0') << setw(2) << (aktualnyCzas->tm_mon + 1) << "-"
            << (aktualnyCzas->tm_year + 1900);
    }
    else {
        strumien << "Brak";
    }
    return strumien.str();
}

Transakcja::Transakcja(double kwota, string typOperacji) {
    this->id = licznikId++;
    this->data = pobierzAktualnaDate();
    this->kwota = kwota;
    this->typOperacji = typOperacji;
}

void Transakcja::wyswietlTransakcje() const {
    cout << "ID: " << id << " | Data: " << data << " | Operacja: " << typOperacji << " | Kwota: " << kwota << endl;
}