#pragma once

#include <string>
#include <sstream>
#include <iomanip>

namespace utils
{
	std::string randomString(std::size_t length);

	bool isTargetRunning();
	void saveDefaultValues();
	void unload();
}