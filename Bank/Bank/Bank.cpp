#include <iostream>
#include <string>
#include <algorithm>
#include "SystemBankowy.h"
#include "Uzytkownik.h"
#include "Rachunek.h"
#include "Walidator.h"

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

                bool peselOk = false;
                while (!peselOk) {
                    cout << "PESEL (11 cyfr): "; cin >> p;
                    if (Walidator::czyPoprawnyPesel(p)) {
                        peselOk = true;
                    }
                    else {
                        cout << "[Blad] PESEL musi skladac sie z 11 cyfr!" << endl;
                    }
                }

                bool hasloOk = false;
                while (!hasloOk) {
                    cout << "Haslo (min. 12 znakow, duza i mala litera, cyfra, znak spec.): "; cin >> h;
                    if (Walidator::czySilneHaslo(h)) {
                        hasloOk = true;
                    }
                    else {
                        cout << "[Blad] Haslo jest za slabe, sprobuj ponownie!" << endl;
                    }
                }

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

                // Do celów symulacyjnych przyjmujemy, że konto docelowe jest normalne w PLN
                Rachunek* kontoCelowe = new Rachunek(cel, TypRachunku::NORMALNE, "PLN");
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
                string wpisanyTyp;
                cout << "Dostepne typy: normalne, oszczednosciowe, walutowe" << endl;
                cout << "Wpisz typ konta z klawiatury: ";
                cin >> wpisanyTyp;

                // Zamiana wpisanego słowa na małe litery
                for (auto& c : wpisanyTyp) c = tolower(c);

                TypRachunku wybranyTyp;
                string waluta = "PLN";

                if (wpisanyTyp == "normalne") {
                    wybranyTyp = TypRachunku::NORMALNE;
                }
                else if (wpisanyTyp == "oszczednosciowe") {
                    wybranyTyp = TypRachunku::OSZCZEDNOSCIOWE;
                }
                else if (wpisanyTyp == "walutowe") {
                    wybranyTyp = TypRachunku::WALUTOWE;

                    cout << "Dostepne waluty: euro, dolar, yen" << endl;
                    cout << "Wpisz walute z klawiatury: ";
                    string wpisanaWaluta;
                    cin >> wpisanaWaluta;
                    for (auto& c : wpisanaWaluta) c = tolower(c);

                    if (wpisanaWaluta == "euro") waluta = "EUR";
                    else if (wpisanaWaluta == "dolar") waluta = "USD";
                    else if (wpisanaWaluta == "yen") waluta = "JPY";
                    else {
                        cout << "[Blad] Nie rozpoznano waluty. Ustawiam domyslnie EUR." << endl;
                        waluta = "EUR";
                    }
                }
                else {
                    cout << "[Blad] Niepoprawny typ konta. Operacja anulowana." << endl;
                    continue;
                }

                zalogowanyKlient->otworzKonto(wpisanyTyp);
                cout << "[SYMULACJA] Tworze obiekt na podstawie Twojego wyboru..." << endl;
                aktywneKonto = new Rachunek("111122223333", wybranyTyp, waluta);
            }
            else if (wybor == 4) {
                zalogowanyKlient->wyswietlKonta();
            }
            else if (wybor == 5) {
                cout << "[SYMULACJA] Test metody na domyslnym koncie..." << endl;
                aktywneKonto = new Rachunek("999988887777", TypRachunku::NORMALNE, "PLN");
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