#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <time.h>

std::uniform_int_distribution<> distr(1, 1001);
std::mt19937 random(uint32_t(time(nullptr)));

auto egesz_szam(const std::string& szam) -> bool { return std::count_if(szam.begin(), szam.end(), ::isdigit) == szam.length(); }
auto read_line() -> std::string {
	std::string ret{};
	std::getline(std::cin, ret);
	return ret;
}
auto to_upper(std::string& str) { std::transform(str.begin(), str.end(), str.begin(), ::toupper); }
constexpr auto cheat = true;

auto main() -> int32_t {
	setlocale(LC_ALL, "hu_HU"); //magyar konzol

	wprintf(L"Tal�ld ki milyen sz�mra gondoltam 1-1000 k�z�tt!\n");
	uint32_t gondolt{}, tipp{}, tippek_szama{};
	bool ujra = true;
	do {
		gondolt = distr(random);
		tipp = tippek_szama = 0;
		if (cheat)
			wprintf(L"(%d-re gondoltam)\n", gondolt);
		do {
			wprintf(L"Tippelj!: ");
			tippek_szama++;
			auto stipp = read_line();
			if (!egesz_szam(stipp)) {
				fwprintf(stderr, L"HIBA! Eg�sz sz�mot k�rek!\n");
				continue;
			}
			tipp = std::atoi(stipp.c_str());
			if (gondolt == tipp)
				wprintf(L"%d tipp ut�n eltal�ltad!\n", tippek_szama);
			if (gondolt < tipp)
				wprintf(L"Kissebb sz�mra gondoltam.\n");
			if (gondolt > tipp)
				wprintf(L"Nagyobb sz�mra gondoltam.\n");
		} while (gondolt != tipp);
		wprintf(L"M�g egy k�r? (Igen/Nem)\n");
		auto valasz = read_line();
		to_upper(valasz);
		ujra = !memcmp(valasz.c_str(), "IGEN", 4); //t�puskonverzi�s tr�kk
	} while (ujra);
}