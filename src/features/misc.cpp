#include "features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/DefEnums.hpp"


void Features::Misc()
{
	if (g_Options.Misc.Helpers.Bunnyhop)
	{
		if ((GetAsyncKeyState(VK_SPACE)) && (g_LocalPlayer.getFlags() & (1 << 0)) && (!g_Client.isMouseEnabled()))
		{
			g_Client.doForceJump();
		}
	}
	if (g_Options.Misc.Helpers.NoFlash)
	{
		if (g_LocalPlayer.getFlashDuration() > 0.0f)
		{
			g_LocalPlayer.setFlashDuration(0.0f);
		}
	}
	if (g_Options.Misc.Helpers.Fov)
	{
		if (!g_LocalPlayer.isScoped())
		{
			g_LocalPlayer.setFov(g_Options.Misc.Helpers.Fov);
		}
	}
	if (g_Options.Misc.Helpers.AutoPistol)
	{
		if ((GetAsyncKeyState(VK_LBUTTON)) && (g_LocalPlayer.getActiveWeapon().isPistol()) && (!g_Client.isMouseEnabled()))
		{
			g_Client.doForceAttack();
		}
	}
}