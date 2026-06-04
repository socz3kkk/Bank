#include <iostream>
#include <string>
#include "SystemBankowy.h"
#include "Uzytkownik.h"

using namespace std;

constexpr int WYJSCIE = 0;
constexpr int REJESTRACJA = 1;
constexpr int LOGOWANIE = 2;
constexpr int OTWORZ_KONTO = 3;
constexpr int WYSWIETL_KONTA = 4;
constexpr int WYLOGUJ = 5;

int main() {
    SystemBankowy bank(string("Narodowy Bank"));
    Uzytkownik* zalogowanyKlient = nullptr;
    int wybor;

    while (true) {
        cout << "\n=== SYSTEM BANKOWY ===" << endl;

        if (zalogowanyKlient == nullptr) {
            cout << REJESTRACJA << ". Rejestracja\n";
            cout << LOGOWANIE << ". Logowanie\n";
        }
        else {
            cout << OTWORZ_KONTO << ". Otworz nowe konto bankowe\n";
            cout << WYSWIETL_KONTA << ". Wyswietl moje konta\n";
            cout << WYLOGUJ << ". Wyloguj\n";
        }
        cout << WYJSCIE << ". Wyjdz z programu\n";
        cout << "Wybor: ";

        if (!(cin >> wybor)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Blad: Nieprawidlowy format danych. Podaj cyfre.\n";
            continue;
        }

        if (wybor == WYJSCIE) break;

        if (zalogowanyKlient == nullptr) {
            if (wybor == REJESTRACJA) {
                string im, naz, p, h;
                cout << "Imie: "; cin >> im;
                cout << "Nazwisko: "; cin >> naz;
                cout << "PESEL: "; cin >> p;
                cout << "Haslo: "; cin >> h;

                if (bank.zarejestrujKlienta(im, naz, p, h) != nullptr) {
                    cout << "Zlecono rejestracje!\n";
                }
            }
            else if (wybor == LOGOWANIE) {
                string p, h;
                cout << "PESEL: "; cin >> p;
                cout << "Haslo: "; cin >> h;

                zalogowanyKlient = bank.zaloguj(p, h);
                if (zalogowanyKlient != nullptr) {
                    cout << "Zalogowano pomyslnie!\n";
                }
                else {
                    cout << "Bledny PESEL lub haslo. Sprobuj ponownie.\n";
                }
            }
        }
        else {
            if (wybor == OTWORZ_KONTO) {
                string typKonta;
                cout << "Podaj typ konta (np. Oszczednosciowe, Walutowe): ";
                cin >> typKonta;
                zalogowanyKlient->otworzKonto(typKonta);
            }
            else if (wybor == WYSWIETL_KONTA) {
                zalogowanyKlient->wyswietlKonta();
            }
            else if (wybor == WYLOGUJ) {
                zalogowanyKlient = nullptr;
                cout << "Wylogowano pomyslnie.\n";
            }
        }
    }
    return 0;
}