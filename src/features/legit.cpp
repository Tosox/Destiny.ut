#include <Windows.h>
#include "Features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/Vector.hpp"
#include "../sdk/CEntity.hpp"
#include "../sdk/DefEnums.hpp"

#define M_PI 3.14159265358979323846f
#define UNITS_TO_METERS 0.0254f
#define RCS_RANGE 2.0f
#define KEY_DOWN 0x8000
#define LOWEST_LOCAL_BONE_INDEX 3

#define MAX_TASER_RANGE 3.5f
#define MAX_KNIFE_RANGE 1.65f
#define OPT_HEALTH_BOUND 55

CEntity& ClosestEnemy()
{
	CEntity entity{};
	float closest = FLT_MAX;
	int closestIndex = -1;

	for (short i = 0; i < 64; ++i)
	{
		entity.Set(g_Client.GetEntityFromList(i));

		// Check entity and flags
		if (g_Client.IsMouseEnabled())
			continue;
		if (entity.Get() == g_LocalPlayer.Get())
			continue;
		if (!entity.IsValid())
			continue;
		if ((entity.GetTeamNum() == g_LocalPlayer.GetTeamNum()) && (!g_Options.Legit.Aimbot.Deathmatch))
			continue;
		if ((!entity.IsSpottedBy(g_LocalPlayer) && (g_Options.Legit.Aimbot.Visible)))
			continue;
		if ((g_LocalPlayer.GetActiveWeapon().IsSniper()) && (g_Options.Legit.Aimbot.Scoped) && (!g_LocalPlayer.IsScoped()))
			continue;
		if ((g_LocalPlayer.GetFlashDuration() > g_Options.Developer.LocalPlayerFlashFlagAmount) && (g_Options.Legit.Aimbot.Flashed))
			continue;
		if ((!g_LocalPlayer.GetFlags()) && (g_Options.Legit.Aimbot.InAir))
			continue;

		float distance = g_LocalPlayer.GetOrigin().to(entity.GetOrigin()).mag();
		if (distance < closest)
		{
			closest = distance;
			closestIndex = i;
		}
	}
	
	// Check if we found a valid target
	if (closestIndex != -1)
		entity.Set(g_Client.GetEntityFromList(closestIndex));
	else
		entity.Set(NULL);

	return entity;
}

void AimAt(Vector3 target)
{
	Vector3 myPos = g_LocalPlayer.GetOrigin() + g_LocalPlayer.GetViewOffset();
	Vector3 deltaVec = myPos.to(target);
	Vector2 newAngles{};

	// Calculate new view angles
	newAngles.x = -asin(deltaVec.z / deltaVec.mag()) * (180.0f / M_PI);
	newAngles.y = atan2(deltaVec.y, deltaVec.x) * (180.0f / M_PI);

	// Add RCS if requested
	if (g_Options.Legit.RCS.Enable)
		newAngles -= g_LocalPlayer.GetAimPunchAngle() * (g_Options.Legit.RCS.Amount / 100) * RCS_RANGE;

	// Prevent snapping onto the target
	newAngles = g_Engine.GetClientState_ViewAngles() + (newAngles - g_Engine.GetClientState_ViewAngles()) / g_Options.Legit.Aimbot.Smoothing;

	newAngles.ClampAngles();

	g_Engine.SetClientState_ViewAngles(newAngles);
}

void Shoot(CEntity &entity)
{
	CWeaponEntity weapon = g_LocalPlayer.GetActiveWeapon();
	float distance = g_LocalPlayer.GetOrigin().to(entity.GetOrigin()).mag() * UNITS_TO_METERS;

	// Decide to shoot if we got the right gun and conditions
	if ((weapon.IsGun()) && (!g_Options.Legit.Triggerbot.ExcludeGuns))
	{
		Sleep(g_Options.Legit.Triggerbot.Delay);
		g_Client.DoForceAttack();
	}
	else if ((weapon.GetItemId() == weapon_taser) && (g_Options.Legit.Triggerbot.AutoTaser))
	{
		if (distance <= MAX_TASER_RANGE)
			g_Client.DoForceAttack();
		
	}
	else if ((weapon.IsKnife()) && (g_Options.Legit.Triggerbot.AutoKnife))
	{
		if (distance <= MAX_KNIFE_RANGE)
			entity.GetHealth() < OPT_HEALTH_BOUND ? g_Client.DoForceAttack2() : g_Client.DoForceAttack();
	}
}

bool CheckTriggerbot(CEntity &entity)
{
	// Check if target is a player
	int crosshairId = g_LocalPlayer.GetCrosshairId();
	if (crosshairId < 1 || crosshairId > 64)
		return false;

	entity.Set(g_Client.GetEntityFromList(crosshairId - 1));

	// Check entity and flags
	if (g_Client.IsMouseEnabled())
		return false;
	if (!entity.IsAlive())
		return false;
	if ((entity.GetTeamNum() == g_LocalPlayer.GetTeamNum()) && (!g_Options.Legit.Triggerbot.Deathmatch))
		return false;
	if ((g_LocalPlayer.GetActiveWeapon().IsSniper()) && (g_Options.Legit.Triggerbot.Scoped) && (!g_LocalPlayer.IsScoped()))
		return false;
	if ((g_LocalPlayer.GetFlashDuration() > g_Options.Developer.LocalPlayerFlashFlagAmount) && (g_Options.Legit.Triggerbot.Flashed))
		return false;
	if ((!g_LocalPlayer.GetFlags()) && (g_Options.Legit.Triggerbot.InAir))
		return false;

	return true;
}

void Features::Legit()
{
	if (g_Options.Legit.RCS.Enable)
	{
		static Vector2 oPunch{};
		Vector2 aimPunchAngle = g_LocalPlayer.GetAimPunchAngle();
		Vector2 nViewAngles{};

		// Check if player shot a specific amount of rounds
		if (g_LocalPlayer.GetShotsFired() >= g_Options.Developer.RcsShotsTrigger)
		{
			Vector2 cViewAngles = g_Engine.GetClientState_ViewAngles();

			// Calculate new view angles
			nViewAngles = (cViewAngles + oPunch) - (aimPunchAngle * (g_Options.Legit.RCS.Amount / 100) * RCS_RANGE);
			nViewAngles.NormalizeAngles();

			g_Engine.SetClientState_ViewAngles(nViewAngles);
		}
		oPunch = aimPunchAngle * (g_Options.Legit.RCS.Amount / 100) * RCS_RANGE;
	}

	if (g_Options.Legit.Triggerbot.Enable)
	{
		// Check if triggerbot can shoot without user input
		bool shoot = g_Options.Legit.Triggerbot.AutoFire;
		if (!g_Options.Legit.Triggerbot.AutoFire)
		{
			shoot = GetAsyncKeyState(VK_MENU) & KEY_DOWN;
		}

		if ((shoot) && (CheckTriggerbot(entity)))
		{
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

		if (g_LocalPlayer.GetActiveWeapon().IsGun())
		{
			CEntity &entity = ClosestEnemy();

			if ((aim) && (entity.IsExisting()))
			{
				Vector3 targetPos = entity.GetBoneById(g_Options.Legit.Aimbot.TargetBone + LOWEST_LOCAL_BONE_INDEX);
				AimAt(targetPos);
			}
		}
	}
}