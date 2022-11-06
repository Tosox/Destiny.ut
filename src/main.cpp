#include "menu.hpp"
#include "settings/globals.hpp"
#include "helpers/utils.hpp"
#include "helpers/offsets.hpp"
#include "features/features.hpp"

#pragma comment(lib, "urlmon.lib")

int main(int argc, char** argv)
{
	// Init the window
	if (!utils::isTargetRunning())
		return EXIT_FAILURE;
	if (!Glfw::GenerateWindow())
		return EXIT_FAILURE;
	Gui::InitImGui();

	// Get process info
	const std::uintptr_t procID = g_Memory.getProcess("csgo.exe");
	g_Client = g_Memory.getModule(procID, "client.dll");
	g_Engine = g_Memory.getModule(procID, "engine.dll");

	// Handle the latest offsets
	const char* url = argc > 1 ? argv[1] : "https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json";
	URLDownloadToFileA(nullptr, url, "offsets.json", NULL, nullptr);
	offsets::initilize();

	// Prevent crash when activating features in main menu
	while (!g_Engine.isConnected())
	{
		Gui::Render();
		Sleep(50);

		if (!Glfw::WindowNotClosed())
			return EXIT_SUCCESS;
	}

	utils::saveDefaultValues();
	
	// Main loop
	while (Glfw::WindowNotClosed())
	{
		g_LocalPlayer = g_Client.getLocalPlayer();

		Gui::Render();

		features::run();
		
		Sleep(1);
	}

	utils::unload();

	return EXIT_SUCCESS;
}