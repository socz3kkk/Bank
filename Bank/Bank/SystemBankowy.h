#pragma once
#include <vector>
#include <string>
#include "Uzytkownik.h"

using namespace std;

class SystemBankowy {
private:
    vector<Uzytkownik> bazaUzytkownikow;

public:
    void zarejestrujUzytkownika(string im, string naz, string p, string tel,
        string pan, string adres, string h);

    Uzytkownik* zaloguj(string pesel, string haslo);
};