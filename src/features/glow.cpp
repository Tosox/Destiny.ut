#include "Features.hpp"
#include "../settings/globals.hpp"

GlowStruct_t& getGlowStructByColor(const Color color)
{
	GlowStruct_t glowStruct{};
	glowStruct.red = color.red;
	glowStruct.green = color.green;
	glowStruct.blue = color.blue;
	glowStruct.alpha = g_Options.Developer.GlowAlpha;
	glowStruct.renderWhenOccluded = true;
	glowStruct.renderWhenUnOccluded = false;
	glowStruct.glowStyle = g_Options.Developer.GlowStyle;
	return glowStruct;
}

void HandleGlow(CEntity& entity)
{
	int glowIndex = entity.getGlowIndex();
	bool isSpotted = entity.isSpottedBy(g_LocalPlayer);

	GlowStruct_t glowStruct = g_Client.getGlowStruct(glowIndex);
	Color glowColor{};

	// Color player depending on different flags
	if (g_LocalPlayer.getTeamNum() == entity.getTeamNum())
	{
		if (!g_Options.Visuals.Glow.Teammates)
			return;
		glowColor = g_Options.Colors.Glow.Teammates;
	}
	else
	{
		if ((g_Options.Visuals.Glow.Flashed) && (entity.getFlashDuration() > g_Options.Developer.EntityFlashFlagAmount))
			glowColor = g_Options.Colors.Glow.Flashed;
		else if ((g_Options.Visuals.Glow.Flashed) && (entity.isDefusing()))
			glowColor = g_Options.Colors.Glow.Defusing;
		else if ((g_Options.Visuals.Glow.Scoped) && (entity.isScoped()))
			glowColor = g_Options.Colors.Glow.Scoped;
		else if (g_Options.Visuals.Glow.Healthbased)
		{
			const int health = entity.getHealth();
			glowColor = { health * -0.01f + 1, health * 0.01f, 0.0f };
		}
		else
		{
			if (isSpotted)
				glowColor = g_Options.Colors.Glow.EnemiesVisible;
			else
				glowColor = g_Options.Colors.Glow.Enemies;
			if ((g_Options.Visuals.Glow.Visible) && (!isSpotted))
				return;
		}
	}

	SetGlowStyle(glowStruct, glowColor);

	g_Client.setGlowStruct(glowIndex, glowStruct);
}
