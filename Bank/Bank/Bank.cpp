#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "SystemBankowy.h"
#include "Uzytkownik.h"
#include "Rachunek.h"

using namespace std;

constexpr int WYJSCIE = 0;
constexpr int REJESTRACJA = 1;
constexpr int LOGOWANIE = 2;

constexpr int OTWORZ_KONTO = 3;
constexpr int WYSWIETL_KONTA = 4;
constexpr int WPLAC_SRODKI = 5;
constexpr int WYPLAC_SRODKI = 6;
constexpr int SPRAWDZ_SALDO = 7;
constexpr int WYLOGUJ = 8;

constexpr int DLUGOSC_PESEL = 11;

/**
 * @brief Funkcja czyszczaca bufor strumienia wejsciowego.
 * Zapobiega zawieszeniu sie programu w przypadku wczytania niepoprawnego typu danych.
 */
void wyczyscBufor() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    SystemBankowy bank("Narodowy Bank");
    Uzytkownik* zalogowanyKlient = nullptr;
    int wybor;

    while (true) {
        cout << "\n====================================\n";
        cout << "           SYSTEM BANKOWY\n";
        cout << "====================================\n";

        if (zalogowanyKlient == nullptr) {
            cout << REJESTRACJA << ". Rejestracja\n";
            cout << LOGOWANIE << ". Logowanie\n";
        }
        else {
            cout << " Zalogowano jako: " << *zalogowanyKlient << "\n";
            cout << "------------------------------------\n";
            cout << OTWORZ_KONTO << ". Otworz nowe konto bankowe\n";
            cout << WYSWIETL_KONTA << ". Wyswietl moje konta\n";
            cout << WPLAC_SRODKI << ". Wplac gotowke na konto\n";
            cout << WYPLAC_SRODKI << ". Wyplac gotowke z konta\n";
            cout << SPRAWDZ_SALDO << ". Sprawdz saldo konta\n";
            cout << WYLOGUJ << ". Wyloguj\n";
        }
        cout << WYJSCIE << ". Wyjdz z programu\n";
        cout << "------------------------------------\n";
        cout << "Wybor: ";

        if (!(cin >> wybor)) {
            wyczyscBufor();
            cout << "\n[BLAD] Nieprawidlowy format. Wpisz cyfre opcji.\n";
            continue;
        }

        if (wybor == WYJSCIE) {
            cout << "\nZamykanie systemu. Do widzenia!\n";
            break;
        }

        try {
            if (zalogowanyKlient == nullptr) {
                switch (wybor) {
                case REJESTRACJA: {
                    string im, naz, p, h;
                    cout << "Podaj imie: "; cin >> im;
                    cout << "Podaj nazwisko: "; cin >> naz;
                    cout << "Podaj PESEL: "; cin >> p;
                    cout << "Podaj haslo: "; cin >> h;

                    if (bank.zarejestrujKlienta(im, naz, p, h) != nullptr) {
                        cout << "[SUKCES] Zlecono rejestracje profilu!\n";
                    }
                    break;
                }
                case LOGOWANIE: {
                    string p, h;
                    cout << "Podaj PESEL: "; cin >> p;
                    cout << "Podaj haslo: "; cin >> h;

                    zalogowanyKlient = bank.zaloguj(p, h);
                    cout << "[SUKCES] Zalogowano pomyslnie!\n";
                    break;
                }
                default:
                    cout << "[BLAD] Wybierz poprawna opcje z menu.\n";
                    break;
                }
            }
            else {
                switch (wybor) {
                case OTWORZ_KONTO: {
                    int opcjaKonta;
                    cout << "Wybierz typ konta z listy:\n";
                    cout << "1. Konto Standardowe\n";
                    cout << "2. Konto Kredytowe\n";
                    cout << "Wybor: ";

                    if (!(cin >> opcjaKonta)) {
                        wyczyscBufor();
                        throw invalid_argument("Oczekiwano cyfry 1 lub 2.");
                    }

                    if (opcjaKonta == 1) zalogowanyKlient->otworzKonto("Standardowe");
                    else if (opcjaKonta == 2) zalogowanyKlient->otworzKonto("Kredytowe");
                    else throw invalid_argument("Niepoprawny numer opcji.");

                    break;
                }
                case WYSWIETL_KONTA: {
                    zalogowanyKlient->wyswietlKonta();
                    break;
                }
                case WPLAC_SRODKI:
                case WYPLAC_SRODKI:
                case SPRAWDZ_SALDO: {
                    zalogowanyKlient->wyswietlKonta();
                    cout << "Wybierz numer konta do operacji (indeks z listy): ";
                    int wybranyIndeks;

                    if (!(cin >> wybranyIndeks) || wybranyIndeks < 1) {
                        wyczyscBufor();
                        throw invalid_argument("Nieprawidlowy format indeksu.");
                    }

                    Rachunek* konto = zalogowanyKlient->pobierzRachunek(wybranyIndeks - 1);

                    if (wybor == SPRAWDZ_SALDO) {
                        cout << "[INFORMACJA] Aktualne saldo wynosi: " << konto->pobierzSaldo() << " PLN\n";
                        break;
                    }

                    double kwota;
                    cout << "Podaj kwote: ";
                    if (!(cin >> kwota)) {
                        wyczyscBufor();
                        throw invalid_argument("Oczekiwano wartosci liczbowej dla kwoty.");
                    }

                    if (wybor == WPLAC_SRODKI) {
                        konto->wplac(kwota);
                        cout << "[SUKCES] Pomyslnie wplacono " << kwota << " PLN.\n";
                    }
                    else if (wybor == WYPLAC_SRODKI) {
                        konto->wyplac(kwota);
                        cout << "[SUKCES] Pomyslnie wyplacono " << kwota << " PLN.\n";
                    }
                    break;
                }
                case WYLOGUJ: {
                    zalogowanyKlient = nullptr;
                    cout << "[SUKCES] Wylogowano pomyslnie.\n";
                    break;
                }
                default:
                    cout << "[BLAD] Wybierz poprawna opcje z menu.\n";
                    break;
                }
            }
        }
        catch (const invalid_argument& e) {
            cout << "\n[BLAD DANYCH] " << e.what() << "\n";
        }
        catch (const length_error& e) {
            cout << "\n[LIMIT] " << e.what() << "\n";
        }
        catch (const out_of_range& e) {
            cout << "\n[BLAD INDEKSU] " << e.what() << "\n";
        }
        catch (const exception& e) {
            cout << "\n[NIEOCZEKIWANY BLAD] " << e.what() << "\n";
        }
    }

    return 0;
}