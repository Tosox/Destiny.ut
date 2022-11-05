#pragma once

#include <string>

namespace utils
{
	std::string randomString(std::size_t length);
	const wchar_t* toWideChar(const char* str);

	bool isTargetRunning();
	void saveDefaultValues();
	void unload();
}