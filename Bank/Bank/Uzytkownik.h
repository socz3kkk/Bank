#pragma once
#include <string>
#include <vector>

using namespace std;

class Rachunek;


class Uzytkownik {
private:
    string imie;
    string nazwisko;
    string pesel;
    string haslo;
    vector<Rachunek*> mojeKonta;

public:
    Uzytkownik(string imie, string nazwisko, string pesel, string haslo);

    ~Uzytkownik();

    void otworzKonto(string typKonta);
    void wyswietlKonta();
    void zamknijKonto(string numerKonta);

    string getPesel() const;
    string getHaslo() const;
};