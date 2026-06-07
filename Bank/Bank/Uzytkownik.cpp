#include "Uzytkownik.h"
#include "Kredytowy.h" 
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

Uzytkownik::Uzytkownik(const string& imie, const string& nazwisko, const string& pesel, const string& haslo)
    : imie(imie), nazwisko(nazwisko), pesel(pesel), haslo(haslo) {
}

Uzytkownik::~Uzytkownik() {
    mojeKonta.clear();
}

void Uzytkownik::otworzKonto(const string& typKonta) {
    constexpr size_t LIMIT_KONT = 3;
    if (mojeKonta.size() >= LIMIT_KONT) {
        throw length_error("Odmowa! Osiagnieto maksymalny limit kont dla tego profilu.");
    }

    string przykladowyNumer = "PL123456789_" + to_string(mojeKonta.size() + 1);

    if (typKonta == "Kredytowe") {
        mojeKonta.push_back(make_unique<Kredytowy>(przykladowyNumer, 0.0, 5000.0));
    }
    else if (typKonta == "Standardowe") {
        mojeKonta.push_back(make_unique<Rachunek>(przykladowyNumer, 0.0));
    }
    else {
        throw invalid_argument("Nieznany typ konta!");
    }

    cout << "[SUKCES] Otworzono nowe konto typu: " << typKonta << " (" << przykladowyNumer << ")\n";
}

void Uzytkownik::wyswietlKonta() const {
    if (mojeKonta.empty()) {
        cout << "Nie posiadasz jeszcze zadnych otwartych kont.\n";
        return;
    }

    for (size_t i = 0; i < mojeKonta.size(); i++) {
        cout << i + 1 << ". Konto nr: " << mojeKonta[i]->pobierzNumer() << "\n";
    }
}

void Uzytkownik::zamknijKonto(const string& numerKonta) {
    cout << "Zamykanie konta " << numerKonta << "...\n";
}

Rachunek* Uzytkownik::pobierzRachunek(int indeks) {
    if (mojeKonta.empty()) {
        throw out_of_range("Brak otwartych kont bankowych!");
    }
    if (indeks < 0 || indeks >= mojeKonta.size()) {
        throw out_of_range("Nieprawidlowy indeks konta.");
    }
    return mojeKonta[indeks].get();
}

string Uzytkownik::getPesel() const { return pesel; }
string Uzytkownik::getHaslo() const { return haslo; }
string Uzytkownik::getImie() const { return imie; }
string Uzytkownik::getNazwisko() const { return nazwisko; }

const vector<unique_ptr<Rachunek>>& Uzytkownik::getKonta() const
{
    return mojeKonta;
}

ostream& operator<<(ostream& os, const Uzytkownik& u) {
    os << u.imie << " " << u.nazwisko << " (PESEL: " << u.pesel << ") | Konta: " << u.mojeKonta.size();
    return os;
}