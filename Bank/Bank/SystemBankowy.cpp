#include "SystemBankowy.h"
#include <iostream>

constexpr size_t WYMAGANA_DLUGOSC_PESEL = 11;

SystemBankowy::SystemBankowy(const string& nazwa) : nazwaBanku(nazwa) {
    cout << "[SystemBankowy] Uruchomiono system dla banku: " << nazwaBanku << endl;
}

SystemBankowy::~SystemBankowy() {
    for (Uzytkownik* u : bazaKlientow) {
        delete u;
    }
    bazaKlientow.clear();
}

Uzytkownik* SystemBankowy::zaloguj(const string& pesel, const string& haslo) const {
    if (pesel.empty() || haslo.empty()) return nullptr;

    for (Uzytkownik* u : bazaKlientow) {
        if (u->getPesel() == pesel && u->getHaslo() == haslo) {
            return u;
        }
    }
    return nullptr;
}

Uzytkownik* SystemBankowy::zarejestrujKlienta(const string& imie, const string& nazwisko, const string& pesel, const string& haslo) {
    if (pesel.length() != WYMAGANA_DLUGOSC_PESEL) {
        cout << "Blad: PESEL musi miec dokladnie " << WYMAGANA_DLUGOSC_PESEL << " znakow.\n";
        return nullptr;
    }

    for (const Uzytkownik* u : bazaKlientow) {
        if (u->getPesel() == pesel) {
            cout << "Blad: Uzytkownik o podanym PESEL juz istnieje!\n";
            return nullptr;
        }
    }

    Uzytkownik* nowy = new Uzytkownik(imie, nazwisko, pesel, haslo);
    bazaKlientow.push_back(nowy);
    return nowy;
}