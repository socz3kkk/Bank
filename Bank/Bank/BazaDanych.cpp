#include "BazaDanych.h"
#include "Uzytkownik.h"
#include "Rachunek.h"
#include "KontoOszczednosciowe.h"
#include "KontoWalutowe.h"
#include "Transakcja.h"
#include <fstream>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

BazaDanych::BazaDanych(const string& plik) : nazwaPliku(plik) {}

void BazaDanych::zapiszDane(const vector<unique_ptr<Uzytkownik>>& uzytkownicy) {
    json dane;
    dane["uzytkownicy"] = json::array();

    for (const auto& uzytkownik : uzytkownicy) {
        json klient;
        klient["imie"] = uzytkownik->getImie();
        klient["nazwisko"] = uzytkownik->getNazwisko();
        klient["pesel"] = uzytkownik->getPesel();
        klient["haslo"] = uzytkownik->getHaslo();

       
        klient["konta"] = json::array();
        for (const auto& konto : uzytkownik->getKonta()) {
            json j_konto;
            j_konto["typ"] = konto->getTypKonta();
            j_konto["numer"] = konto->pobierzNumer();
            j_konto["saldo"] = konto->pobierzSaldo();
            j_konto["waluta"] = konto->pobierzWalute();

           
            if (auto ko = dynamic_cast<KontoOszczednosciowe*>(konto.get())) {
                j_konto["oprocentowanie"] = ko->getOprocentowanie();
                j_konto["liczbaWyplat"] = ko->getLiczbaWyplat();
            }
            else if (auto kw = dynamic_cast<KontoWalutowe*>(konto.get())) {
                j_konto["kurs"] = kw->getKurs();
            }

           
            j_konto["historia"] = json::array();
            for (const auto& tx : konto->pobierzHistorie()) {
                json j_tx;
                j_tx["id"] = tx.getIdTransakcji();
                j_tx["typ"] = tx.getTypOperacji();
                j_tx["kwota"] = tx.getKwota();
                j_tx["data"] = tx.getData();
                j_konto["historia"].push_back(j_tx);
            }

            klient["konta"].push_back(j_konto);
        }
        dane["uzytkownicy"].push_back(klient);
    }

    ofstream plik(nazwaPliku);
    if (plik.is_open()) {
        plik << dane.dump(4);
        plik.close();
    }
}

void BazaDanych::wczytajDane(vector<unique_ptr<Uzytkownik>>& uzytkownicy) {
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) return;

    json dane;
    try {
        plik >> dane;
    }
    catch (...) {
        cout << "[BAZA DANYCH] Plik bazy pusty lub uszkodzony. Rozpoczeto z pusta pamiecia.\n";
        return;
    }
    plik.close();

    if (!dane.contains("uzytkownicy")) return;

    for (const auto& klient : dane["uzytkownicy"]) {
        auto nowyUzytkownik = make_unique<Uzytkownik>(
            klient.value("imie", ""),
            klient.value("nazwisko", ""),
            klient.value("pesel", ""),
            klient.value("haslo", "")
        );

        if (klient.contains("konta")) {
            for (const auto& j_konto : klient["konta"]) {
                string typ = j_konto.value("typ", "");
                string numer = j_konto.value("numer", "");
                double saldo = j_konto.value("saldo", 0.0);
                string waluta = j_konto.value("waluta", "PLN");

                unique_ptr<Rachunek> r = nullptr;

               
                if (typ == "Oszczednosciowe") {
                    double opr = j_konto.value("oprocentowanie", 5.0);
                    int lw = j_konto.value("liczbaWyplat", 0);
                    auto ko = make_unique<KontoOszczednosciowe>(numer, saldo, opr);
                    ko->setLiczbaWyplat(lw); 
                    r = move(ko);
                }
                else if (typ == "Walutowe") {
                    double kurs = j_konto.value("kurs", 4.30);
                    r = make_unique<KontoWalutowe>(numer, saldo, waluta, kurs);
                }

                
                if (r) {
                    if (j_konto.contains("historia")) {
                        for (const auto& j_tx : j_konto["historia"]) {
                            Transakcja tx(
                                j_tx.value("id", ""),
                                j_tx.value("typ", ""),
                                j_tx.value("kwota", 0.0),
                                j_tx.value("data", "")
                            );
                            r->dodajTransakcjeDoHistorii(tx);
                        }
                    }
                    
                    nowyUzytkownik->dodajWczytaneKonto(move(r));
                }
            }
        }
        uzytkownicy.push_back(move(nowyUzytkownik));
    }
}