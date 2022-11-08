#include <Windows.h>
#include <string>
#include <algorithm>
#include <ctime>
#include "utils.hpp"
#include "../settings/globals.hpp"

std::string utils::randomString(std::size_t length)
{
	// Initilize the randomizer
	const std::size_t seed = static_cast<std::size_t>(std::time(nullptr)) * GetCurrentProcessId();
	std::srand(seed);

	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const int maxIdx = sizeof(charset) - 1;
		return charset[std::rand() % maxIdx];
	};

	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);

	return str;
}

bool utils::isTargetRunning()
{
	const HWND csgo = FindWindowA("Valve001", nullptr);
	return csgo != nullptr;
}

void utils::saveDefaultValues()
{
	g_Options.Default.oFov = 90; // TODO: g_LocalPlayer.m_iDefaultFOV() is returning 0
	g_Options.Default.oModelAmbient = g_Engine.getModelAmbientMin();
}

void utils::unload()
{
	g_LocalPlayer.setFov(g_Options.Default.oFov);
	g_Engine.setModelAmbientMin(g_Options.Default.oModelAmbient);
}