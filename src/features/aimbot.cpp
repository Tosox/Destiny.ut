#include "features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/Vector.hpp"
#include "../sdk/CEntity.hpp"

#define M_PI 3.14159265358979323846f
#define KEY_DOWN 0x8000

CEntity getClosestEnemy()
{
	CEntity entity{};
	float closest = FLT_MAX;
	int closestIndex = -1;

	for (int i = 0; i < 64; ++i)
	{
		entity = g_Client.getEntityFromList(i);

		if ((!entity) || (entity == g_LocalPlayer))
			continue;

		if ((!entity.isAlive()) || (entity.isDormant()))
			continue;

		if ((entity.getTeamNum() == g_LocalPlayer.getTeamNum()) && (!g_Options.Legit.Aimbot.Deathmatch))
			continue;

		if ((!entity.isSpottedBy(g_LocalPlayer) && (g_Options.Legit.Aimbot.Visible)))
			continue;

		if ((g_LocalPlayer.getActiveWeapon().isSniper()) && (g_Options.Legit.Aimbot.Scoped) && (!g_LocalPlayer.isScoped()))
			continue;

		if ((g_LocalPlayer.getFlashDuration() > 2.5f) && (g_Options.Legit.Aimbot.Flashed))
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

	return (closestIndex != -1 ? g_Client.getEntityFromList(closestIndex) : NULL);
}

void aimAt(Vector3& target)
{
	Vector3 myPos = g_LocalPlayer.getOrigin() + g_LocalPlayer.getViewOffset();
	Vector3 deltaVec = myPos.to(target);
	Vector2 newAngles{};

	// Calculate new view angles
	newAngles.x = -std::asin(deltaVec.z / deltaVec.mag()) * (180.f / M_PI);
	newAngles.y = std::atan2(deltaVec.y, deltaVec.x) * (180.f / M_PI);

	// Add RCS if requested
	if (g_Options.Legit.RCS.Enable)
		newAngles -= g_LocalPlayer.getAimPunchAngle() * ((g_Options.Legit.RCS.Amount / 100) * 2.f);

	// Prevent snapping onto the target
	newAngles = g_Engine.getClientStateViewAngles() + ((newAngles - g_Engine.getClientStateViewAngles()) / g_Options.Legit.Aimbot.Smoothing);

	newAngles.ClampAngles();

	g_Engine.setClientStateViewAngles(newAngles);
}

void features::legit::aimbot()
{
	if (!g_Options.Legit.Aimbot.Enable)
		return;

	if (!g_Engine.isConnected())
		return;

	if (g_Client.isMouseEnabled())
		return;

	const bool shouldAim = (g_Options.Legit.Aimbot.AutoAim ? true : GetAsyncKeyState(VK_LBUTTON) & KEY_DOWN);
	if (!shouldAim)
		return;

	CWeaponEntity weapon = g_LocalPlayer.getActiveWeapon();
	if ((!weapon) || (!weapon.isGun()))
		return;

	CEntity entity = getClosestEnemy();
	if (!entity)
		return;

	Vector3 targetPos = entity.getBoneById(g_Options.Legit.Aimbot.TargetBone + 3);
	aimAt(targetPos);
}