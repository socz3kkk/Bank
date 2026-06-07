#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

#include "SystemBankowy.h"
#include "Uzytkownik.h"
#include "Rachunek.h"
#include "KontoOszczednosciowe.h"
#include "KontoWalutowe.h"

using namespace std;

void wyczyscBufor() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void poczekajNaEnter() {
    cout << "\n[Nacisnij ENTER, aby wrocic do menu...]";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void rysujNaglowek(const string& tytul) {
    cout << "\n============================================\n";
    cout << "   " << tytul << "\n";
    cout << "============================================\n";
}

void menuZarzadzaniaKontami(Uzytkownik* zalogowany) {
    int wybor = -1;
    while (wybor != 0) {
        rysujNaglowek("MODUL: ZARZADZANIE KONTAMI");
        cout << "1. Wyswietl wszystkie moje konta\n";
        cout << "2. Otworz nowe Konto Oszczednosciowe\n";
        cout << "3. Otworz nowe Konto Walutowe\n";
        cout << "4. Zamknij istniejace konto\n";
        cout << "5. Wyswietl historie transakcji konta\n";
        cout << "0. Powrot do Menu Glownego\n";
        cout << "--------------------------------------------\n";
        cout << "Twoj wybor: ";

        if (!(cin >> wybor)) { wyczyscBufor(); continue; }

        try {
            switch (wybor) {
            case 1:
                cout << "\n--- TWOJE AKTYWNE KONTA ---\n";
                zalogowany->wyswietlKonta();
                poczekajNaEnter();
                break;
            case 2:
                zalogowany->otworzKonto("Oszczednosciowe");
                poczekajNaEnter();
                break;
            case 3:
                zalogowany->otworzKonto("Walutowe");
                poczekajNaEnter();
                break;
            case 4: {
                cout << "\n--- ZAMYKANIE KONTA ---\n";
                zalogowany->wyswietlKonta();
                cout << "\nPodaj numer konta do zamkniecia (indeks z listy): ";
                int indeks;
                if (!(cin >> indeks) || indeks < 1) {
                    wyczyscBufor();
                    throw invalid_argument("Nieprawidlowy format indeksu.");
                }
                zalogowany->zamknijKonto(indeks - 1);
                poczekajNaEnter();
                break;
            }
            case 5: {
                cout << "\n--- HISTORIA TRANSAKCJI ---\n";
                zalogowany->wyswietlKonta();
                cout << "\nWybierz numer konta do sprawdzenia historii (indeks z listy): ";
                int indeks;
                if (!(cin >> indeks) || indeks < 1) {
                    wyczyscBufor();
                    throw invalid_argument("Nieprawidlowy format indeksu.");
                }

                Rachunek* konto = zalogowany->pobierzRachunek(indeks - 1);
                const auto& historia = konto->pobierzHistorie();

                if (historia.empty()) {
                    cout << "[INFORMACJA] Brak historii transakcji dla tego konta.\n";
                }
                else {
                    cout << "\nHistoria dla konta " << konto->pobierzNumer() << ":\n";
                    cout << "--------------------------------------------\n";
                    for (const auto& tx : historia) {
                        cout << tx << "\n";
                    }
                    cout << "--------------------------------------------\n";
                }
                poczekajNaEnter();
                break;
            }
            case 0: break;
            default: cout << "[BLAD] Niepoprawna opcja.\n";
            }
        }
        catch (const exception& e) {
            cout << "\n[BLAD SYSTEMU]: " << e.what() << "\n";
            poczekajNaEnter();
        }
    }
}

void menuOperacjiKrajowych(Uzytkownik* zalogowany, SystemBankowy& bank) {
    int wybor = -1;
    while (wybor != 0) {
        rysujNaglowek("MODUL: OPERACJE KRAJOWE (PLN)");
        cout << "1. Sprawdz saldo konta PLN\n";
        cout << "2. Wplac srodki (PLN)\n";
        cout << "3. Wyplac srodki (PLN)\n";
        cout << "4. Wykonaj przelew na inne konto\n";
        cout << "0. Powrot do Menu Glownego\n";
        cout << "--------------------------------------------\n";
        cout << "Twoj wybor: ";

        if (!(cin >> wybor)) { wyczyscBufor(); continue; }
        if (wybor == 0) break;

        try {
            cout << "\n--- TWOJE KONTA KRAJOWE (PLN) ---\n";
            const auto& konta = zalogowany->getKonta();
            bool maKontaPLN = false;

            for (size_t i = 0; i < konta.size(); ++i) {
                if (dynamic_cast<KontoWalutowe*>(konta[i].get()) == nullptr) {
                    cout << i + 1 << ". ";
                    konta[i]->wyswietlSzczegoly();
                    cout << "\n";
                    maKontaPLN = true;
                }
            }

            if (!maKontaPLN) {
                cout << "[INFORMACJA] Nie posiadasz zadnych kont w PLN do operacji krajowych.\n";
                poczekajNaEnter();
                continue;
            }
            // ------------------------------------------------

            cout << "\nWybierz numer konta ZRODLOWEGO do operacji (indeks z listy): ";
            int indeks;
            if (!(cin >> indeks) || indeks < 1) { wyczyscBufor(); throw invalid_argument("Nieprawidlowy format indeksu."); }

            Rachunek* kontoZrodlowe = zalogowany->pobierzRachunek(indeks - 1);

            if (dynamic_cast<KontoWalutowe*>(kontoZrodlowe) != nullptr) {
                cout << "[BLAD] Wybrano Konto Walutowe! Operacje krajowe obsluguja tylko konta PLN.\n";
                poczekajNaEnter();
                continue;
            }

            if (wybor == 1) {
                cout << "[INFORMACJA] Aktualne saldo wynosi: " << kontoZrodlowe->pobierzSaldo() << " PLN\n";
                poczekajNaEnter();
                continue;
            }

            if (wybor == 4) {
                cout << "Podaj DOCELOWY numer konta (np. PL123456): ";
                string numerDocelowy;
                cin >> numerDocelowy;

                Rachunek* kontoDocelowe = bank.znajdzRachunek(numerDocelowy);

                if (kontoDocelowe == nullptr) {
                    throw invalid_argument("Nie znaleziono konta o podanym numerze w systemie!");
                }

                if (dynamic_cast<KontoWalutowe*>(kontoDocelowe) != nullptr) {
                    throw invalid_argument("Odmowa transakcji! Konto docelowe jest w walucie obcej. Przelewy obslugowane sa tylko dla kont PLN.");
                }

                double kwota;
                cout << "Podaj kwote przelewu: ";
                if (!(cin >> kwota)) { wyczyscBufor(); throw invalid_argument("Oczekiwano wartosci liczbowej."); }

                if (kontoZrodlowe->wykonajPrzelew(kontoDocelowe, kwota)) {
                    cout << "[SUKCES] Przelew " << kwota << " PLN do " << numerDocelowy << " zrealizowany.\n";
                    bank.zapiszStanSystemu();
                }
                else {
                    cout << "[BLAD] Operacja odrzucona (brak srodkow lub wybrano to samo konto).\n";
                }
                poczekajNaEnter();
                continue;
            }

            double kwota;
            cout << "Podaj kwote w PLN: ";
            if (!(cin >> kwota)) { wyczyscBufor(); throw invalid_argument("Oczekiwano wartosci liczbowej."); }

            if (wybor == 2) {
                kontoZrodlowe->wplac(kwota);
                cout << "[SUKCES] Pomyslnie wplacono " << kwota << " PLN na konto.\n";
            }
            else if (wybor == 3) {
                if (kontoZrodlowe->wyplac(kwota)) {
                    cout << "[SUKCES] Pomyslnie wyplacono " << kwota << " PLN.\n";
                }
                else {
                    cout << "[BLAD] Operacja odrzucona (brak srodkow lub limit).\n";
                }
            }
            poczekajNaEnter();
        }
        catch (const exception& e) {
            cout << "\n[BLAD SYSTEMU]: " << e.what() << "\n";
            poczekajNaEnter();
        }
    }
}

void menuOperacjiWalutowych(Uzytkownik* zalogowany) {
    int wybor = -1;
    while (wybor != 0) {
        rysujNaglowek("MODUL: OPERACJE WALUTOWE");
        cout << "1. Sprawdz saldo konta walutowego\n";
        cout << "2. Wplac walute obca\n";
        cout << "3. Wyplac walute obca\n";
        cout << "4. Symulator wymiany walut (Przelicz na PLN)\n";
        cout << "0. Powrot do Menu Glownego\n";
        cout << "--------------------------------------------\n";
        cout << "Twoj wybor: ";

        if (!(cin >> wybor)) { wyczyscBufor(); continue; }
        if (wybor == 0) break;

        try {
            cout << "\n--- TWOJE KONTA WALUTOWE ---\n";
            const auto& konta = zalogowany->getKonta();
            bool maKontaWalutowe = false;

            for (size_t i = 0; i < konta.size(); ++i) {
                if (dynamic_cast<KontoWalutowe*>(konta[i].get()) != nullptr) {
                    cout << i + 1 << ". ";
                    konta[i]->wyswietlSzczegoly();
                    cout << "\n";
                    maKontaWalutowe = true;
                }
            }

            if (!maKontaWalutowe) {
                cout << "[INFORMACJA] Nie posiadasz zadnych kont walutowych.\n";
                poczekajNaEnter();
                continue;
            }
            // ------------------------------------------------------

            cout << "\nWybierz numer konta WALUTOWEGO (indeks z listy): ";
            int indeks;
            if (!(cin >> indeks) || indeks < 1) { wyczyscBufor(); throw invalid_argument("Nieprawidlowy format indeksu."); }

            Rachunek* konto = zalogowany->pobierzRachunek(indeks - 1);
            KontoWalutowe* kontoWal = dynamic_cast<KontoWalutowe*>(konto);

            if (kontoWal == nullptr) {
                throw invalid_argument("Wybrane konto NIE JEST kontem walutowym!");
            }

            if (wybor == 1) {
                cout << "[INFORMACJA] Aktualne saldo wynosi: " << kontoWal->pobierzSaldo()
                    << " " << kontoWal->pobierzWalute() << "\n";
                poczekajNaEnter();
                continue;
            }

            double kwota;
            cout << "Podaj kwote w walucie obcej: ";
            if (!(cin >> kwota)) { wyczyscBufor(); throw invalid_argument("Oczekiwano wartosci liczbowej."); }

            switch (wybor) {
            case 2:
                kontoWal->wplacWalute(kwota);
                cout << "[SUKCES] Zaksiegowano wplate w walucie konta.\n";
                break;
            case 3:
                if (kontoWal->wyplacWalute(kwota)) {
                    cout << "[SUKCES] Pomyslnie wyplacono " << kwota << " w walucie konta.\n";
                }
                else {
                    cout << "[BLAD] Operacja odrzucona (brak srodkow).\n";
                }
                break;
            case 4:
                cout << "[KURS WYMIANY] Kwota " << kwota << " w Twojej walucie obcej, "
                    << "po przewalutowaniu daje: " << kontoWal->wymienNaPln(kwota) << " PLN.\n";
                break;
            default:
                cout << "[BLAD] Niepoprawna opcja.\n";
            }
            poczekajNaEnter();
        }
        catch (const exception& e) {
            cout << "\n[BLAD SYSTEMU]: " << e.what() << "\n";
            poczekajNaEnter();
        }
    }
}

void menuOperacjiOkresowych(Uzytkownik* zalogowany) {
    rysujNaglowek("MODUL: OPERACJE OKRESOWE");
    try {
        zalogowany->wyswietlKonta();
        cout << "\nWybierz konto, dla ktorego chcesz zamknac okres rozliczeniowy (indeks z listy): ";
        int indeks;
        if (!(cin >> indeks) || indeks < 1) { wyczyscBufor(); throw invalid_argument("Nieprawidlowy format indeksu."); }

        Rachunek* konto = zalogowany->pobierzRachunek(indeks - 1);

        KontoOszczednosciowe* kontoOszcz = dynamic_cast<KontoOszczednosciowe*>(konto);
        KontoWalutowe* kontoWalut = dynamic_cast<KontoWalutowe*>(konto);

        if (kontoOszcz != nullptr) {
            kontoOszcz->wykonajOperacjeOkresowa();
            cout << "[SUKCES] Naleznosci okresowe dla Konta Oszczednosciowego zostaly naliczone.\n";
        }
        else if (kontoWalut != nullptr) {
            kontoWalut->wykonajOperacjeOkresowa();
            cout << "[SUKCES] Wykonano operacje okresowa dla Konta Walutowego.\n";
        }
        else {
            cout << "[INFORMACJA] To konkretne konto nie wspiera operacji okresowych.\n";
        }
        poczekajNaEnter();
    }
    catch (const exception& e) {
        cout << "\n[BLAD SYSTEMU]: " << e.what() << "\n";
        poczekajNaEnter();
    }
}

int main() {
    SystemBankowy bank("Narodowy Bank Obywatelski");
    Uzytkownik* zalogowanyKlient = nullptr;
    int wybor = -1;

    while (wybor != 0) {
        if (zalogowanyKlient == nullptr) {
            rysujNaglowek("SYSTEM BANKOWY - EKRAN POWITALNY");
            cout << "1. Zaloguj sie do bankowosci\n";
            cout << "2. Zarejestruj nowego klienta\n";
            cout << "0. Wyjdz z systemu\n";
            cout << "--------------------------------------------\n";
            cout << "Twoj wybor: ";

            if (!(cin >> wybor)) { wyczyscBufor(); continue; }
            if (wybor == 0) break;

            try {
                if (wybor == 1) {
                    string p, h;
                    cout << "Podaj numer PESEL: "; cin >> p;
                    cout << "Podaj haslo: "; cin >> h;
                    zalogowanyKlient = bank.zaloguj(p, h);
                    cout << "[SUKCES] Logowanie przebieglo pomyslnie.\n";
                    poczekajNaEnter();
                }
                else if (wybor == 2) {
                    string im, naz, p, h;
                    cout << "Podaj imie: "; cin >> im;
                    cout << "Podaj nazwisko: "; cin >> naz;
                    cout << "Podaj PESEL (11 znakow): "; cin >> p;
                    cout << "Ustanow haslo: "; cin >> h;

                    if (bank.zarejestrujKlienta(im, naz, p, h) != nullptr) {
                        cout << "[SUKCES] Profil klienta zostal pomyslnie utworzony.\n";
                    }
                    poczekajNaEnter();
                }
            }
            catch (const exception& e) {
                cout << "\n[BLAD LOGOWANIA/REJESTRACJI]: " << e.what() << "\n";
                poczekajNaEnter();
            }
        }
        else {
            rysujNaglowek("MENU GLOWNE APLIKACJI");
            cout << "Witaj, " << zalogowanyKlient->getImie() << " " << zalogowanyKlient->getNazwisko() << "!\n";
            cout << "--------------------------------------------\n";
            cout << "1. Zarzadzanie kontami     (Otwieranie, Zamykanie, Podglad)\n";
            cout << "2. Operacje krajowe PLN    (Wplaty, Wyplaty, Przelew)\n";
            cout << "3. Operacje walutowe       (Wplaty, Wyplaty, Kantorek)\n";
            cout << "4. Operacje okresowe       (Zamykanie miesiaca, Odsetki)\n";
            cout << "9. Wyloguj uzytkownika\n";
            cout << "0. Wyjdz z systemu\n";
            cout << "--------------------------------------------\n";
            cout << "Wybierz modul: ";

            if (!(cin >> wybor)) { wyczyscBufor(); continue; }

            switch (wybor) {
            case 1: menuZarzadzaniaKontami(zalogowanyKlient); break;
            case 2: menuOperacjiKrajowych(zalogowanyKlient, bank); break;
            case 3: menuOperacjiWalutowych(zalogowanyKlient); break;
            case 4: menuOperacjiOkresowych(zalogowanyKlient); break;
            case 9:
                zalogowanyKlient = nullptr;
                cout << "\n[SUKCES] Zostales wylogowany ze wzgledow bezpieczenstwa.\n";
                poczekajNaEnter();
                break;
            case 0: break;
            default:
                cout << "[BLAD] Niepoprawna opcja z menu.\n";
                poczekajNaEnter();
            }
        }
    }

    cout << "\nDziekujemy za skorzystanie z naszych uslug. Do widzenia!\n";
    return 0;
}