#include "Features.hpp"
#include "../settings/globals.hpp"

void features::misc::autopistol()
{
	if (!g_Options.Misc.Helpers.AutoPistol)
		return;

	if (g_LocalPlayer == NULL)
		return;

	if (g_Client.isMouseEnabled())
		return;

	CWeaponEntity weapon = g_LocalPlayer.getActiveWeapon();
	if ((weapon == NULL) || (!weapon.isPistol()))
		return;

	if (!GetAsyncKeyState(VK_LBUTTON))
		return;

	g_Client.doForceAttack();
}