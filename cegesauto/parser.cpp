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
	m_data.clear();
	m_source = source;
}

bool parser::parse() {
	while (!end()) {
		auto itm = forgalom{};
		itm.m_nap = number();
		itm.m_ora = identifier();
		itm.m_rsz = identifier();
		itm.m_id = number();
		itm.m_km = number();
		itm.m_ki = number() == 0;
		m_data.push_back(itm);
	}
	return true; //nincs hibakeresés
}