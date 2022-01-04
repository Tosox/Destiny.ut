#include <Windows.h>
#include <xor/xor.hpp>
#include <MemMan/MemMan.hpp>
#include <iostream>
#include "menu.hpp"
#include "settings/globals.hpp"
#include "helpers/utils.hpp"
#include "helpers/offsets.hpp"
#include "features/features.hpp"

#pragma comment(lib, "urlmon.lib")

#define PROCESSEXE L"csgo.exe"
#define CLIENTDLL L"client.dll"
#define ENGINEDLL L"engine.dll"

MemMan* g_Mem = new MemMan();
Options g_Options;
CClient g_Client;
CEngine g_Engine;
CBaseEntity g_LocalPlayer;

int main(int argc, char** argv)
{
	// Init the window
	if (!Utils::GotTargetWindow())
		return EXIT_FAILURE;
	if (!Glfw::GenerateWindow())
		return EXIT_FAILURE;
	Gui::InitImGui();

	// Get process info
	int procID = g_Mem->getProcess(PROCESSEXE);
	g_Client.Set(g_Mem->getModule(procID, CLIENTDLL));
	g_Engine.Set(g_Mem->getModule(procID, ENGINEDLL));

	// Handle the latest offsets
	URLDownloadToFile(NULL, XorStr(argc > 1 ? Utils::GetWideChar(argv[1]) : L"https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json"), XorStr(L"offsets.json"), 0, NULL);
	offsets::InitOffsets();

	// Prevent crash when activating features in main menu
	while (!g_Engine.IsConnected())
	{
		Gui::Render();
		Sleep(50);

		if (!Glfw::WindowNotClosed())
			return EXIT_SUCCESS;
	}

	Utils::GetDefaultValues();
	
	// Main loop
	while (Glfw::WindowNotClosed())
	{
		g_LocalPlayer.Set(g_Client.GetLocalPlayer());

		Gui::Render();

		Features::Legit();
		Features::Visuals();
		Features::Misc();
		
		Sleep(1);
	}

	// Exit
	Utils::Unload();
	return EXIT_SUCCESS;
}