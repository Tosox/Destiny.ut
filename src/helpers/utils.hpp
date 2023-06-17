#pragma once

#include <string>

namespace utils
{
	std::string randomString(std::size_t length);

	SIZE getTargetSize();

	bool isTargetRunning();

	void saveDefaultValues();
	void unload();
}
