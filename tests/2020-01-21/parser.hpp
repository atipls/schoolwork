#pragma once
#include <stdint.h>
#include <vector>
#include <string>

struct adat {
	int32_t m_id;
	int32_t m_km;
	std::string m_telepules;
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
	std::vector<adat> m_adat{};
	parser(const std::string& source);
	bool parse();
};