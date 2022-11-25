#include "Features.hpp"
#include "../settings/globals.hpp"

#define KEY_DOWN 0xFFFF

void features::misc::thirdperson()
{
	if (g_Options.Misc.Helpers.Thirdperson)
		g_LocalPlayer.setObserverMode(GetAsyncKeyState(VK_MBUTTON) & KEY_DOWN ? 1 : 0);
}