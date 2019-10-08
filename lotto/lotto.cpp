#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

#define INPUT L"lottosz.dat"
#define OUTPUT L"lotto52.ki"
#define VALID(het) (het <= 52 && het >= 1)

using lotto_t = std::array<int32_t, 5>;

namespace het52 {
	lotto_t adat{};
	auto beker() -> void {
		wprintf(L"52. H�t lott�sz�mai (soronk�nt egy): \n");

		//bek�r�s
		for (int i = 0; i < 5; i++)
			std::wcin >> adat[i];

		wprintf(L"Be�rt sz�mok: \n");

		//ki�r�s
		for (int i = 0; i < 5; i++)
			std::wcout << adat[i] << L' ';
		std::wcout << '\n';
	}

	auto rendez() -> void {
		std::sort(adat.begin(), adat.end(), [](const int32_t& a, const int32_t& b) {
			return a < b;
				  });
		wprintf(L"Sz�mok rendezve: ");
		for (int i = 0; i < 5; i++)
			std::wcout << adat[i] << L' ';
		std::wcout << '\n';
	}
}

namespace tobbi_het {
	std::vector<lotto_t> lottosz{}; //t�bbi h�t
	std::wifstream ifs(INPUT);
	auto betolt() -> void {
		std::wstring sor{};
		while (std::getline(ifs, sor)) {
			lotto_t het{};
			for (int i = 0; i < 5; i++)
				ifs >> het[i];
			lottosz.push_back(het);
		}
	}
	auto valasztott() -> void {
		uint32_t het{};

		do {
			wprintf(L"H�t: ");
			std::wcin >> het;
			if (!VALID(het))
				wprintf(L"Kiv�lasztott h�t (%d) hib�s!\n", het);
		} while (!VALID(het));

		wprintf(L"H�t %d sorsz�mai: ", het);

		for (int i = 0; i < 5; i++)
			std::wcout << lottosz[het - 1][i] << L' ';
		std::wcout << L'\n';
	}
	auto kihuzas() -> void {
		bool van[90]{ false };
		bool talalt = false;
		for (auto& het : lottosz)
			for (auto i = 0; i < 5; i++)
				van[het[i]] = true;
		auto i = 0;
		for (int i = 1; i < 90; i++) {
			if (!van[i]) {
				talalt = true;
				break;
			}
		}
		wprintf(L"Van-e olyan sz�m amit egyszer sem h�ztak? %s\n", talalt ? L"Van" : L"Nincs");
	}
	auto paratlan() -> void {
		int32_t paros{};
		int32_t paratlan{};

		for (auto& het : lottosz) {
			for (auto i = 0; i < 5; i++) {
				if (het[i] % 2 == 0)
					paros++;
				else paratlan++;
			}
		}
		wprintf(L"%d-szor/szer volt p�ros, %d-szor/szer volt p�ratlan.\n", paros, paratlan);
	}
	auto hozzafuz() -> void {
		lottosz.push_back(het52::adat);
		std::wofstream ofs(OUTPUT);

		for (auto& het : lottosz) {
			for (auto i = 0; i < 5; i++)
				ofs << het[i] << L' ';
			ofs << L'\n';
		}
	}
	auto mindenszam(uint32_t maxsor) -> void {
		wprintf(L"8. feladat: Az egyes sz�mokat h�nyszor h�zt�k ki 2003-ban?\n");
		int32_t szam[90]{ 0 };
		for (auto& het : lottosz)
			for (auto i = 0; i < 5; i++)
				szam[het[i]]++;
		for (auto i = 1; i < 90; i++) {
			std::wcout << szam[i] << ' ';
			if ((i - 1) % maxsor == (maxsor - 1))
				std::wcout << '\n';
		}
		std::wcout << '\n';
	}
	auto primszamok() -> void {
		wprintf(L"9. feladat: 1-90 k�z�tti pr�msz�mokb�l melyiket nem h�zt�k ki?\n");

		auto primek = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89 };
		std::unordered_map<int, bool> kihuzva{};

		//kezdetben semmi sincs kih�zva
		std::transform(primek.begin(), primek.end(), std::inserter(kihuzva, kihuzva.end()), [](int v) { return std::make_pair(v, false); });
		for (auto& het : lottosz) {
			for (auto i = 0; i < 5; i++) {
				if (kihuzva.count(het[i]) > 0)
					kihuzva[het[i]] = true;
			}
		}
		for (auto& prim : kihuzva) {
			if (!prim.second)
				wprintf(L"'%d' pr�msz�m nem lett kih�zva.\n", prim.first);
		}
	}
}

int main() {
	setlocale(LC_ALL, "hu_HU"); //magyar konzol

	het52::beker();
	het52::rendez();

	tobbi_het::betolt();
	tobbi_het::valasztott();
	tobbi_het::kihuzas();
	tobbi_het::paratlan();
	tobbi_het::hozzafuz();
	tobbi_het::mindenszam(15);
	tobbi_het::primszamok();

	std::cin.get();
	return 0;
}