#include "Uzytkownik.h"
#include <iostream>

Uzytkownik::Uzytkownik(string im, string naz, string p, string tel, string pan, string adres, string h)
    : imie(im), nazwisko(naz), pesel(p), nrTelefonu(tel), panienskieMatki(pan), adresZameldowania(adres), haslo(h) {
}

Uzytkownik::~Uzytkownik() {
    for (Rachunek* konto : mojeKonta) {
        delete konto;
    }
    mojeKonta.clear();
}

string Uzytkownik::getPesel() const {
    return pesel;
}

bool Uzytkownik::sprawdzHaslo(string podaneHaslo) const {
    return haslo == podaneHaslo;
}

void Uzytkownik::wybierzKonto(string numerKonta) {
    cout << "Szukam konta o numerze: " << numerKonta << "..." << endl;
}

void Uzytkownik::otworzNoweKonto(Rachunek* noweKonto) {
    mojeKonta.push_back(noweKonto);
    cout << "Nowy rachunek zostal przypisany do profilu klienta." << endl;
}