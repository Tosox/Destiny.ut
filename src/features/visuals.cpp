#include <Windows.h>
#include "Features.hpp"
#include "../settings/globals.hpp"
#include "../sdk/Color.hpp"
#include "../sdk/Structs.hpp"
#include "../sdk/CEntity.hpp"

#define BYTE_MAX 255
#define MAX_PLAYERS 64

struct EntityList_t
{
	CEntity entity[MAX_PLAYERS];
} EntityList;

void HandleBrightness()
{
	// Only change brightness once
	static float tBrightness = NULL;

	if (tBrightness != g_Options.Visuals.World.Brightness)
	{
		int xorBrightness = *(int*)&g_Options.Visuals.World.Brightness ^ g_Options.Default.oModelAmbient;
		g_Engine.SetModelAmbientMin(xorBrightness);
		tBrightness = g_Options.Visuals.World.Brightness;
	}
}

void SetChamsStyle(ClrRender_t& clrRender, const Color color)
{
	clrRender.red = (BYTE)(color.red * BYTE_MAX);
	clrRender.green = (BYTE)(color.green * BYTE_MAX);
	clrRender.blue = (BYTE)(color.blue * BYTE_MAX);
}

void HandleChams(CEntity& entity)
{
	ClrRender_t clrRender{};
	Color clrRenderColor{};

	// Color player depending on team
	if (g_LocalPlayer.GetTeamNum() == entity.GetTeamNum())
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

	entity.SetClrRender(clrRender);
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
	int glowIndex = entity.GetGlowIndex();
	bool isSpotted = entity.IsSpottedBy(g_LocalPlayer);

	GlowStruct_t glowStruct = g_Client.GetGlowStruct(glowIndex);
	Color glowColor{};

	// Color player depending on different flags
	if (g_LocalPlayer.GetTeamNum() == entity.GetTeamNum())
	{
		if (!g_Options.Visuals.Glow.Teammates)
			return;
		glowColor = g_Options.Colors.Glow.Teammates;
	}
	else
	{
		if ((g_Options.Visuals.Glow.Flashed) && (entity.GetFlashDuration() > g_Options.Developer.EntityFlashFlagAmount))
			glowColor = g_Options.Colors.Glow.Flashed;
		else if ((g_Options.Visuals.Glow.Flashed) && (entity.IsDefusing()))
			glowColor = g_Options.Colors.Glow.Defusing;
		else if ((g_Options.Visuals.Glow.Scoped) && (entity.IsScoped()))
			glowColor = g_Options.Colors.Glow.Scoped;
		else if (g_Options.Visuals.Glow.Healthbased)
		{
			int health = entity.GetHealth();
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

	g_Client.SetGlowStruct(glowIndex, glowStruct);
}

void Features::Visuals()
{
	HandleBrightness();

	for (short i = 0; i < (g_Options.Developer.Use32EntityLoop ? 32 : MAX_PLAYERS); ++i)
	{
		EntityList.entity[i].Set(g_Client.GetEntityFromList(i));

		if (EntityList.entity[i].Get() == g_LocalPlayer.Get())
			continue;
		if (!EntityList.entity[i].IsValid())
			continue;

		if (g_Options.Visuals.World.Radar)
			EntityList.entity[i].SetSpotted(true);
		if (g_Options.Visuals.Glow.Enable)
			HandleGlow(EntityList.entity[i]);
		if (g_Options.Visuals.Chams.Enable)
			HandleChams(EntityList.entity[i]);
	}
}