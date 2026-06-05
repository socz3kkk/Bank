#include "SystemBankowy.h"
#include <iostream>
#include <stdexcept>

constexpr size_t WYMAGANA_DLUGOSC_PESEL = 11;

SystemBankowy::SystemBankowy(const string& nazwa) : nazwaBanku(nazwa) {
    cout << "[SystemBankowy] Uruchomiono system dla banku: " << nazwaBanku << endl;
}

SystemBankowy::~SystemBankowy() {
    bazaKlientow.clear();
}

Uzytkownik* SystemBankowy::zaloguj(const string& pesel, const string& haslo) const {
    if (pesel.empty() || haslo.empty()) {
        throw invalid_argument("Dane logowania nie moga byc puste!");
    }

    for (const auto& u : bazaKlientow) {
        if (u->getPesel() == pesel && u->getHaslo() == haslo) {
            return u.get();
        }
    }
    throw invalid_argument("Bledny PESEL lub haslo.");
}

Uzytkownik* SystemBankowy::zarejestrujKlienta(const string& imie, const string& nazwisko, const string& pesel, const string& haslo) {
    if (pesel.length() != WYMAGANA_DLUGOSC_PESEL) {
        throw invalid_argument("PESEL musi miec dokladnie " + to_string(WYMAGANA_DLUGOSC_PESEL) + " znakow.");
    }

    for (const auto& u : bazaKlientow) {
        if (u->getPesel() == pesel) {
            throw invalid_argument("Uzytkownik o podanym numerze PESEL juz istnieje w bazie.");
        }
    }

    bazaKlientow.push_back(make_unique<Uzytkownik>(imie, nazwisko, pesel, haslo));
    return bazaKlientow.back().get();
}