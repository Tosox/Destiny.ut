#include "features.hpp"
#include "../settings/globals.hpp"

void features::visuals::radar(CEntity& entity)
{
	if (g_Options.Visuals.World.Radar)
		entity.setSpotted(true);
}
