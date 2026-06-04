#pragma once
#include <string>
#include <cctype>
#include <algorithm>

class Walidator {
public:
    static bool czyPoprawnyPesel(const std::string& pesel) {
        if (pesel.length() != 11) return false;
        return std::all_of(pesel.begin(), pesel.end(), ::isdigit);
    }

    static bool czySilneHaslo(const std::string& haslo) {
        if (haslo.length() < 12) return false;

        bool maDuza = false, maMala = false, maCyfre = false, maZnakSpec = false;
        std::string znakiSpecjalne = "!@#$%^&*()-_+={}[]|:;<>,.?/";

        for (char c : haslo) {
            if (isupper(c)) maDuza = true;
            else if (islower(c)) maMala = true;
            else if (isdigit(c)) maCyfre = true;
            else if (znakiSpecjalne.find(c) != std::string::npos) maZnakSpec = true;
        }

        return maDuza && maMala && maCyfre && maZnakSpec;
    }
};