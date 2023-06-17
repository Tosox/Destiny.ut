#include "Features.hpp"
#include "../settings/globals.hpp"

void features::misc::noflash()
{
	if (!g_Options.Misc.Helpers.NoFlash)
		return;

	if (!g_LocalPlayer.exists())
		return;

	if (g_LocalPlayer.getFlashDuration() <= 0.f)
		return;

	g_LocalPlayer.setFlashDuration(0.f);
}
