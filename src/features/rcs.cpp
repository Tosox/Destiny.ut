#include "features.hpp"
#include "../settings/globals.hpp"

void features::legit::rcs()
{
	if (!g_Options.Legit.RCS.Enable)
		return;

	if (!g_Engine.isConnected())
		return;

	if (g_LocalPlayer.getShotsFired() < 3)
		return;

	static Vector2 oldPunch{};

	Vector2 aimPunchAngle = g_LocalPlayer.getAimPunchAngle();
	Vector2 viewAngles = g_Engine.getClientStateViewAngles();

	// Calculate new view angles
	Vector2 newViewAngles = (viewAngles + oldPunch) - (aimPunchAngle * (g_Options.Legit.RCS.Amount / 100) * 2.f);
	newViewAngles.NormalizeAngles();

	g_Engine.setClientStateViewAngles(newViewAngles);

	oldPunch = aimPunchAngle * (g_Options.Legit.RCS.Amount / 100) * 2.f;
}