#include "Features.hpp"
#include "../settings/globals.hpp"

ClrRender_t getClrRenderByColor(const Color color)
{
	ClrRender_t clrRender{};
	clrRender.red = static_cast<unsigned char>(color.red * 255);
	clrRender.green = static_cast<unsigned char>(color.green * 255);
	clrRender.blue = static_cast<unsigned char>(color.blue * 255);
	return clrRender;
}

void features::visuals::chams(CEntity& entity)
{
	if (!g_Options.Visuals.Chams.Enable)
		return;

	const Color clrRenderColor = (g_LocalPlayer.getTeamNum() == entity.getTeamNum() ? g_Options.Colors.Chams.Teammates : g_Options.Colors.Chams.Enemies);
	ClrRender_t clrRender = getClrRenderByColor(clrRenderColor);

	entity.setClrRender(clrRender);
}