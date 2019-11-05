#pragma once
#include <string>
#include <vector>

struct question_item {
	std::string m_question;
	int32_t m_answer;
	int32_t m_points;
	std::string m_theme;
};

class parser {
	uint32_t m_pos{ 0 };
	std::string m_source{ 0 };
	inline char get() {
		if (end())
			return '\0';
		return m_source[m_pos++];
	}
	inline char cur() { return m_source[m_pos]; }
	inline bool end() { return m_pos >= m_source.length(); }

	std::string line();
	std::string identifier();
	int32_t number();
public:
	std::vector<question_item> m_questions{};
	parser(const std::string& source);
	bool parse();
};