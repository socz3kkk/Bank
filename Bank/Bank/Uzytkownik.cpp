#include "Uzytkownik.h"
#include <iostream>

using namespace std;

Uzytkownik::Uzytkownik(string imie, string nazwisko, string pesel, string haslo) {
    this->imie = imie;
    this->nazwisko = nazwisko;
    this->pesel = pesel;
    this->haslo = haslo;
    cout << "[Uzytkownik] Utworzono profil dla: " << this->imie << " " << this->nazwisko << endl;
}

Uzytkownik::~Uzytkownik() {
    cout << "[Uzytkownik] Usunieto z pamieci profil: " << imie << " " << nazwisko << endl;
}

void Uzytkownik::otworzKonto(string typKonta) {
    cout << "[Uzytkownik] Otwieram nowe konto typu: " << typKonta << endl;
}

void Uzytkownik::wyswietlKonta() {
    cout << "[Uzytkownik] Pobieram i wyswietlam liste wszystkich kont uzytkownika..." << endl;
}

void Uzytkownik::zamknijKonto(string numerKonta) {
    cout << "[Uzytkownik] Trwa zamykanie konta o numerze: " << numerKonta << endl;
}

string Uzytkownik::getPesel() const {
    return pesel;
}

string Uzytkownik::getHaslo() const {
    return haslo;
}