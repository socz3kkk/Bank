# 🏦 Symulator Systemu Bankowego

Projekt to konsolowa aplikacja w języku C++ symulująca działanie nowoczesnego systemu bankowego. Architektura aplikacji opiera się na paradygmatach programowania obiektowego (OOP), wykorzystując dziedziczenie, polimorfizm oraz hermetyzację danych.

## 👥 Zespół Projektowy
* Krystian Bielski
* Daniel Nurkowski
* Dawid Gargula
* Kuba Latos

---

## 🏗️ Architektura Systemu (Diagram UML)

Architektura została zaprojektowana z myślą o skalowalności i bezpieczeństwie. Poniższy diagram przedstawia strukturę klas i relacje między nimi:

![Diagram Klas Systemu Bankowego](diagramUML.png)

---

## 🚀 Główne Moduły Systemu

Aplikacja składa się z następujących, zintegrowanych ze sobą podsystemów:
* **Baza danych użytkowników** - zarządzanie klientami w pamięci systemu.
* **System kont użytkowników** - przypisywanie wielu rachunków do jednego klienta oraz bezpieczna nawigacja między nimi.
* **Typy kont i System rachunków bankowych** - obsługa kont specjalistycznych (np. subkonta oszczędnościowe z mechanizmem lokat i naliczania odsetek).
* **System walutowy** - mechanizmy przeliczania walut i zarządzania kursami (na kontach walutowych).
* **System przelewów** - realizacja płatności między różnymi rachunkami.
* **Historia transakcji** - zorganizowany rejestr operacji dla każdego rachunku.

---

## 🕹️ Możliwości Symulatora (Akcje Użytkownika)

Po uruchomieniu aplikacji, użytkownik ma do dyspozycji interaktywne menu konsolowe, pozwalające na:
1. Zalogowanie się do swojego profilu.
2. Wybór konkretnego rachunku (jeśli posiada ich kilka).
3. Sprawdzanie aktualnego salda konta.
4. Wykonanie przelewu środków na inne konto (Standardowy Przelew).
5. Wykonanie natychmiastowego przelewu BLIK (na numer telefonu).
6. Zarządzanie oszczędnościami (dodanie środków na lokatę).

---

## 🗄️ Przechowywane Dane

W ramach profilu klienta i jego rachunków, system przetwarza następujące dane:
* **Dane osobowe:** Imię, Nazwisko.
* **Dane kontaktowe i weryfikacyjne:** PESEL, Numer telefonu, Adres zameldowania, Nazwisko panieńskie matki.
* **Dane finansowe:** Aktualne saldo przypisanych kont oraz kompletna historia transakcji.