#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

//f�jl m�ret 
auto file_meret(std::wifstream& ifs) -> long {
	auto size = ifs.tellg(); //std::ios::ate elv�rt.
	ifs.seekg(0, std::ios_base::beg); //wifs elej�re
	ifs.clear(); //hib�k kihagy�sa
	return long(size);
}

//c�l: sz�vegf�jl k�sz�t�se
auto create_file() -> void {
	std::wofstream ofs("szoveg.txt");
	wprintf(L"1. feladat: F�jl ki�r�sa. Adja meg a sorokat, lez�r�s: '#'.\n");
	std::wstring sor{};
	do {
		std::getline(std::wcin, sor); //sor beszed�se wide stdin-b�l
		ofs << sor << '\n';
	} while (sor[0] != '#'); // am�g az els� karakter nem #
	ofs.flush(); //f�jl ki�r�sa
	ofs.close(); //f�lj bez�r�sa
}

auto write_file() -> void {
	wprintf(L"2. feladat: F�jl beolvas�sa. A szoveg.txt f�jl ki�r�sa a k�perny�re.\n");
	std::wifstream ifs("szoveg.txt", std::ios::badbit | std::ios::ate);
	if (ifs.bad()) {
		wprintf(L"szoveg.txt nem tal�lhat�!\n");
		return;
	}
	//�j sz�veg
	auto meret = file_meret(ifs);
	auto szoveg = new wchar_t[meret];
	ifs.read(szoveg, meret);

	std::wcout << szoveg << '\n'; //sz�veg ki�r�sa wide stdout-ba

	/*soronk�nt
	std::wstring sor{};
	while (std::getline(ifs, sor))
		std::wcout << sor << '\n'; //sor ki�r�sa wide stdout-
	*/

	//mem�ria
	delete[] szoveg;
}

auto main(char argc, char* argv[]) -> int32_t {
	setlocale(LC_ALL, "hu_HU"); //magyar konzol
	create_file();
	write_file();

	std::wcin.get();
	return 0;
}