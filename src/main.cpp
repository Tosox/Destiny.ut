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
	if (!gui::generateWindow())
		return EXIT_FAILURE;
	gui::initilize();

	// Get process info
	const std::uintptr_t procID = g_Memory.getProcess("csgo.exe");
	g_Client = g_Memory.getModule(procID, "client.dll");
	g_Engine = g_Memory.getModule(procID, "engine.dll");

	// Handle the latest offsets
	const char* url = (argc > 1 ? argv[1] : "https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json");
	const HRESULT result = URLDownloadToFileA(nullptr, url, "offsets.json", NULL, nullptr);
	offsets::initilize();

	utils::saveDefaultValues();
	
	// Main loop
	while (gui::windowNotClosed())
	{
		g_LocalPlayer = g_Client.getLocalPlayer();

		gui::render();

		features::run();
		
		Sleep(1);
	}

	gui::shutdown();
	if (g_Options.Developer.UnloadOnExit)
		utils::unload();

	return EXIT_SUCCESS;
}