#include "Uzytkownik.h"
#include <iostream>

using namespace std;

Uzytkownik::Uzytkownik(const string& imie, const string& nazwisko, const string& pesel, const string& haslo)
    : imie(imie), nazwisko(nazwisko), pesel(pesel), haslo(haslo) {
}

Uzytkownik::~Uzytkownik() {
    cout << "[Uzytkownik] Usunieto profil: " << imie << " " << nazwisko << endl;

    for (Rachunek* r : mojeKonta) {
        delete r;
    }
    mojeKonta.clear();
}

void Uzytkownik::otworzKonto(const string& typKonta) {
    string przykladowyNumer = "PL123456789";

    Rachunek* noweKonto = new Rachunek(przykladowyNumer, 0.0);
    mojeKonta.push_back(noweKonto);

    cout << "Otworzono nowe konto typu: " << typKonta << "\n";
    cout << "Przypisany numer konta: " << przykladowyNumer << "\n";
}

void Uzytkownik::wyswietlKonta() const {
    cout << "Zestawienie kont uzytkownika: " << imie << " " << nazwisko << "\n";

    if (mojeKonta.empty()) {
        cout << "Nie posiadasz jeszcze zadnych otwartych kont.\n";
        return;
    }

    for (size_t i = 0; i < mojeKonta.size(); i++) {
        cout << i + 1 << ". Konto nr: " << mojeKonta[i]->pobierzNumer()
            << " | Saldo: " << mojeKonta[i]->pobierzSaldo() << " PLN\n";
    }
}

void Uzytkownik::zamknijKonto(const string& numerKonta) {
    cout << "Zamykanie konta " << numerKonta << "...\n";
}

Rachunek* Uzytkownik::pobierzRachunek(int indeks) {
    if (mojeKonta.empty()) {
        return nullptr;
    }
    if (indeks >= 0 && indeks < mojeKonta.size()) {
        return mojeKonta[indeks];
    }
    return nullptr;
}

string Uzytkownik::getPesel() const { return pesel; }
string Uzytkownik::getHaslo() const { return haslo; }