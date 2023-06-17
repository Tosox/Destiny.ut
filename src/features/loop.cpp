#include "features.hpp"
#include "../settings/globals.hpp"

void features::visuals::loop()
{
	if (!g_Engine.isConnected())
		return;

	for (int i = 0; i < 64; ++i)
	{
		CEntity entity = g_Client.getEntityFromList(i);

		if ((!entity.exists()) || (entity == g_LocalPlayer))
			continue;

		if ((!entity.isAlive()) || (entity.isDormant()))
			continue;

		radar(entity);
		glow(entity);
		chams(entity);
	}
}
