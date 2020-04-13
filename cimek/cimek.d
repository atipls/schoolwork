module main;

import std.stdio, std.algorithm, std.algorithm.searching, std.file, 
	std.array, std.string, std.conv, core.stdc.locale, std.range : enumerate;

version(Windows) {
	extern(Windows) int SetConsoleOutputCP(uint);
}

private string shortenFull(string ip) {
	auto sp = ip.split(':');
	int[] sz = new int[8];

	for (int i = 0; i < 8; i++) {
		if (sp[i] == "0")
			for (int j = i; sp[j] == "0"; j++, sz[i]++){}
	}
	const auto max = sz.enumerate.maxElement!"a.value"();
	if (max.value <= 1)
		return "Nem rövidíthető tovább!";
	const auto mi = max.index;
	return sp[0..mi].join(":") ~ "::" ~ sp[mi+sz[mi]..8].join(":");
}

void main() {
	// Karakter kódolás windows alatt 
	// 
	version (Windows) {
		SetConsoleOutputCP(65001);
	}

	auto data = readText("ip.txt").chop.split("\r\n");
	int[4] db;

	foreach (string ip; data) {
		db[ip[0..9] == "2001:0db8" ? 0 :
		   ip[0..7] == "2001:0e" ? 1 :
			ip[0..2] == "fc" || ip[0..2] == "fd" ? 2 : 3]++;
	}

	"2. feladat:\nAz állományban %d darab adatsor van.\n".writefln(data.length);
	"3. feladat:\nA legalacsonyabb tárolt IP-cím:\n%s\n".writefln(data.dup.sort[0]);
	"4. feladat:".writeln;
	"Dokumentációs cím: %d".writefln(db[0]);
	"Globális egyedi cím: %d".writefln(db[1]);
	"Helyi egyedi cím: %d\n".writefln(db[2]);

	auto sok = File("sok.txt", "w");
	for(int i = 0; i < data.length; i++) {
		if (data[i].count('0') > 18)
			sok.writefln("%d %s", i + 1, data[i]);
	}
	sok.close();

	"6. feladat:\nKérek egy sorszámot: ".write;
	auto ip = data[to!int(readln().chop()) - 1];
	string sh = "";
	foreach(string gr; ip.split(':'))
		sh ~= (gr == "0000" ? "0" : gr.chompPrefix("0")) ~ ":";
	sh = sh.chomp(":");

	"%s\n%s\n".writefln(ip, sh);

	"7. feladat:\n%s".writefln(sh.shortenFull);
}
