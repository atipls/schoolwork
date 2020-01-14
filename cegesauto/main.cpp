#include <iostream>
#include <fstream>
#include <unordered_map>
#include "parser.hpp"

parser* g_parser;
long file_meret(std::ifstream& ifs) {
	auto size = ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	ifs.clear();
	return long(size);
}

void utolso_elvitt_auto() {
	printf("2. feladat: \n");
	forgalom* utolso{ nullptr };
	for (auto& fg : g_parser->m_data)
		if (fg.m_ki)
			utolso = &fg;
	if (utolso) {
		printf("\"%s\" (%d) autót vitték el utoljára %d. napon.\n", utolso->m_rsz.c_str(), utolso->m_id, utolso->m_nap);
	} else {
		printf("Nem vittek el egy autót sem.\n");
	}
}
void nap_forgalma() {
	printf("3. feladat: \nNap: ");
	int32_t nap;
	std::cin >> nap;

	printf("Forgalom a(z) %d. napon: \n", nap);

	for (auto& fg : g_parser->m_data)
		if (fg.m_nap == nap)
			printf("%s %s %d %s\n", fg.m_ora.c_str(), fg.m_rsz.c_str(), fg.m_id, fg.m_ki ? "ki" : "be");
}
void autok_honap_vegen() {
	printf("4. feladat: \n");
	std::unordered_map<std::string, bool> ittvan{ false };
	uint32_t nincs_itt{ 0 };
	for (auto& fg : g_parser->m_data)
		ittvan[fg.m_rsz] = !fg.m_ki;
	for (auto& itt : ittvan)
		if (!itt.second)
			nincs_itt++;
	printf("A hónap végén %d autót nem hoztak vissza.\n", nincs_itt);
}

uint32_t megtett_tavolsag_autok(forgalom& p) {
	forgalom* elso{ nullptr };
	forgalom* utolso{ nullptr };
	for (auto& fg : g_parser->m_data) {
		if (fg.m_rsz == p.m_rsz) {
			if (!elso && fg.m_ki)
				elso = &fg;
			if (!fg.m_ki)
				utolso = &fg;
		}
	}
	if (!elso || !utolso)
		return 0;
	return utolso->m_km - elso->m_km;
}
void autok_tavolsaga() {
	printf("5. feladat: \n");
	std::unordered_map<std::string, bool> kiirt{ false };
	for (auto& fg : g_parser->m_data) {
		if (!kiirt[fg.m_rsz]) {
			printf("%s: %dkm.\n", fg.m_rsz.c_str(), megtett_tavolsag_autok(fg));
			kiirt[fg.m_rsz] = true;
		}
	}
}
uint32_t megtett_tavolsag_szemely(forgalom& p) {
	forgalom* elso{ nullptr };
	forgalom* utolso{ nullptr };
	for (auto& fg : g_parser->m_data) {
		if (p.m_id == fg.m_id && p.m_rsz == fg.m_rsz && !elso && fg.m_ki)
			elso = &fg;
	}
	for (auto fg = g_parser->m_data.rbegin(); fg != g_parser->m_data.rend(); fg++)
		if (p.m_id == fg->m_id && p.m_rsz == fg->m_rsz && !fg->m_ki)
			utolso = &*fg;
	if (!elso || !utolso)
		return 0;
	return utolso->m_km - elso->m_km;
}
void leghosszabb_ut() {
	printf("6. feladat: \n");
	struct tavolsag {
		int32_t m_id;
		std::string m_rsz;
		uint32_t m_tav;
	};
	std::vector<tavolsag> tavolsagok{};
	for (auto& fg : g_parser->m_data)
		tavolsagok.push_back(tavolsag{ fg.m_id, fg.m_rsz, megtett_tavolsag_szemely(fg) });
	uint32_t legid{ 0 }, legkm{ 0 };
	for (auto& tv : tavolsagok)
		if (tv.m_tav > legkm) {
			legkm = tv.m_tav;
			legid = tv.m_id;
		}
	printf("Leghosszabb út: %dkm, személy: %d\n", legkm, legid);
}
forgalom* kivitel(const std::string& rsz, const int32_t id) {
	for (auto& fg : g_parser->m_data) {
		if (fg.m_ki && fg.m_rsz == rsz && fg.m_id == id)
			return &fg;
	}
	return nullptr;
}
forgalom* visszahozatal(const std::string& rsz, const int32_t id) {
	for (auto fg = g_parser->m_data.rbegin(); fg != g_parser->m_data.rend(); fg++)
		if (!fg->m_ki && fg->m_rsz == rsz && fg->m_id == id)
			return &*fg;
	return nullptr;
}
void menetlevel() {
	printf("7. feladat: \nRendszám: ");
	std::string rsz;
	std::cin >> rsz;
	std::ofstream ofs(rsz + "_menetlevel.txt");

	for (auto& fg : g_parser->m_data) {
		if (fg.m_rsz == rsz && fg.m_ki) {
			auto kv = kivitel(rsz, fg.m_id);
			auto vz = visszahozatal(rsz, fg.m_id);

			ofs << fg.m_id << "\t";
			if (kv)
				ofs << int(kv->m_nap) << ".\t" << kv->m_ora << "\t" << kv->m_km << "km\t";
			if (vz)
				ofs << int(vz->m_nap) << ".\t" << vz->m_ora << "\t" << vz->m_km << "km\t";
			ofs << "\n";
		}
	}

	ofs.flush();
	ofs.close();
	printf("Menetlevél kész.\n");
}
int main() {
	setlocale(LC_ALL, "hu_HU");

	//1. feladat
	auto ifs = std::ifstream("autok.txt", std::ios::ate);
	auto meret = file_meret(ifs);
	auto tavok = new char[meret + 1];
	memset(tavok, 0, meret + 1);

	ifs.read(tavok, meret);
	ifs.close();

	g_parser = new parser(tavok);
	g_parser->parse();

	utolso_elvitt_auto();
	//nap_forgalma();
	autok_honap_vegen();
	autok_tavolsaga();
	leghosszabb_ut();
	menetlevel();

	std::cin.get();
	return 0;
}
