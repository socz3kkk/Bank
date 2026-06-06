#include <iostream>
#include "KontoOszczednosciowe.h"
#include "KontoWalutowe.h"

using namespace std;

int main() {
    cout << "--- Symulator Systemu Bankowego (Smoke Test) ---\n";

    KontoOszczednosciowe kontoOszcz("123456789", 1500.0, 5.0);
    KontoWalutowe kontoWal("987654321", 500.0, "EUR", 4.30);

    kontoOszcz.naliczOdsetki();

    cout << "\nWyswietlanie informacji o kontach:\n";
    kontoOszcz.wyswietlInformacje();
    cout << "\n";
    kontoWal.wyswietlInformacje();

    return 0;
}