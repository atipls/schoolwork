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
constexpr auto cheat = true; //constexpr hogy ki tudja a fordító optimizálni

int main() {
	fprintf(stdout, "Talald ki milyen szamra gondoltam 1-1000 kozott!\n");
	uint32_t gondolt{}, tipp{}, tippek_szama{};
	bool ujra = true;
	do {
		gondolt = distr(random);
		tipp = 0;
		tippek_szama = 0;
		if (cheat)
			fprintf(stderr, "(%d-re gondoltam)\n", gondolt);
		do {
			fprintf(stdout, "Tippelj!: ");
			tippek_szama++;
			auto stipp = read_line();
			if (!egesz_szam(stipp)) {
				fprintf(stderr, "HIBA! Egesz szamot kerek!\n");
				continue;
			}
			tipp = std::atoi(stipp.c_str());
			if (gondolt == tipp)
				fprintf(stdout, "%d tipp utan eltalaltad!\n", tippek_szama);
			if (gondolt < tipp)
				fprintf(stdout, "Kissebb szamra gondoltam.\n");
			if (gondolt > tipp)
				fprintf(stdout, "Nagyobb szamra gondoltam.\n");
		} while (gondolt != tipp);
		fprintf(stdout, "Meg egy kor? (Igen/Nem)\n");
		auto valasz = read_line();
		to_upper(valasz);
		ujra = !memcmp(valasz.c_str(), "IGEN", 4); //típuskonverziós trükk
	} while (ujra);
}