#include "Features.hpp"
#include "../settings/globals.hpp"

void features::misc::fov()
{
	if (!g_Options.Misc.Helpers.Fov)
		return;

	if (!g_LocalPlayer)
		return;

	if (g_LocalPlayer.isScoped())
		return;

	g_LocalPlayer.setFov(g_Options.Misc.Helpers.Fov);
}
