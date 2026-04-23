#include "SystemBankowy.h"
#include <iostream>

void SystemBankowy::zarejestrujUzytkownika(string im, string naz, string p, string tel,
    string pan, string adres, string h) {
    bazaUzytkownikow.emplace_back(im, naz, p, tel, pan, adres, h);
    cout << "Uzytkownik " << im << " " << naz << " zostal poprawnie zarejestrowany w systemie." << endl;
}

Uzytkownik* SystemBankowy::zaloguj(string pesel, string haslo) {
    for (auto& uzytkownik : bazaUzytkownikow) {
        if (uzytkownik.getPesel() == pesel && uzytkownik.sprawdzHaslo(haslo)) {
            cout << "Logowanie zakonczone sukcesem!" << endl;
            return &uzytkownik;
        }
    }

    cout << "Blad logowania: Niepoprawny PESEL lub haslo." << endl;
    return nullptr;
}