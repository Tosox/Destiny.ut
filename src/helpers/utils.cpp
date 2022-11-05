#include <Windows.h>
#include <string>
#include <algorithm>
#include <ctime>
#include <xor/xor.hpp>
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

// Convert between char* and wchar_t*
const wchar_t* utils::toWideChar(const char* str)
{
    const std::size_t strLength = std::strlen(str) + 1;
    std::size_t len{};
    wchar_t* wstr = new wchar_t[strLength];
    mbstowcs_s(&len, wstr, strLength, str, strLength - 1);
    return wstr;
}

// Get CS:GO window handle
bool utils::isTargetRunning()
{
	const HWND csgo = FindWindowW(nullptr, XorStr(L"Counter-Strike: Global Offensive - Direct3D 9"));
	return csgo != nullptr;
}

// Get default values
void utils::saveDefaultValues()
{
	g_Options.Default.oFov = 90; // TODO: g_LocalPlayer.m_iDefaultFOV() is returning 0
	g_Options.Default.oModelAmbient = g_Engine.GetModelAmbientMin();
}

// Restore default values
void utils::unload()
{
	if (g_Options.Developer.UnloadOnExit)
	{
		g_LocalPlayer.SetFov(g_Options.Default.oFov);
		g_Engine.SetModelAmbientMin(g_Options.Default.oModelAmbient);
	}

	Gui::Shutdown();
}