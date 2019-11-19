#include "parser.hpp"

std::string parser::identifier() {
	std::string ret{};
	do {
		ret.append(1 /*cnt*/, get() /*ch*/);
	} while (!end() && cur() != '\n' && cur() != ' ');
	if (!end()) get();
	return ret;
}

int32_t parser::number() {
	auto num = identifier();
	return atoi(num.c_str());
}

parser::parser(const std::string& source) {
	m_utak.clear();
	m_source = source;
}

bool parser::parse() {
	while (!end()) {
		auto itm = futar_ut{};
		itm.m_nap = number();
		itm.m_fuvar = number();
		itm.m_tavolsag = number();
		m_utak.push_back(itm);
	}
	return true; //nincs hibakeresés
}