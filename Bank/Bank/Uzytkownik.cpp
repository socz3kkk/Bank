#include "Uzytkownik.h"
#include "Rachunek.h"
#include "RachunekOszczednosciowy.h"
#include "RachunekWalutowy.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Uzytkownik::Uzytkownik(string imie, string nazwisko, string pesel, string haslo) {
    this->imie = imie;
    this->nazwisko = nazwisko;
    this->pesel = pesel;
    this->haslo = haslo;
}

Uzytkownik::~Uzytkownik() {
    for (auto konto : mojeKonta) {
        delete konto;
    }
    mojeKonta.clear();
}

void Uzytkownik::otworzKonto(string typKonta) {
    string nowyNumer = "PL" + to_string(rand() % 900000 + 100000);
    Rachunek* noweKonto = nullptr;

    if (typKonta == "oszczednosciowe" || typKonta == "Oszczednosciowe") {
        noweKonto = new RachunekOszczednosciowy(nowyNumer);
    }
    else if (typKonta == "walutowe" || typKonta == "Walutowe") {
        noweKonto = new RachunekWalutowy(nowyNumer, "EUR");
    }
    else {
        noweKonto = new Rachunek(nowyNumer, TypRachunku::NORMALNE, "PLN");
    }

    mojeKonta.push_back(noweKonto);
    cout << "[System] Otwarto nowe konto: " << nowyNumer << endl;
}

void Uzytkownik::wyswietlKonta() {
    if (mojeKonta.empty()) {
        cout << "[System] Brak przypisanych kont." << endl;
        return;
    }
    for (auto konto : mojeKonta) {
        konto->wyswietlSzczegoly();
    }
}

void Uzytkownik::zamknijKonto(string numerKonta) {
    for (auto it = mojeKonta.begin(); it != mojeKonta.end(); ++it) {
        if ((*it)->getNumerKonta() == numerKonta) {
            delete* it;
            mojeKonta.erase(it);
            cout << "[System] Zamknieto konto: " << numerKonta << endl;
            return;
        }
    }
}

string Uzytkownik::getPesel() const {
    return pesel;
}

string Uzytkownik::getHaslo() const {
    return haslo;
}