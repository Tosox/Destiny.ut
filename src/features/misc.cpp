#include <Windows.h>
#include "features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/DefEnums.hpp"

#define FL_ONGROUND (1 << 0)

void Features::Misc()
{
	if (g_Options.Misc.Helpers.Bunnyhop)
	{
		if ((GetAsyncKeyState(VK_SPACE)) && (g_LocalPlayer.GetFlags() & FL_ONGROUND) && (!g_Client.IsMouseEnabled()))
		{
			g_Client.DoForceJump();
		}
	}
	if (g_Options.Misc.Helpers.FakeLag)
	{
		g_Engine.SetSendPackets(false);
		Sleep(8);
		g_Engine.SetSendPackets(true);
	}
	if (g_Options.Misc.Helpers.NoFlash)
	{
		if (g_LocalPlayer.GetFlashDuration() > 0.0f)
		{
			g_LocalPlayer.SetFlashDuration(0.0f);
		}
	}
	if (g_Options.Misc.Helpers.Fov)
	{
		if (!g_LocalPlayer.IsScoped())
		{
			g_LocalPlayer.SetFov(g_Options.Misc.Helpers.Fov);
		}
	}
	if (g_Options.Misc.Helpers.AutoPistol)
	{
		if ((GetAsyncKeyState(VK_LBUTTON)) && (g_LocalPlayer.GetActiveWeapon().IsPistol()) && (!g_Client.IsMouseEnabled()))
		{
			g_Client.DoForceAttack();
		}
	}
}