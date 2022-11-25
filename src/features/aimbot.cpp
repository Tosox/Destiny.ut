#include "features.hpp"
#include "../helpers/math.hpp"
#include "../helpers/utils.hpp"
#include "../settings/globals.hpp"

#define KEY_DOWN 0x8000

CEntity getClosestEnemy()
{
	float closest = FLT_MAX;
	int closestIndex = -1;

	for (int i = 0; i < 64; ++i)
	{
		CEntity entity = g_Client.getEntityFromList(i);

		if ((entity == NULL) || (entity == g_LocalPlayer))
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

		Vector2 angles = math::CalculateAngle(g_LocalPlayer.getEyeLocation(), entity.getOrigin());
		Vector2 enemyPos{};
		if (!math::WorldToScreen(entity.getOrigin(), enemyPos))
			continue;

		const SIZE windowSize = utils::getTargetSize();
		const float distance = std::sqrtf(std::powf(enemyPos.x - (windowSize.cx / 2.f), 2) + std::powf(enemyPos.y - (windowSize.cy / 2.f), 2));
		if (distance > g_Options.Legit.Aimbot.Fov)
			continue;

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
	// Calculate new view angles
	Vector2 newAngles = math::CalculateAngle(g_LocalPlayer.getEyeLocation(), target);

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
	if ((weapon == NULL) || (!weapon.isGun()))
		return;

	CEntity entity = getClosestEnemy();
	if (entity == NULL)
		return;

	Vector3 targetPos = entity.getBoneById(g_Options.Legit.Aimbot.TargetBone + 3);
	aimAt(targetPos);
}