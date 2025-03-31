#include "dbg/log.hpp"

#include <iostream>

void dbg::log(std::string s) {
	std::cout << s;
}

void dbg::wlog(std::wstring s) {
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] <= 0x7F) {
			std::wcout << s[i];
		}
		else {
			std::wcout << L"?";
		}
	}
}