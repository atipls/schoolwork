#include <iostream>
#include <fstream>
#include <random>
#include "parser.hpp"
#include <time.h>

parser* g_parser = nullptr;
int32_t g_sz[15]; //véletlen számok

std::uniform_int_distribution<int> g_dist(-200, 200);
std::mt19937 g_engine;

long file_meret(std::ifstream& ifs) {
	auto size = ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	ifs.clear();
	return long(size);
}

void adatok_kiir() {
	printf("1. feladat: \n");
	for (auto& adat : g_parser->m_adat)
		printf("Település: %-12s Azonosító: %d KM: %d\n", adat.m_telepules.c_str(), adat.m_id, adat.m_km);
}

void veletlen_szamok_feltolt() {
	printf("2. feladat: \n");
	for (int32_t i = 0; i < 15; i++) {
		g_sz[i] = g_dist(g_engine);
		printf("%d ", g_sz[i]);
	}
	printf("\n");
}

void veletlen_szamok_osszege() {
	printf("3. feladat: \n");
	int32_t osszeg = 0;
	for (int32_t i = 0; i < 15; i++)
		osszeg += g_sz[i];
	printf("Számok összege: %d\n", osszeg);
}

void szamok_max_erteke() {
	printf("4. feladat: \n");
	int32_t max = INT_MIN, maxidx = 0;
	for (int32_t i = 0; i < 15; i++) {
		if (max < g_sz[i]) {
			max = g_sz[i];
			maxidx = i;
		}
	}
	printf("Számok legnagyobb eleme: %d helye: %d\n", max, maxidx);
}

void szamok_50ek_kozott() {
	printf("5. feladat: \n");
	int32_t db = 0;
	for (int32_t i = 0; i < 15; i++) {
		if (g_sz[i] <= 50 && g_sz[i] >= -50)
			db++;
	}
	printf("%d db szám van -50 és 50 között.\n", db);
}

int main() {
	setlocale(LC_ALL, "hu_HU");

	g_engine.seed((uint32_t)time(0));

	std::ifstream ifs("adat.txt", std::ios::ate);
	auto meret = file_meret(ifs);
	auto szoveg = new char[meret + 1];
	memset(szoveg, 0, meret + 1);

	ifs.read(szoveg, meret);
	g_parser = new parser(szoveg);
	g_parser->parse();

	adatok_kiir();
	veletlen_szamok_feltolt();
	veletlen_szamok_osszege();
	szamok_max_erteke();
	szamok_50ek_kozott();

	delete[] szoveg;
	delete g_parser;
}