#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

//fájl méret 
auto file_meret(std::wifstream& ifs) -> long {
	auto size = ifs.tellg(); //std::ios::ate elvárt.
	ifs.seekg(0, std::ios_base::beg); //wifs elejére
	ifs.clear(); //hibák kihagyása
	return long(size);
}

//cél: szövegfájl készítése
auto create_file() -> void {
	std::wofstream ofs("szoveg.txt");
	wprintf(L"1. feladat: Fájl kiírása. Adja meg a sorokat, lezárás: '#'.\n");
	std::wstring sor{};
	do {
		std::getline(std::wcin, sor); //sor beszedése wide stdin-bõl
		ofs << sor << '\n';
	} while (sor[0] != '#'); // amíg az elsõ karakter nem #
	ofs.flush(); //fájl kiírása
	ofs.close(); //fálj bezárása
}

auto write_file() -> void {
	wprintf(L"2. feladat: Fájl beolvasása. A szoveg.txt fájl kiírása a képernyõre.\n");
	std::wifstream ifs("szoveg.txt", std::ios::badbit | std::ios::ate);
	if (ifs.bad()) {
		wprintf(L"szoveg.txt nem található!\n");
		return;
	}
	//új szöveg
	auto meret = file_meret(ifs);
	auto szoveg = new wchar_t[meret];
	ifs.read(szoveg, meret);

	std::wcout << szoveg << '\n'; //szöveg kiírása wide stdout-ba

	/*soronként
	std::wstring sor{};
	while (std::getline(ifs, sor))
		std::wcout << sor << '\n'; //sor kiírása wide stdout-
	*/

	//memória
	delete[] szoveg;
}

auto main(char argc, char* argv[]) -> int32_t {
	setlocale(LC_ALL, "hu_HU"); //magyar konzol
	create_file();
	write_file();

	std::wcin.get();
	return 0;
}