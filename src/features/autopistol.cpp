#include "Features.hpp"
#include "../settings/globals.hpp"

#define KEY_DOWN 0x8000

void features::misc::autopistol()
{
	if (!g_Options.Misc.Helpers.AutoPistol)
		return;

	if (!g_LocalPlayer.exists())
		return;

	if (g_Client.isMouseEnabled())
		return;

	CWeaponEntity weapon = g_LocalPlayer.getActiveWeapon();
	if ((!weapon.exists()) || (!weapon.isPistol()))
		return;

	if (!(GetAsyncKeyState(VK_LBUTTON) & KEY_DOWN))
		return;

	g_Client.doForceAttack();
}