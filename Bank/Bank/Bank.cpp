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

void menuOperacjiKrajowych(Uzytkownik* zalogowany) {
    int wybor = -1;
    while (wybor != 0) {
        rysujNaglowek("MODUL: OPERACJE KRAJOWE (PLN)");
        cout << "1. Sprawdz saldo konta PLN\n";
        cout << "2. Wplac srodki (PLN)\n";
        cout << "3. Wyplac srodki (PLN)\n";
        cout << "0. Powrot do Menu Glownego\n";
        cout << "--------------------------------------------\n";
        cout << "Twoj wybor: ";

        if (!(cin >> wybor)) { wyczyscBufor(); continue; }
        if (wybor == 0) break;

        try {
            zalogowany->wyswietlKonta();
            cout << "\nWybierz numer konta do operacji (indeks z listy): ";
            int indeks;
            if (!(cin >> indeks) || indeks < 1) { wyczyscBufor(); throw invalid_argument("Nieprawidlowy format indeksu."); }

            Rachunek* konto = zalogowany->pobierzRachunek(indeks - 1);

            if (dynamic_cast<KontoWalutowe*>(konto) != nullptr) {
                cout << "[BLAD] Wybrano Konto Walutowe! Do zarzadzania nim posluzy Ci modul 'Operacje walutowe'.\n";
                poczekajNaEnter();
                continue;
            }

            if (wybor == 1) {
                cout << "[INFORMACJA] Aktualne saldo wynosi: " << konto->pobierzSaldo() << " PLN\n";
                poczekajNaEnter();
                continue;
            }

            double kwota;
            cout << "Podaj kwote w PLN: ";
            if (!(cin >> kwota)) { wyczyscBufor(); throw invalid_argument("Oczekiwano wartosci liczbowej."); }

            if (wybor == 2) {
                konto->wplac(kwota);
                cout << "[SUKCES] Pomyslnie wplacono " << kwota << " PLN na konto.\n";
            }
            else if (wybor == 3) {
                if (konto->wyplac(kwota)) {
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
        cout << "1. Wplac walute obca\n";
        cout << "2. Wyplac walute obca\n";
        cout << "3. Symulator wymiany walut (Przelicz na PLN)\n";
        cout << "0. Powrot do Menu Glownego\n";
        cout << "--------------------------------------------\n";
        cout << "Twoj wybor: ";

        if (!(cin >> wybor)) { wyczyscBufor(); continue; }
        if (wybor == 0) break;

        try {
            zalogowany->wyswietlKonta();
            cout << "\nWybierz numer konta WALUTOWEGO (indeks z listy): ";
            int indeks;
            if (!(cin >> indeks) || indeks < 1) { wyczyscBufor(); throw invalid_argument("Nieprawidlowy format indeksu."); }

            Rachunek* konto = zalogowany->pobierzRachunek(indeks - 1);
            KontoWalutowe* kontoWal = dynamic_cast<KontoWalutowe*>(konto);

            if (kontoWal == nullptr) {
                throw invalid_argument("Wybrane konto NIE JEST kontem walutowym!");
            }

            double kwota;
            cout << "Podaj kwote w walucie obcej: ";
            if (!(cin >> kwota)) { wyczyscBufor(); throw invalid_argument("Oczekiwano wartosci liczbowej."); }

            switch (wybor) {
            case 1:
                kontoWal->wplacWalute(kwota);
                cout << "[SUKCES] Zaksiegowano wplate w walucie konta.\n";
                break;
            case 2:
                if (kontoWal->wyplacWalute(kwota)) {
                    cout << "[SUKCES] Pomyslnie wyplacono " << kwota << " w walucie konta.\n";
                }
                else {
                    cout << "[BLAD] Operacja odrzucona.\n";
                }
                break;
            case 3:
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
            cout << "2. Operacje krajowe PLN    (Wplaty, Wyplaty, Saldo)\n";
            cout << "3. Operacje walutowe       (Wplaty, Wyplaty, Kantorek)\n";
            cout << "4. Operacje okresowe       (Zamykanie miesiaca, Odsetki)\n";
            cout << "9. Wyloguj uzytkownika\n";
            cout << "0. Wyjdz z systemu\n";
            cout << "--------------------------------------------\n";
            cout << "Wybierz modul: ";

            if (!(cin >> wybor)) { wyczyscBufor(); continue; }

            switch (wybor) {
            case 1: menuZarzadzaniaKontami(zalogowanyKlient); break;
            case 2: menuOperacjiKrajowych(zalogowanyKlient); break;
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