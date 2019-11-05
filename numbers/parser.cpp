#include "parser.hpp"

std::string parser::line() {
	std::string ret{};
	do {
		ret.append(1 /*cnt*/, get() /*ch*/);
	} while (!end() && cur() != '\n');
	return ret;
}

//csak space-ig megy egy identifier (pl "tortenelem" "matematika" stb..)
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
	m_questions.clear();
	m_source = source;
}

bool parser::parse() {
	while (!end()) {
		auto itm = question_item{};
		itm.m_question = line();
		itm.m_answer = number();
		itm.m_points = number();
		itm.m_theme = identifier();
		m_questions.push_back(itm);
	}
	return true; //nincs hibakeresés
}