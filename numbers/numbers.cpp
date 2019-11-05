#include <iostream>
#include <fstream>
#include <unordered_map>
#include <random>
#include "parser.hpp"
#include <time.h>

parser* g_parser = nullptr;

long file_meret(std::ifstream& ifs) {
	auto size = ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	ifs.clear();
	return long(size);
}

void matek_feladat_pontok() {
	uint32_t mcnt{ 1 }; //ennyi matek feladat van
	//ennyi pontot ér ennyi feladat
	//[ "1" => "10", "2" => "6" ]
	std::unordered_map<uint32_t, uint32_t> pontsz{};

	for (auto& question : g_parser->m_questions) {
		if (question.m_theme == "matematika") {
			mcnt++;
			pontsz[question.m_points]++;
		}
	}

	printf("A fájlban %d matematika feladat van", mcnt);
	for (auto& pont : pontsz) {
		printf(", ");
		printf("%d pontot ér %d feladat", pont.first, pont.second);
	}
	printf(".\n");
}

void feladat_szamertek_terjedelem() {
	int32_t min{ INT_MAX }, max{ 0 };

	for (auto& question : g_parser->m_questions) {
		auto n = question.m_answer;
		if (n < min)
			min = n;
		else if (n > max)
			max = n;
	}

	printf("4. feladat: A számok %d-tól/tõl %d-ig terjednek.\n", min, max);
}

void temakorok() {
	std::unordered_map<std::string, bool> kiirt{};
	printf("5. feladat: Témakörök: ");
	for (auto& question : g_parser->m_questions) {
		auto temakor = question.m_theme;
		if (!kiirt[temakor]) {
			printf("%s ", temakor.c_str());
			kiirt[temakor] = true;
		}
	}
	printf("\n");
}

void temakor_kerdes() {
	printf("Milyen témakörbõl szeretne kérdést kapni? ");
	std::string tema;
	std::cin >> tema;

	std::vector<question_item> kerdesek{};
	for (auto& question : g_parser->m_questions)
		if (question.m_theme == tema)
			kerdesek.push_back(question);

	std::uniform_int_distribution<> distr(0, kerdesek.size() - 1);
	std::mt19937 random(uint32_t(time(nullptr)));

	//véletlen kérdés a témakörbõl
	auto kerdes = kerdesek[distr(random)];
	printf("%s (%d) ", kerdes.m_question.c_str(), kerdes.m_answer);

	std::string valasz;
	std::cin >> valasz;

	auto helyes = atoi(valasz.c_str()) == kerdes.m_answer;
	printf("A válasz %d pontot ér.\n", helyes ? kerdes.m_points : 0);
	if (!helyes)
		printf("A helyes válasz: %d\n", kerdes.m_answer);
}

void feladatsor_generalas() {
	std::ofstream ofs("tesztfel.txt");

	std::uniform_int_distribution<> distr(0, g_parser->m_questions.size() - 1);
	std::mt19937 random(uint32_t(time(nullptr)));
	std::unordered_map<std::string, bool> volt{};

	uint32_t osszpontszam{0};
	for (int i = 0; i < 10; i++) {
		question_item* kerdes;
		do {
			kerdes = &g_parser->m_questions[distr(random)];
		} while (volt[kerdes->m_question]);
		volt[kerdes->m_question] = true;
		ofs << kerdes->m_points << " " << kerdes->m_answer << " " << kerdes->m_question << "\n";
		osszpontszam += kerdes->m_points;
	}
	ofs << "A feladatsorra összesen " << osszpontszam << " pont adható.\n";
	ofs.flush();
	ofs.close();
}

int main() {
	setlocale(LC_ALL, "hu_HU"); //magyar konzol

	std::ifstream ifs("felszam.txt", std::ios::ate);
	auto meret = file_meret(ifs);
	auto szoveg = new char[meret + 1];
	memset(szoveg, 0, meret + 1);

	ifs.read(szoveg, meret);
	ifs.close();

	g_parser = new parser(szoveg);
	g_parser->parse();

	printf("2. feladat: %d feladat van a fájlban.\n", g_parser->m_questions.size());

	matek_feladat_pontok();
	feladat_szamertek_terjedelem();
	temakorok();
	temakor_kerdes();
	feladatsor_generalas();

	delete[] szoveg;
	delete g_parser;

	std::cin.get();
	return 0;
}