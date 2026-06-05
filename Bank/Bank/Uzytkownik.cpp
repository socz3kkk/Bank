#include "Uzytkownik.h"
#include "Kredytowy.h"
#include <iostream>
#include <string>

using namespace std;

Uzytkownik::Uzytkownik(const string& imie, const string& nazwisko, const string& pesel, const string& haslo)
    : imie(imie), nazwisko(nazwisko), pesel(pesel), haslo(haslo) {
}

Uzytkownik::~Uzytkownik() {
    cout << "[Uzytkownik] Usunieto profil: " << imie << " " << nazwisko << endl;
    mojeKonta.clear();
}

void Uzytkownik::otworzKonto(const string& typKonta) {
    constexpr size_t LIMIT_KONT = 3;
    if (mojeKonta.size() >= LIMIT_KONT) {
        cout << "[BLAD] Odmowa! Osiagnieto maksymalny limit kont (" << LIMIT_KONT << ") dla tego profilu.\n";
        return;
    }
    
    string przykladowyNumer = "PL123456789_" + to_string(mojeKonta.size() + 1);

    if (typKonta == "Kredytowe") {
        mojeKonta.push_back(make_unique<Kredytowy>(przykladowyNumer, 0.0, 5000.0));
    }
    else {
        mojeKonta.push_back(make_unique<Rachunek>(przykladowyNumer, 0.0));
    }

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
        cout << i + 1 << ". Konto nr: " << mojeKonta[i]->pobierzNumer()<< "\n";
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
        return mojeKonta[indeks].get();
    }
    return nullptr;
}

string Uzytkownik::getPesel() const { return pesel; }
string Uzytkownik::getHaslo() const { return haslo; }