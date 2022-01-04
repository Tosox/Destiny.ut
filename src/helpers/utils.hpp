#pragma once

#include <string>

namespace Utils
{
	std::string random_string(int length);
	const wchar_t* GetWideChar(const char* str);

	bool GotTargetWindow();
	void GetDefaultValues();
	void Unload();
}