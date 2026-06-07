#include "SystemBankowy.h"
#include <iostream>
#include <stdexcept>

constexpr size_t WYMAGANA_DLUGOSC_PESEL = 11;

SystemBankowy::SystemBankowy(const string& nazwa)
    : nazwaBanku(nazwa), menedzerPlikow("baza_danych.json") { // Inicjalizacja pliku docelowego

    cout << "[SystemBankowy] Uruchomiono system dla banku: " << nazwaBanku << endl;

    // Wczytanie danych z bazy przy uruchomieniu programu
    menedzerPlikow.wczytajDane(bazaKlientow);
    if (!bazaKlientow.empty()) {
        cout << "[SystemBankowy] Wczytano " << bazaKlientow.size() << " profili klientow z bazy JSON.\n";
    }
}

SystemBankowy::~SystemBankowy() {
    zapiszStanSystemu(); // Zapis przed zamknieciem programu
    bazaKlientow.clear();
}

void SystemBankowy::zapiszStanSystemu() {
    menedzerPlikow.zapiszDane(bazaKlientow);
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

    zapiszStanSystemu(); // Od razu zabezpieczamy dane po rejestracji nowego klienta
    return bazaKlientow.back().get();
}