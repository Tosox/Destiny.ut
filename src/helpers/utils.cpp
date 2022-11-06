#include <Windows.h>
#include <string>
#include <algorithm>
#include <ctime>
#include "utils.hpp"
#include "../menu.hpp"
#include "../settings/globals.hpp"

// Generate random window name
std::string utils::randomString(std::size_t length)
{
    // Initilize the randomizer
    const std::size_t seed = static_cast<std::size_t>(time(nullptr)) * GetCurrentProcessId();
    srand(seed);

    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const int maxIdx = sizeof(charset) - 1;
        return charset[rand() % maxIdx];
    };

    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);

    return str;
}

// Get CS:GO window handle
bool utils::isTargetRunning()
{
	const HWND csgo = FindWindowA("Valve001", nullptr);
	return csgo != nullptr;
}

// Get default values
void utils::saveDefaultValues()
{
	g_Options.Default.oFov = 90; // TODO: g_LocalPlayer.m_iDefaultFOV() is returning 0
	g_Options.Default.oModelAmbient = g_Engine.getModelAmbientMin();
}

// Restore default values
void utils::unload()
{
	if (g_Options.Developer.UnloadOnExit)
	{
		g_LocalPlayer.setFov(g_Options.Default.oFov);
		g_Engine.setModelAmbientMin(g_Options.Default.oModelAmbient);
	}

	Gui::Shutdown();
}