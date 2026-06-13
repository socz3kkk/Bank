🏦 Symulator Systemu Bankowego

Projekt to konsolowa aplikacja w języku C++ symulująca działanie nowoczesnego systemu bankowego. Architektura aplikacji opiera się na paradygmatach programowania obiektowego (OOP), wykorzystując dziedziczenie, polimorfizm, hermetyzację danych oraz nowoczesne wzorce zarządzania pamięcią.

🏗️ Architektura Systemu (Diagram UML)

Architektura została zaprojektowana z myślą o skalowalności i bezpieczeństwie. Poniższy diagram przedstawia strukturę klas i relacje między nimi:

![Diagram Klas Systemu Bankowego](diagramUML.png)

🚀 Główne Moduły Systemu

Aplikacja składa się z następujących, zintegrowanych ze sobą podsystemów:

Baza danych użytkowników (JSON) - centralny zapis stanu aplikacji. Dzięki zewnętrznej bibliotece json.hpp stan obiektów (dane klientów, salda, historia) jest trwale serializowany i przechowywany w pliku baza_danych.json.

System użytkowników i pamięci - przypisywanie wielu rachunków do jednego klienta. System wykorzystuje nowoczesne inteligentne wskaźniki (std::unique_ptr z biblioteki <memory>), gwarantując bezpieczeństwo pamięciowe i brak wycieków (memory leaks).

Polimorficzny system rachunków - klasa bazowa Rachunek (definiująca walutę i saldo) rozszerzona o specyficzne warianty:

KontoOszczednosciowe – posiada mechanizm naliczania oprocentowania oraz limity darmowych wypłat (każda transakcja powyżej limitu obciążana jest stałą opłatą rzędu 10 jednostek).

KontoWalutowe – umożliwia operacje w innej walucie, uwzględniając definiowany kurs wymiany oraz 2-procentową prowizję operacyjną.

System przelewów i autorytet logiki - zarządzany w głównej pętli zdarzeń w Bank.cpp, posiada solidną walidację danych wejściowych (czyszczenie buforów strumienia std::cin), zabezpieczając system przed crashami przy błędnych danych od użytkownika.

Rejestr transakcji - klasa Transakcja zapisująca unikalne ID operacji, typ, kwotę i dokładną datę dla pełnego audytu konta.

👥 Zespół Projektowy i Wkład

Jakub Latos – Tworzenie i architektura głównej klasy bazowej Rachunek. Odpowiedzialny za bazowe mechanizmy przechowywania salda oraz operacje na koncie (wpłaty/wypłaty) i wdrożenie metod wirtualnych, otwierając drogę do polimorfizmu.

Krystian Bielski – Zbudowanie centralnej klasy SystemBankowy oraz pliku Bank.cpp. Projektowanie interfejsu użytkownika, nawigacji oraz poprawnego przepływu sterowania. Odpowiadał za walidację wprowadzanych danych wejściowych.

Dawid Gargula – Implementacja BazyDanych oraz systemu tworzenia logów w klasie Transakcja. Odpowiadał za integrację zewnętrznej biblioteki Nlohmann JSON do strukturalnego i trwałego zapisu danych w pamięci masowej.

Daniel Nurkowski – Rozszerzenie systemu o konta specjalistyczne. Zaimplementowanie klas KontoOszczednosciowe (z logiką prowizji i limitów) oraz KontoWalutowe (mechanika kursów walut), sprawnie wykorzystując mechanizmy dziedziczenia w C++.

⚙️ Instrukcja kompilacji i uruchomienia

Projekt został napisany z wykorzystaniem nowoczesnych elementów standardu C++17 i jest przystosowany do środowiska MSVC.

Kompilacja za pomocą Visual Studio (Zalecane):

Sklonuj repozytorium na swój dysk: git clone https://github.com/socz3kkk/Bank.git

Otwórz plik rozwiązania projektu, klikając w Bank.sln.

Wybierz konfigurację budowania na górnym pasku (np. x64 Debug).

Skompiluj projekt (Ctrl + Shift + B) i uruchom (F5).

📊 Sprawozdanie z zajęć projektowych

Cel i założenia: Celem było zaprezentowanie solidnej implementacji zasad OOP, poprawnego podziału odpowiedzialności na klasy (Single Responsibility) oraz współpracy z wykorzystaniem systemu kontroli Git.

Wnioski i realizacja: Projekt udowodnił skuteczność dziedziczenia i polimorfizmu w systemach bankowych. Użycie wektorów w połączeniu z std::unique_ptr skutecznie wyeliminowało problemy manualnego zarządzania wskaźnikami. Ponadto, wdrożenie zewnętrznej biblioteki JSON udowodniło umiejętność skalowania aplikacji o zewnętrzne zależności, zapewniając solidną persystencję danych w pliku baza_danych.json. System działa stabilnie i w pełni odpowiada początkowym założeniom.
