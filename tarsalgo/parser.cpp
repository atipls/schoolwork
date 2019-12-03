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
	m_ajto_adat.clear();
	m_source = source;
}

bool parser::parse() {
	while (!end()) {
		auto itm = tarsalgo_ajto{};
		itm.m_ora = number();
		itm.m_perc = number();
		itm.m_id = number();
		itm.m_be = identifier() == "be";
		m_ajto_adat.push_back(itm);
	}
	return true; //nincs hibakeresés
}