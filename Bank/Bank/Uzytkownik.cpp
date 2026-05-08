#include "Uzytkownik.h"
#include <iostream>

using namespace std;

Uzytkownik::Uzytkownik(const string& imie, const string& nazwisko, const string& pesel, const string& haslo)
    : imie(imie), nazwisko(nazwisko), pesel(pesel), haslo(haslo) {
}

Uzytkownik::~Uzytkownik() {
    cout << "[Uzytkownik] Usunieto profil: " << imie << " " << nazwisko << endl;
}

void Uzytkownik::otworzKonto(const string& typKonta) {
    cout << "Otwieram nowe konto typu: " << typKonta << "\n";
}

void Uzytkownik::wyswietlKonta() const {
    cout << "Zestawienie kont uzytkownika: " << imie << " " << nazwisko << "\n";
    cout << "(Logika wyswietlania salda czeka na metode w klasie Rachunek)\n";
}

void Uzytkownik::zamknijKonto(const string& numerKonta) {
    cout << "Zamykanie konta " << numerKonta << "...\n";
}

string Uzytkownik::getPesel() const { return pesel; }
string Uzytkownik::getHaslo() const { return haslo; }