#include <iostream>
#include <string>
#include "SystemBankowy.h"
#include "Uzytkownik.h"

using namespace std;

int main() {
    SystemBankowy bank("Narodowy Bank");
    Uzytkownik* zalogowanyKlient = nullptr;
    int wybor;

    while (true) {
        cout << "\n=== SYSTEM BANKOWY ===" << endl;

        if (zalogowanyKlient == nullptr) {
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
        }
        else {
            cout << "3. Otworz nowe konto bankowe" << endl;
            cout << "4. Wyswietl moje konta" << endl;
            cout << "5. Wyloguj" << endl;
        }
        cout << "0. Wyjdz z programu" << endl;
        cout << "Wybor: ";
        cin >> wybor;

        if (wybor == 0) {
            break;
        }

        if (zalogowanyKlient == nullptr) {
            if (wybor == 1) {
                string im, naz, p, h;
                cout << "Imie: "; cin >> im;
                cout << "Nazwisko: "; cin >> naz;
                cout << "PESEL: "; cin >> p;
                cout << "Haslo: "; cin >> h;

                bank.zarejestrujKlienta(im, naz, p, h);
                cout << "Zlecono rejestracje!" << endl;
            }
            else if (wybor == 2) {
                string p, h;
                cout << "PESEL: "; cin >> p;
                cout << "Haslo: "; cin >> h;

                zalogowanyKlient = bank.zaloguj(p, h);

                if (zalogowanyKlient != nullptr) {
                    cout << "Zalogowano pomyslnie!" << endl;
                }
                else {
                    cout << "Bledny PESEL lub haslo. Sprobuj ponownie" << endl;

                }
            }
        }
        else {
            if (wybor == 3) {
                string typKonta;
                cout << "Podaj typ konta (np. Oszczednosciowe, Walutowe): ";
                cin >> typKonta;

                zalogowanyKlient->otworzKonto(typKonta);
            }
            else if (wybor == 4) {
                zalogowanyKlient->wyswietlKonta();
            }
            else if (wybor == 5) {
                zalogowanyKlient = nullptr;
                cout << "Wylogowano pomyslnie." << endl;
            }
        }
    }
    return 0;
}