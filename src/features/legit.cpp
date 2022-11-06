#include "Features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/Vector.hpp"
#include "../sdk/CEntity.hpp"
#include "../sdk/DefEnums.hpp"

#define M_PI 3.14159265358979323846f
#define KEY_DOWN 0x8000
#define LOWEST_LOCAL_BONE_INDEX 3

CEntity ClosestEnemy()
{
	CEntity entity{};
	float closest = FLT_MAX;
	int closestIndex = -1;

	for (short i = 0; i < 64; ++i)
	{
		entity = g_Client.getEntityFromList(i);

		// Check entity and flags
		if (g_Client.isMouseEnabled())
			continue;
		if (entity == g_LocalPlayer)
			continue;
		if (!entity.isValid())
			continue;
		if ((entity.getTeamNum() == g_LocalPlayer.getTeamNum()) && (!g_Options.Legit.Aimbot.Deathmatch))
			continue;
		if ((!entity.isSpottedBy(g_LocalPlayer) && (g_Options.Legit.Aimbot.Visible)))
			continue;
		if ((g_LocalPlayer.getActiveWeapon().isSniper()) && (g_Options.Legit.Aimbot.Scoped) && (!g_LocalPlayer.isScoped()))
			continue;
		if ((g_LocalPlayer.getFlashDuration() > g_Options.Developer.LocalPlayerFlashFlagAmount) && (g_Options.Legit.Aimbot.Flashed))
			continue;
		if ((!g_LocalPlayer.getFlags()) && (g_Options.Legit.Aimbot.InAir))
			continue;

		const float distance = g_LocalPlayer.getOrigin().to(entity.getOrigin()).mag();
		if (distance < closest)
		{
			closest = distance;
			closestIndex = i;
		}
	}
	
	// Check if we found a valid target
	if (closestIndex != -1)
		entity = g_Client.getEntityFromList(closestIndex);
	else
		entity = NULL;

	return entity;
}

void AimAt(Vector3 target)
{
	Vector3 myPos = g_LocalPlayer.getOrigin() + g_LocalPlayer.getViewOffset();
	Vector3 deltaVec = myPos.to(target);
	Vector2 newAngles{};

	// Calculate new view angles
	newAngles.x = -asin(deltaVec.z / deltaVec.mag()) * (180.0f / M_PI);
	newAngles.y = atan2(deltaVec.y, deltaVec.x) * (180.0f / M_PI);

	// Add RCS if requested
	if (g_Options.Legit.RCS.Enable)
		newAngles -= g_LocalPlayer.getAimPunchAngle() * (g_Options.Legit.RCS.Amount / 100) * 2.f;

	// Prevent snapping onto the target
	newAngles = g_Engine.getClientStateViewAngles() + (newAngles - g_Engine.getClientStateViewAngles()) / g_Options.Legit.Aimbot.Smoothing;

	newAngles.ClampAngles();

	g_Engine.setClientStateViewAngles(newAngles);
}

void Shoot(CEntity &entity)
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

CEntity CheckTriggerbot()
{
	CEntity entity{};

	// Check if target is a player
	const int crosshairId = g_LocalPlayer.getCrosshairId();
	if (crosshairId < 1 || crosshairId > 64)
		return {};

	entity = g_Client.getEntityFromList(crosshairId - 1);

	// Check entity and flags
	if (g_Client.isMouseEnabled())
		return {};
	if (!entity.isAlive())
		return {};
	if ((entity.getTeamNum() == g_LocalPlayer.getTeamNum()) && (!g_Options.Legit.Triggerbot.Deathmatch))
		return {};
	if ((g_LocalPlayer.getActiveWeapon().isSniper()) && (g_Options.Legit.Triggerbot.Scoped) && (!g_LocalPlayer.isScoped()))
		return {};
	if ((g_LocalPlayer.getFlashDuration() > g_Options.Developer.LocalPlayerFlashFlagAmount) && (g_Options.Legit.Triggerbot.Flashed))
		return {};
	if ((!g_LocalPlayer.getFlags()) && (g_Options.Legit.Triggerbot.InAir))
		return {};

	return entity;
}

void features::Legit()
{
	if (g_Options.Legit.RCS.Enable)
	{
		static Vector2 oPunch{};
		Vector2 aimPunchAngle = g_LocalPlayer.getAimPunchAngle();
		Vector2 nViewAngles{};

		// Check if player shot a specific amount of rounds
		if (g_LocalPlayer.getShotsFired() >= g_Options.Developer.RcsShotsTrigger)
		{
			Vector2 cViewAngles = g_Engine.getClientStateViewAngles();

			// Calculate new view angles
			nViewAngles = (cViewAngles + oPunch) - (aimPunchAngle * (g_Options.Legit.RCS.Amount / 100) * 2.f);
			nViewAngles.NormalizeAngles();

			g_Engine.setClientStateViewAngles(nViewAngles);
		}
		oPunch = aimPunchAngle * (g_Options.Legit.RCS.Amount / 100) * 2.f;
	}

	if (g_Options.Legit.Triggerbot.Enable)
	{
		// Check if triggerbot can shoot without user input
		bool shoot = g_Options.Legit.Triggerbot.AutoFire;
		if (!g_Options.Legit.Triggerbot.AutoFire)
		{
			shoot = GetAsyncKeyState(VK_MENU) & KEY_DOWN;
		}

		if ((shoot))
		{
			CEntity entity = CheckTriggerbot();
			Shoot(entity);
		}
	}

	if (g_Options.Legit.Aimbot.Enable)
	{
		// Check if aimbot can shoot without user input
		bool aim = g_Options.Legit.Aimbot.AutoAim;
		if (!g_Options.Legit.Aimbot.AutoAim)
		{
			aim = GetAsyncKeyState(VK_LBUTTON) & KEY_DOWN;
		}

		if (g_LocalPlayer.getActiveWeapon().isGun())
		{
			CEntity &entity = ClosestEnemy();

			if ((aim) && (!!entity))
			{
				Vector3 targetPos = entity.getBoneById(g_Options.Legit.Aimbot.TargetBone + LOWEST_LOCAL_BONE_INDEX);
				AimAt(targetPos);
			}
		}
	}
}