#pragma once
#include <stdint.h>
#include <vector>
#include <string>

struct forgalom {
	uint8_t m_nap;
	std::string m_ora;
	std::string m_rsz;
	int32_t m_id;
	uint32_t m_km;
	bool m_ki;
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
	std::vector<forgalom> m_data{};
	parser(const std::string& source);
	bool parse();
};