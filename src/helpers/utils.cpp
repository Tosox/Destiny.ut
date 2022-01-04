#include <Windows.h>
#include <string>
#include <algorithm>
#include <ctime>
#include <xor/xor.hpp>
#include "utils.hpp"
#include "../menu.hpp"
#include "../settings/globals.hpp"

// Generate random window name
std::string Utils::random_string(int length)
{
    // Init the randomizer
    srand((unsigned)time(NULL) * GetCurrentProcessId());

    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const int max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };

    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

// Convert between char* and wchar_t*
const wchar_t* Utils::GetWideChar(const char* str)
{
    size_t len;
    const size_t szStr = strlen(str) + 1;
    wchar_t* wstr = new wchar_t[szStr];
    mbstowcs_s(&len, wstr, szStr,str, szStr - 1);
    return wstr;
}

// Get CS:GO window handle
bool Utils::GotTargetWindow()
{
	HWND csgo = FindWindow(0, (XorStr(L"Counter-Strike: Global Offensive - Direct3D 9")));
	return csgo != NULL;
}

// Get default values
void Utils::GetDefaultValues()
{
	g_Options.Default.oFov = 90; // TODO: g_LocalPlayer.m_iDefaultFOV() is returning 0
	g_Options.Default.oModelAmbient = g_Engine.GetModelAmbientMin();
}

// Restore default values
void Utils::Unload()
{
	if (g_Options.Developer.UnloadOnExit)
	{
		g_LocalPlayer.SetFov(g_Options.Default.oFov);
		g_Engine.SetModelAmbientMin(g_Options.Default.oModelAmbient);
	}

	delete g_Mem;
	Gui::Shutdown();
}