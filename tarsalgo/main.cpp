#include <iostream>
#include <fstream>
#include <algorithm>
#include "parser.hpp"
#include <unordered_map>
parser* g_parser;

long file_meret(std::ifstream& ifs) {
	auto size = ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	ifs.clear();
	return long(size);
}

int delta_perc(int o1, int p1, int o2, int p2) { return ((o2 - o1) * 60) + (p2 - p1); }

void belep_kilep_azonosito() {
	printf("2. feladat: \n");

	auto be = g_parser->m_ajto_adat.begin();
	auto ki = g_parser->m_ajto_adat.end() - 1;
	while (!be->m_be)
		be++;
	printf("Az elsõ belépõ: %d\n", be->m_id);
	while (ki->m_be)
		ki--;
	printf("Az utolsó kilépõ: %d\n", ki->m_id);
}

void athaladasok() {
	std::ofstream ofs("athaladas.txt");
	std::unordered_map<int, int> asz{}; //áthaladások száma
	for (auto& sz : g_parser->m_ajto_adat)
		asz[sz.m_id]++;

	for (auto& i : asz)
		ofs << i.first << " " << i.second << std::endl;

	ofs.flush();
	ofs.close();
}

void vegen_tartozkodok() {
	printf("4. feladat: \n");
	std::unordered_map<int, bool> tartozkodik{};
	for (auto& sz : g_parser->m_ajto_adat)
		tartozkodik[sz.m_id] = sz.m_be;
	printf("A Nap végén tartózkodók: ");
	for (auto& t : tartozkodik)
		if (t.second) printf("%d ", t.first);
	printf("\n");
}

void legtobben_a_tarsalgoban() {
	printf("5. feladat: \n");
	std::unordered_map<int, int> bent{};
	int total = 0;
	for (auto& sz : g_parser->m_ajto_adat) {
		if (sz.m_be)
			total++;
		else total--;
		bent[sz.m_ora * 100 + sz.m_perc] = total;
	}
	std::vector<std::pair<int, int>> bent_lista(bent.begin(), bent.end());
	std::sort(bent_lista.begin(), bent_lista.end(), [](auto& a, auto& b) { return a.second < b.second; });
	auto& op = bent_lista.front().first;
	printf("%d:%d-kor voltak bent legtöbben a társalgóban.\n", int(op / 100), op % 100);
}

int bekert_id = 0;

void bekert_tartozkodas() {
	printf("7. feladat: \n");
	bool bent{};

	for (auto& sz : g_parser->m_ajto_adat) {
		if (sz.m_id != bekert_id)
			continue;
		printf("%d:%d%c", sz.m_ora, sz.m_perc, sz.m_be ? '-' : '\n');
	}
	printf("\n");
}

void bekert_osszes_perc() {
	printf("8. feladat: \n");
	int total{};
	int ora{};
	int perc{};
	bool bent{};

	for (auto& sz : g_parser->m_ajto_adat) {
		if (sz.m_id != bekert_id)
			continue;
		bent = sz.m_be;
		if (bent) {
			ora = sz.m_ora;
			perc = sz.m_perc;
		} else {
			total += delta_perc(ora, perc, sz.m_ora, sz.m_perc);
			bent = false;
		}
	}
	printf("A(z). %d. személy összesen %d percet volt bent, a megfigyelés végén %s.\n", bekert_id, total, bent ? "bent volt a társalgóban" : "nem volt bent a társalgóban");
}

int main() {
	setlocale(LC_ALL, "hu_HU");

	//1. feladat
	auto ifs = std::ifstream("ajto.txt", std::ios::ate);
	auto meret = file_meret(ifs);
	auto tavok = new char[meret + 1];
	memset(tavok, 0, meret + 1);

	ifs.read(tavok, meret);
	ifs.close();

	g_parser = new parser(tavok);
	g_parser->parse();

	belep_kilep_azonosito();
	athaladasok();
	vegen_tartozkodok();
	legtobben_a_tarsalgoban();

	printf("6. feladat: \n");
	printf("Adja meg a személy azonosítóját: ");
	std::cin >> bekert_id;
	bekert_tartozkodas();
	bekert_osszes_perc();

	delete g_parser;
	std::cin.get();
	return 0;
}