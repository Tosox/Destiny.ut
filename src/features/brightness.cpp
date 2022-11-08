#include "Features.hpp"
#include "../settings/globals.hpp"

void features::visuals::brightness()
{
	static float prevBrightness = NULL;

	if (prevBrightness != g_Options.Visuals.World.Brightness)
	{
		int brightness = *(int*)&g_Options.Visuals.World.Brightness ^ g_Options.Default.oModelAmbient;
		g_Engine.setModelAmbientMin(brightness);
		prevBrightness = g_Options.Visuals.World.Brightness;
	}
}