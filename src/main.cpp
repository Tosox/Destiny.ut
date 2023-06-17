#include <format>
#include "menu.hpp"
#include "settings/globals.hpp"
#include "helpers/utils.hpp"
#include "helpers/offsets.hpp"
#include "features/features.hpp"

#pragma comment(lib, "urlmon.lib")

int main(int argc, char** argv)
{
	const bool isTargetRunning = utils::isTargetRunning();
	if (!isTargetRunning)
	{
		MessageBox(NULL, "CS:GO is not running yet", "Error", MB_ICONERROR);
		exit(1);
	}

	const bool isWindowGenerated = gui::generateWindow();
	if (!isWindowGenerated)
	{
		MessageBox(NULL, "Could not generate process window", "Error", MB_ICONERROR);
		exit(1);
	}

	gui::initilize();

	// Handle the latest offsets
	const char* url = (argc > 1 ? argv[1] : "https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.json");
	HRESULT result = URLDownloadToFileA(nullptr, url, "offsets.json", 0, nullptr);
	if (result != S_OK)
	{
		// console::throwWarning("[!] Could not update offsets. Falling back to blazedumper's offsets");

		url = "https://raw.githubusercontent.com/Akandesh/blazedumper/master/csgo.json";
		result = URLDownloadToFileA(nullptr, url, "offsets.json", 0, nullptr);
		// if (result != S_OK)
			// console::throwWarning("[!] Could not update offsets. Falling back to old offsets file");
	}

	offsets::initialize();

	// Get process info
	const std::uintptr_t procID = g_Memory.getProcess("csgo.exe");
	g_Client = g_Memory.getModule(procID, "client.dll");
	g_Engine = g_Memory.getModule(procID, "engine.dll");

	utils::saveDefaultValues();
	
	// Main loop
	while (gui::windowNotClosed())
	{
		g_LocalPlayer = g_Client.getLocalPlayer();

		gui::render();

		features::run();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	gui::shutdown();
	utils::unload();

	return EXIT_SUCCESS;
}
