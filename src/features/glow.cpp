#include "Features.hpp"
#include "../settings/globals.hpp"

void setGlowStructByColor(GlowStruct_t& glowStruct, const Color& color)
{
	glowStruct.red = color.red;
	glowStruct.green = color.green;
	glowStruct.blue = color.blue;
	glowStruct.alpha = g_Options.Developer.GlowAlpha;
	glowStruct.renderWhenOccluded = true;
	glowStruct.renderWhenUnOccluded = false;
	glowStruct.glowStyle = g_Options.Developer.GlowStyle;
}

void features::visuals::glow(CEntity& entity)
{
	if (!g_Options.Visuals.Glow.Enable)
		return;

	const int glowIndex = entity.getGlowIndex();
	const bool isSpotted = entity.isSpottedBy(g_LocalPlayer);
	const int health = entity.getHealth();

	GlowStruct_t glowStruct = g_Client.getGlowStruct(glowIndex);
	Color glowColor{};

	// Color player depending on different flags
	if (g_LocalPlayer.getTeamNum() == entity.getTeamNum())
		glowColor = g_Options.Colors.Glow.Teammates;
	else
	{
		if ((g_Options.Visuals.Glow.Flashed) && (entity.getFlashDuration() > 2.5f))
			glowColor = g_Options.Colors.Glow.Flashed;
		else if ((g_Options.Visuals.Glow.Flashed) && (entity.isDefusing()))
			glowColor = g_Options.Colors.Glow.Defusing;
		else if ((g_Options.Visuals.Glow.Scoped) && (entity.isScoped()))
			glowColor = g_Options.Colors.Glow.Scoped;
		else if (g_Options.Visuals.Glow.Healthbased)
			glowColor = { (health * -0.01f) + 1, health * 0.01f, 0.0f };
		else
		{
			if ((g_Options.Visuals.Glow.Visible) && (!isSpotted))
				return;

			glowColor = isSpotted ? g_Options.Colors.Glow.EnemiesVisible : g_Options.Colors.Glow.Enemies;
		}
	}

	setGlowStructByColor(glowStruct, glowColor);

	g_Client.setGlowStruct(glowIndex, glowStruct);
}
