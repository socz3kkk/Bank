#include <fstream>
#include <iomanip>
#include "json.hpp"
using json = nlohmann::json;
#include "SystemBankowy.h"
#include "Uzytkownik.h" 
#include <iostream>

using namespace std;


SystemBankowy::SystemBankowy(string nazwa) {
    nazwaBanku = nazwa;
    cout << "[SystemBankowy] Uruchomiono system dla banku: " << nazwaBanku << endl;
}

SystemBankowy::~SystemBankowy() {
    cout << "[SystemBankowy] Zamykanie systemu bankowego i czyszczenie pamieci..." << endl;
}

Rachunek* SystemBankowy::szukajRachunku(string numerKonta) {
    cout << "[SystemBankowy] Przeszukuje baze w poszukiwaniu konta nr: " << numerKonta << endl;
    return nullptr;
}

Uzytkownik* SystemBankowy::zaloguj(string pesel, string haslo) {
    cout << "[SystemBankowy] Rozpoczeto probe logowania dla PESEL: " << pesel << endl;
    return nullptr;
}

Uzytkownik* SystemBankowy::zarejestrujKlienta(string imie, string nazwisko, string pesel, string haslo) {
    cout << "[SystemBankowy] Przyjeto wniosek o rejestracje nowego klienta: " << imie << " " << nazwisko << endl;
    return nullptr;
    void SystemBankowy::zapiszDoPliku()
{
    json j;

    for (const auto& rachunek : rachunki)
    {
        j.push_back({
            {"id", rachunek.getId()},
            {"owner", rachunek.getWlasciciel()},
            {"balance", rachunek.getSaldo()}
        });
    }

    std::ofstream file("accounts.json");

    file << std::setw(4) << j;

    file.close();
}
}
