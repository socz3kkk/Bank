#include <iostream>
#include <string>
#include "SystemBankowy.h"
#include "Uzytkownik.h"
#include "Rachunek.h"

using namespace std;

int main() {
    SystemBankowy bank("Narodowy Bank");
    Uzytkownik* zalogowanyKlient = nullptr;
    Rachunek* aktywneKonto = nullptr;

    int wybor;

    while (true) {
        cout << "\n=== " << (aktywneKonto ? "OPERACJE NA KONCIE" : "SYSTEM BANKOWY") << " ===" << endl;

        if (zalogowanyKlient == nullptr) {
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "0. Wyjdz z programu" << endl;
        }
        else if (aktywneKonto != nullptr) {
            cout << "Obecnie zarzadzasz kontem: " << aktywneKonto->getNumerKonta() << endl;
            cout << "1. Wplac srodki" << endl;
            cout << "2. Wyplac srodki" << endl;
            cout << "3. Wykonaj przelew" << endl;
            cout << "4. Wyswietl szczegoly konta" << endl;
            cout << "5. Powrot do menu glownego uzytkownika" << endl;
            cout << "0. Wyjdz z programu" << endl;
        }
        else {
            cout << "3. Otworz nowe konto bankowe" << endl;
            cout << "4. Wyswietl moje konta" << endl;
            cout << "5. Wybierz konto do operacji (TEST RACHUNKU)" << endl;
            cout << "6. Wyloguj" << endl;
            cout << "0. Wyjdz z programu" << endl;
        }

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
            }
            else if (wybor == 2) {
                string p, h;
                cout << "PESEL: "; cin >> p;
                cout << "Haslo: "; cin >> h;

                cout << "[SYMULACJA] Wymuszam zalogowanie do testow..." << endl;
                zalogowanyKlient = new Uzytkownik("Krystian", "Testowy", p, h);
            }
        }
        else if (aktywneKonto != nullptr) {
            if (wybor == 1) {
                double kwota;
                cout << "Podaj kwote do wplaty: "; cin >> kwota;
                aktywneKonto->wplac(kwota);
            }
            else if (wybor == 2) {
                double kwota;
                cout << "Podaj kwote do wyplaty: "; cin >> kwota;
                aktywneKonto->wyplac(kwota);
            }
            else if (wybor == 3) {
                string cel; double kwota;
                cout << "Podaj numer konta docelowego: "; cin >> cel;
                cout << "Podaj kwote: "; cin >> kwota;

                Rachunek* kontoCelowe = new Rachunek(cel, "PLN");
                aktywneKonto->wykonajPrzelew(kontoCelowe, kwota);
                delete kontoCelowe;
            }
            else if (wybor == 4) {
                aktywneKonto->wyswietlSzczegoly();
            }
            else if (wybor == 5) {
                delete aktywneKonto;
                aktywneKonto = nullptr;
                cout << "Powrot do glownego panelu." << endl;
            }
        }
        else {
            if (wybor == 3) {
                string typKonta;
                cout << "Podaj typ konta: "; cin >> typKonta;
                zalogowanyKlient->otworzKonto(typKonta);
            }
            else if (wybor == 4) {
                zalogowanyKlient->wyswietlKonta();
            }
            else if (wybor == 5) {
                cout << "[SYMULACJA] Tworze obiekt Rachunek, abys mogl przetestowac metody..." << endl;
                aktywneKonto = new Rachunek("999988887777", "PLN");
            }
            else if (wybor == 6) {
                delete zalogowanyKlient;
                zalogowanyKlient = nullptr;
                cout << "Wylogowano pomyslnie." << endl;
            }
        }
    }

    if (aktywneKonto != nullptr) delete aktywneKonto;
    if (zalogowanyKlient != nullptr) delete zalogowanyKlient;

    cout << "Zamykanie aplikacji..." << endl;
    return 0;
}