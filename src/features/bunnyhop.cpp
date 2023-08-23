#include "Features.hpp"
#include "../settings/globals.hpp"

#define FL_ON_GROUND (1 << 0)

void features::misc::bunnyhop()
{
	if (!g_Options.Misc.Helpers.Bunnyhop)
		return;

	if (!g_LocalPlayer.exists())
		return;

	if (g_Client.isMouseEnabled())
		return;

	if (!(g_LocalPlayer.getFlags() & FL_ON_GROUND))
		return;

	if (!GetAsyncKeyState(VK_SPACE))
		return;

	g_Client.doForceJump();
}
