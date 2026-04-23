#include <iostream>
#include <string>
#include "SystemBankowy.h"
#include "Uzytkownik.h"
#include "Rachunek.h"

using namespace std;

int main() {
    SystemBankowy bank;
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
            cout << "4. Wyloguj" << endl;
        }
        cout << "0. Wyjdz z programu" << endl;
        cout << "Wybor: ";
        cin >> wybor;

        if (wybor == 0) {
            break;
        }

        if (zalogowanyKlient == nullptr) {
            if (wybor == 1) {
                string im, naz, p, tel, pan, adr, h;
                cout << "Imie: "; cin >> im;
                cout << "Nazwisko: "; cin >> naz;
                cout << "PESEL: "; cin >> p;
                cout << "Telefon: "; cin >> tel;
                cout << "Nazwisko panienskie matki: "; cin >> pan;
                cout << "Miasto: "; cin >> adr;
                cout << "Haslo: "; cin >> h;

                bank.zarejestrujUzytkownika(im, naz, p, tel, pan, adr, h);
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
                    cout << "Bledny PESEL lub haslo." << endl;
                }
            }
        }
        else {
            if (wybor == 3) {
                string nrKonta;
                cout << "Podaj numer dla nowego konta: "; cin >> nrKonta;


            }
            else if (wybor == 4) {
                zalogowanyKlient = nullptr;
                cout << "Wylogowano pomyslnie." << endl;
            }
        }
    }

    return 0;
}