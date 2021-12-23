#include <Windows.h>
#include "Features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/Vector.hpp"
#include "../sdk/CEntity.hpp"
#include "../sdk/DefEnums.hpp"

#define M_PI 3.14159265358979323846f
#define UNITS_TO_METERS 0.0254f
#define PERCENT_TO_FLOAT 100
#define RCS_RANGE 2
#define KEY_DOWN 0x8000
#define LOWEST_LOCAL_BONE_INDEX 3

#define MAX_PLAYERS 64
#define MAX_TASER_RANGE 3.5f
#define MAX_KNIFE_RANGE 1.65f
#define OPT_HEALTH_BOUND 55

CEntity entity{};

CEntity& ClosestEnemy()
{
	float closest = FLT_MAX;
	int closestIndex = -1;

	static CEntity target{};
	for (short i = 0; i < (g_Options.Developer.Use32EntityLoop ? 32 : MAX_PLAYERS); ++i)
	{
		target.Set(g_Client.GetEntityFromList(i));

		if (target.Get() == g_LocalPlayer.Get())
			continue;
		if (!target.IsValid()) 
			continue;
		if ((target.GetTeamNum() == g_LocalPlayer.GetTeamNum()) && (!g_Options.Legit.Aimbot.Deathmatch))
			continue;
		if ((!target.IsSpottedBy(g_LocalPlayer) && (g_Options.Legit.Aimbot.Visible)))
			continue;
		if ((g_LocalPlayer.GetActiveWeapon().IsSniper()) && (g_Options.Legit.Aimbot.Scoped) && (!g_LocalPlayer.IsScoped()))
			continue;
		if ((g_LocalPlayer.GetFlashDuration() > g_Options.Developer.LocalPlayerFlashFlagAmount) && (g_Options.Legit.Aimbot.Flashed))
			continue;
		if ((!g_LocalPlayer.GetFlags()) && (g_Options.Legit.Aimbot.InAir))
			continue;

		float distance = g_LocalPlayer.GetOrigin().to(target.GetOrigin()).mag();
		if (distance < closest)
		{
			closest = distance;
			closestIndex = i;
		}
	}
	
	if (closestIndex != -1)
		target.Set(g_Client.GetEntityFromList(closestIndex));
	else
		target.Set(NULL);

	return target;
}

void AimAt(Vector3 target)
{
	Vector3 myPos = g_LocalPlayer.GetOrigin() + g_LocalPlayer.GetViewOffset();
	Vector3 deltaVec = myPos.to(target);
	Vector2 newAngles{};

	newAngles.x = -asin(deltaVec.z / deltaVec.mag()) * (180 / M_PI);
	newAngles.y = atan2(deltaVec.y, deltaVec.x) * (180 / M_PI);

	if (g_Options.Legit.Aimbot.RCS)
	{
		newAngles -= g_LocalPlayer.GetAimPunchAngle() * 2.0f;
		newAngles.NormalizeAngles();
	}

	newAngles.ClampAngles();

	Vector2 smoothing = g_Engine.GetClientState_ViewAngles() + (newAngles - g_Engine.GetClientState_ViewAngles()) / g_Options.Legit.Aimbot.Smoothing;

	g_Engine.SetClientState_ViewAngles(smoothing);
}

void Shoot()
{
	CWeaponEntity weapon = g_LocalPlayer.GetActiveWeapon();
	float distance = g_LocalPlayer.GetOrigin().to(entity.GetOrigin()).mag() * UNITS_TO_METERS;

	if ((weapon.IsGun()) && (!g_Options.Legit.Triggerbot.ExcludeGuns))
	{
		Sleep(g_Options.Legit.Triggerbot.Delay);
		g_Client.DoForceAttack();
	}
	else if ((weapon.m_iItemDefinitionIndex() == weapon_taser) && (g_Options.Legit.Triggerbot.AutoTaser))
	{
		if (distance > MAX_TASER_RANGE)
			return;

		g_Client.DoForceAttack();
	}
	else if ((weapon.IsKnife()) && (g_Options.Legit.Triggerbot.AutoKnife))
	{
		if (distance > MAX_KNIFE_RANGE)
			return;

		entity.GetHealth() < OPT_HEALTH_BOUND ? g_Client.DoForceAttack2() : g_Client.DoForceAttack();
	}
}

bool CheckTriggerbot()
{
	int crosshairId = g_LocalPlayer.GetCrosshairId();

	if (crosshairId < 1 || crosshairId > MAX_PLAYERS)
		return false;

	entity.Set(g_Client.GetEntityFromList(crosshairId - 1));

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
	if ((!g_LocalPlayer.GetActiveWeapon().IsGun()) && (g_Options.Legit.Triggerbot.AutoKnife) && (g_Options.Legit.Triggerbot.AutoTaser))
		return false;

	return true;
}

void Features::Legit()
{
	if (g_Options.Legit.RCS.Enable)
	{
		static Vector2 oPunch{};
		Vector2 nViewAngles{};
		Vector2 aimPunchAngle = g_LocalPlayer.GetAimPunchAngle();

		if (g_LocalPlayer.GetShotsFired() >= g_Options.Developer.RcsShotsTrigger)
		{
			Vector2 cViewAngles = g_Engine.GetClientState_ViewAngles();

			nViewAngles = ((cViewAngles + oPunch) - (aimPunchAngle * (g_Options.Legit.RCS.Amount / PERCENT_TO_FLOAT) * RCS_RANGE));
			oPunch = aimPunchAngle * (g_Options.Legit.RCS.Amount / PERCENT_TO_FLOAT) * RCS_RANGE;
			nViewAngles.NormalizeAngles();

			g_Engine.SetClientState_ViewAngles(nViewAngles);
		}
		else
		{
			oPunch.Zero();
		}
	}

	if (g_Options.Legit.Triggerbot.Enable)
	{
		bool shoot = g_Options.Legit.Triggerbot.AutoFire;
		if (!g_Options.Legit.Triggerbot.AutoFire)
		{
			shoot = GetAsyncKeyState(VK_MENU) & KEY_DOWN;
		}

		if ((shoot) && (CheckTriggerbot()))
		{
			Shoot();
		}
	}

	if (g_Options.Legit.Aimbot.Enable)
	{
		bool aim = g_Options.Legit.Aimbot.AutoAim;
		if (!g_Options.Legit.Aimbot.AutoAim)
		{
			aim = GetAsyncKeyState(VK_LBUTTON) & KEY_DOWN;
		}

		if (g_LocalPlayer.GetActiveWeapon().IsGun())
		{
			CEntity target = ClosestEnemy();

			if ((aim) && (target.Get() != NULL))
			{
				AimAt(target.GetBoneById(g_Options.Legit.Aimbot.TargetBone + LOWEST_LOCAL_BONE_INDEX));
			}
		}
	}

	Sleep(1);
}