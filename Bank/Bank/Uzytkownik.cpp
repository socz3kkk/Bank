#include "Uzytkownik.h"
#include "Rachunek.h"
#include "KontoOszczednosciowe.h"
#include "KontoWalutowe.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <random>

using namespace std;

string generujLosowyNumerKonta() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> zakres(100000, 999999);

    return "PL" + to_string(zakres(gen));
}

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

    string unikalnyNumer = generujLosowyNumerKonta();

    if (typKonta == "Oszczednosciowe") {
        mojeKonta.push_back(make_unique<KontoOszczednosciowe>(unikalnyNumer, 0.0, 5.0));
    }
    else if (typKonta == "Walutowe") {
        mojeKonta.push_back(make_unique<KontoWalutowe>(unikalnyNumer, 0.0, "EUR", 4.30));
    }
    else {
        throw invalid_argument("Nieznany typ konta!");
    }

    cout << "[SUKCES] Otworzono nowe konto typu: " << typKonta << " (" << unikalnyNumer << ")\n";
}

void Uzytkownik::wyswietlKonta() const {
    if (mojeKonta.empty()) {
        cout << "Nie posiadasz jeszcze zadnych otwartych kont.\n";
        return;
    }

    for (size_t i = 0; i < mojeKonta.size(); i++) {
        cout << i + 1 << ". ";
        mojeKonta[i]->wyswietlSzczegoly();
        cout << "\n";
    }
}

void Uzytkownik::zamknijKonto(int indeks) {
    if (mojeKonta.empty()) {
        throw out_of_range("Brak otwartych kont do zamkniecia!");
    }
    if (indeks < 0 || indeks >= mojeKonta.size()) {
        throw out_of_range("Nieprawidlowy indeks konta.");
    }

    mojeKonta.erase(mojeKonta.begin() + indeks);
    cout << "[SUKCES] Konto zostalo pomyslnie zamkniete i usuniete z systemu.\n";
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

const vector<unique_ptr<Rachunek>>& Uzytkownik::getKonta() const { return mojeKonta; }

void Uzytkownik::dodajWczytaneKonto(unique_ptr<Rachunek> konto) {
    if (konto != nullptr) {
        mojeKonta.push_back(move(konto));
    }
}

ostream& operator<<(ostream& os, const Uzytkownik& u) {
    os << u.imie << " " << u.nazwisko << " (PESEL: " << u.pesel << ") | Konta: " << u.mojeKonta.size();
    return os;
}