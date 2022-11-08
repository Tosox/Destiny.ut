#include "features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/CEntity.hpp"
#include "../sdk/DefEnums.hpp"

#define KEY_DOWN 0x8000

CEntity getPlayerInCrosshair()
{
	CEntity entity{};

	// Check if target is a player
	const int crosshairId = g_LocalPlayer.getCrosshairId();
	if (crosshairId < 1 || crosshairId > 64)
		return NULL;

	return g_Client.getEntityFromList(crosshairId - 1);
}

void Shoot(CEntity& entity)
{
	CWeaponEntity weapon = g_LocalPlayer.getActiveWeapon();
	const float distance = g_LocalPlayer.getOrigin().to(entity.getOrigin()).mag();

	// Decide to shoot if we got the right gun and conditions
	if ((weapon.isGun()) && (!g_Options.Legit.Triggerbot.ExcludeGuns))
	{
		Sleep(g_Options.Legit.Triggerbot.Delay);
		g_Client.doForceAttack();
	}
	else if ((weapon.getItemId() == weapon_taser) && (g_Options.Legit.Triggerbot.AutoTaser))
	{
		if (distance <= 137.5f)
			g_Client.doForceAttack();

	}
	else if ((weapon.isKnife()) && (g_Options.Legit.Triggerbot.AutoKnife))
	{
		if (distance <= 65.f)
			entity.getHealth() < 55 ? g_Client.doForceAttack2() : g_Client.doForceAttack();
	}
}

void features::legit::triggerbot()
{
	if (!g_Options.Legit.Triggerbot.Enable)
		return;

	if (!g_Engine.isConnected())
		return;

	if (g_Client.isMouseEnabled())
		return;

	const bool canShoot = (g_Options.Legit.Triggerbot.AutoFire ? true : GetAsyncKeyState(VK_MENU) & KEY_DOWN);
	if (!canShoot)
		return;

	CEntity entity = getPlayerInCrosshair();
	if (!entity)
		return;

	if (!entity.isAlive())
		return;

	if ((entity.getTeamNum() == g_LocalPlayer.getTeamNum()) && (!g_Options.Legit.Triggerbot.Deathmatch))
		return;

	if ((g_LocalPlayer.getActiveWeapon().isSniper()) && (g_Options.Legit.Triggerbot.Scoped) && (!g_LocalPlayer.isScoped()))
		return;

	if ((g_LocalPlayer.getFlashDuration() > g_Options.Developer.LocalPlayerFlashFlagAmount) && (g_Options.Legit.Triggerbot.Flashed))
		return;

	if ((!g_LocalPlayer.getFlags()) && (g_Options.Legit.Triggerbot.InAir))
		return;

	Shoot(entity);
}