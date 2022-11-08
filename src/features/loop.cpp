#include "features.hpp"
#include "../settings/globals.hpp"

void features::visuals::loop()
{
	if (!g_Options.Visuals.EnableGlobal)
		return;

	if (!g_Engine.isConnected())
		return;

	for (int i = 0; i < 64; ++i)
	{
		CEntity entity = g_Client.getEntityFromList(i);

		if (!entity)
			return;

		if (entity.isDormant())
			return;

		if (!entity.isAlive())
			return;

		if (entity == g_LocalPlayer)
			return;

		radar(entity);
		glow(entity);
		chams(entity);
	}
}
