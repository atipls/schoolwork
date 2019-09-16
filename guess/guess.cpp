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

	wprintf(L"Találd ki milyen számra gondoltam 1-1000 között!\n");
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
				fwprintf(stderr, L"HIBA! Egész számot kérek!\n");
				continue;
			}
			tipp = std::atoi(stipp.c_str());
			if (gondolt == tipp)
				wprintf(L"%d tipp után eltaláltad!\n", tippek_szama);
			if (gondolt < tipp)
				wprintf(L"Kissebb számra gondoltam.\n");
			if (gondolt > tipp)
				wprintf(L"Nagyobb számra gondoltam.\n");
		} while (gondolt != tipp);
		wprintf(L"Még egy kör? (Igen/Nem)\n");
		auto valasz = read_line();
		to_upper(valasz);
		ujra = !memcmp(valasz.c_str(), "IGEN", 4); //típuskonverziós trükk
	} while (ujra);
}