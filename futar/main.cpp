#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include "parser.hpp"
parser* g_parser;

long file_meret(std::ifstream& ifs) {
	auto size = ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	ifs.clear();
	return long(size);
}

void het_nedik_napja_kmben(const char* fmt, std::function<bool(futar_ut&, futar_ut&)> pred) {
	auto& utak = g_parser->m_utak;
	auto smallest = std::min_element(utak.begin(), utak.end(), pred);
	auto osszes_km = 0;
	for (size_t i = 0; i < utak.size(); i++)
		if (utak[i].m_nap == smallest->m_nap)
			osszes_km += utak[i].m_tavolsag;
	printf(fmt, osszes_km);
}

void futar_szabadnapok() {
	printf("4. feladat: Szabadnapok.\n");
	auto& utak = g_parser->m_utak;
	bool napok[7]{ false };

	for (size_t i = 0; i < utak.size(); i++)
		napok[utak[i].m_nap - 1] = true;

	for (size_t i = 0; i < 6; i++)
		if (!napok[i])
			printf("\tA h�t %d. napj�n nem dolgozott a fut�r.\n", i + 1);
}

void het_legtobb_fuvar() {
	printf("5. feladat: Legt�bb fuvar a napon.\n");

	auto& utak = g_parser->m_utak;
	int fuvarok[7]{ 0 };
	for (auto& ut : utak)
		fuvarok[ut.m_nap - 1]++;

	int maxhet = 0, maxidx = 0;
	for (size_t i = 0; i < 6; i++) {
		if (fuvarok[i] > maxhet) {
			maxhet = fuvarok[i];
			maxidx = i;
		}
	}
	printf("\tA legt�bb fuvar a h�t %d. napj�n volt. (%d fuvar)\n", maxidx + 1, maxhet);
}

void napok_tavolsaga() {
	printf("6. feladat: Napok t�vols�ga.\n");
	auto& utak = g_parser->m_utak;
	int tavolsagok[7]{ 0 };
	for (auto& ut : utak)
		tavolsagok[ut.m_nap - 1] += ut.m_tavolsag;
	for (size_t i = 0; i < 6; i++) {
		printf("\t%d. nap: %d km\n", i + 1, tavolsagok[i]);
	}
}

int get_dijazas(int tavolsag) {
#define range(min, max) (tavolsag >= min && tavolsag <= max)

	if (range(1, 2))
		return 500;
	if (range(3, 5))
		return 700;
	if (range(6, 10))
		return 900;
	if (range(11, 20))
		return 1400;
	if (range(21, 30))
		return 2000;

	return INT_MAX;

#undef range
}

void dijazas_kerdez() {
	printf("7. feladat: T�vols�g: ");
	int tav;
	std::cin >> tav;
	printf("\t%d km: %d ft.\n", tav, get_dijazas(tav));
}

//8. feladat
void dijazas_osszehatarozas() {
	auto& utak = g_parser->m_utak;
	std::ofstream ofs("dijazas.txt");

	std::sort(utak.begin(), utak.end(), [](futar_ut& a, futar_ut& b) { return a.m_fuvar < b.m_fuvar; });

	for (size_t i = 0; i < 6; i++) {
		for (size_t j = 0; j < utak.size(); j++) {
			if (utak[j].m_nap == i - 1)
				ofs << utak[j].m_nap << ". nap "
				<< utak[j].m_fuvar << ". �t: "
				<< get_dijazas(utak[j].m_tavolsag) << " Ft" << std::endl;
		}
	}
	ofs.flush();
	ofs.close();
}

void futar_fizetes() {
	int osszeg = 0;
	auto& utak = g_parser->m_utak;
	for (auto& ut : utak)
		osszeg += get_dijazas(ut.m_tavolsag);

	printf("9. feladat: �sszes fizet�s: %d Ft\n", osszeg);
}

int main() {
	setlocale(LC_ALL, "hu_HU");

	//1. feladat
	auto ifs = std::ifstream("tavok.txt", std::ios::ate);
	auto meret = file_meret(ifs);
	auto tavok = new char[meret + 1];
	memset(tavok, 0, meret + 1);

	ifs.read(tavok, meret);
	ifs.close();

	g_parser = new parser(tavok);
	g_parser->parse();

	het_nedik_napja_kmben("2. feladat: A h�t els� napj�n a fut�rnak %d km �tja volt.\n", [&](futar_ut& a, futar_ut& b) { return a.m_nap < b.m_nap; });
	het_nedik_napja_kmben("3. feladat: A h�t utols� napj�n a fut�rnak %d km �tja volt.\n", [&](futar_ut& a, futar_ut& b) { return a.m_nap > b.m_nap; });
	futar_szabadnapok();
	het_legtobb_fuvar();
	napok_tavolsaga();
	dijazas_kerdez();
	dijazas_osszehatarozas();
	futar_fizetes();

	delete g_parser;
	std::cin.get();
	return 0;
}