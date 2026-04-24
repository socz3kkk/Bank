#pragma once
#include <string>
#include <vector>
#include "Uzytkownik.h"

class Rachunek;
class BazaDanych;

class SystemBankowy {
private:
    string nazwaBanku;
    vector<Uzytkownik*> bazaKlientow;
    BazaDanych* menedzerPlikow;

public:
    SystemBankowy(string nazwa);

    ~SystemBankowy();

    Rachunek* szukajRachunku(string numerKonta);

    Uzytkownik* zaloguj(string pesel, string haslo);

    Uzytkownik* zarejestrujKlienta(string imie, string nazwisko, string pesel, string haslo);
};