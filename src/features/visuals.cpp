#include "Features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/Color.hpp"
#include "../sdk/Structs.hpp"
#include "../sdk/CEntity.hpp"

void HandleBrightness()
{
	// Only change brightness once
	static float tBrightness = NULL;

	if (tBrightness != g_Options.Visuals.World.Brightness)
	{
		int xorBrightness = *(int*)&g_Options.Visuals.World.Brightness ^ g_Options.Default.oModelAmbient;
		g_Engine.setModelAmbientMin(xorBrightness);
		tBrightness = g_Options.Visuals.World.Brightness;
	}
}

void SetChamsStyle(ClrRender_t& clrRender, const Color color)
{
	clrRender.red = static_cast<unsigned char>(color.red * 255);
	clrRender.green = static_cast<unsigned char>(color.green * 255);
	clrRender.blue = static_cast<unsigned char>(color.blue * 255);
}

void HandleChams(CEntity& entity)
{
	ClrRender_t clrRender{};
	Color clrRenderColor{};

	// Color player depending on team
	if (g_LocalPlayer.getTeamNum() == entity.getTeamNum())
	{
		if (!g_Options.Visuals.Chams.Teammates)
			return;
		clrRenderColor = g_Options.Colors.Chams.Teammates;
	}
	else
	{
		clrRenderColor = g_Options.Colors.Chams.Enemies;
	}

	SetChamsStyle(clrRender, clrRenderColor);

	entity.setClrRender(clrRender);
}

void SetGlowStyle(GlowStruct_t& glowStruct, const Color color)
{
	glowStruct.red = color.red;
	glowStruct.green = color.green;
	glowStruct.blue = color.blue;
	glowStruct.alpha = g_Options.Developer.GlowAlpha;
	glowStruct.renderWhenOccluded = true;
	glowStruct.renderWhenUnOccluded = false;
	glowStruct.glowStyle = g_Options.Developer.GlowStyle;
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

void Features::Visuals()
{
	HandleBrightness();

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