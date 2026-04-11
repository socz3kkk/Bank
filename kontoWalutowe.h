#pragma once
#ifndef KontoWalutowe_h
#define KontoWalutowe_h

#include <iostream>
#include <string>

class KontoWalutowe {
private:
	std::string waluta;
	double saldo;

public:
	KontoWalutowe(std::string w, double s) : waluta(w), saldo(s) {}

	void przewalutuj(std::string DocelowaWaluta) {
		std::cout << "Wykonano przewalutowanie dla: " << waluta << std::endl;
		
		double KursPLN = 1;
		double KursUSD = 0.25;
		double KursEUR = 0.23;
		double KursJPY = 38;

		double KwotaPLN;

		if (waluta == "PLN")KwotaPLN = saldo;
		else if (waluta == "USD") KwotaPLN = saldo / KursUSD;
		else if (waluta == "EUR") KwotaPLN = saldo / KursEUR;
		else if (waluta == "JPY") KwotaPLN = saldo / KursJPY;
		else {
			std::cout << "Nieobslugiwana waluta zrodlowa" << std::endl;
			return;
		}

		if (DocelowaWaluta == "PLN") saldo = KwotaPLN * KursPLN;
		else if (DocelowaWaluta == "USD") saldo = KwotaPLN * KursUSD;
		else if (DocelowaWaluta == "EUR") saldo = KwotaPLN * KursEUR;
		else if (DocelowaWaluta == "JPY") saldo = KwotaPLN * KursJPY;
		else {
			std::cout << "Nieobslugiwana waluta docelowa!!!1!" << std::endl;
			return;
		}

		waluta = DocelowaWaluta;
		std::cout << "Przewalutowano pomyslnie. Nowy stan konta: " << saldo << " " << waluta << std::endl;
	}


	void PokazSaldo() {
		std::cout << "Stan konta: " << saldo << " " << waluta << std::endl;
	}
};
#endif

