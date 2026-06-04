#pragma once
#include <string>
#include <vector>
#include "Uzytkownik.h"

using namespace std;

class SystemBankowy {
private:
    string nazwaBanku;
    vector<Uzytkownik*> bazaKlientow;

public:
    SystemBankowy(const string& nazwa);
    virtual ~SystemBankowy();

    Uzytkownik* zaloguj(const string& pesel, const string& haslo) const;
    Uzytkownik* zarejestrujKlienta(const string& imie, const string& nazwisko, const string& pesel, const string& haslo);
};