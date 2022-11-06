#include "Features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/Color.hpp"
#include "../sdk/Structs.hpp"
#include "../sdk/CEntity.hpp"



void features::Visuals()
{
	for (short i = 0; i < 64; ++i)
	{
		CEntity entity = g_Client.getEntityFromList(i);

		if (entity == g_LocalPlayer)
			continue;
		if (!entity.isValid())
			continue;

		if (g_Options.Visuals.World.Radar)
			entity.setSpotted(true);
		if (g_Options.Visuals.Glow.Enable)
			HandleGlow(entity);
		if (g_Options.Visuals.Chams.Enable)
			HandleChams(entity);
	}
}