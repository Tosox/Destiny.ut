#include "Features.hpp"
#include "../settings/globals.hpp"

void features::misc::bunnyhop()
{
	if (!g_Options.Misc.Helpers.Bunnyhop)
		return;
	if (g_Client.isMouseEnabled())
		return;
	if (!(g_LocalPlayer.getFlags() & (1 << 0)))
		return;
	if (!GetAsyncKeyState(VK_SPACE))
		return;

	g_Client.doForceJump();
}
