#pragma once
#include <stdint.h>
#include <vector>
#include <string>

struct tarsalgo_ajto {
	int m_ora;
	int m_perc;
	int m_id; //azonosító
	bool m_be;
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

	std::string identifier();
	int32_t number();
public:
	std::vector<tarsalgo_ajto> m_ajto_adat{};
	parser(const std::string& source);
	bool parse();
};