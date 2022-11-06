#pragma once

#include "../sdk/Color.hpp"

struct Options
{
	struct Legit_t
	{
		struct Aimbot_t
		{
			bool Enable = false;
			bool AutoAim = false;
			bool Deathmatch = false;
			bool Visible = false;
			bool Scoped = false;
			bool Flashed = false;
			bool InAir = false;
			int TargetBone = 3;
			int Smoothing = 1;
		} Aimbot;
		struct Triggerbot_t
		{
			bool Enable = false;
			bool AutoFire = false;
			bool Deathmatch = false;
			bool Scoped = false;
			bool Flashed = false;
			bool InAir = false;
			bool AutoKnife = false;
			bool AutoTaser = false;
			bool ExcludeGuns = false;
			int Delay = 150;
		} Triggerbot;
		struct RCS_t
		{
			bool Enable = false;
			float Amount = 0.0f;
		} RCS;
	} Legit;

	struct Visuals_t
	{
		struct Glow_t
		{
			bool Enable = false;
			bool Teammates = false;
			bool Visible = false;
			bool Healthbased = false;
			bool Defusing = false;
			bool Scoped = false;
			bool Flashed = false;
		} Glow;
		struct Chams_t
		{
			bool Enable = false;
			bool Teammates = false;
		} Chams;
		struct World_t
		{
			bool Radar = false;
			float Brightness = 0.0f;
		} World;
	} Visuals;

	struct Misc_t
	{
		struct Helpers_t
		{
			bool Bunnyhop = false;
			bool AutoPistol = false;
			bool NoFlash = false;
			int Fov = 90;
		} Helpers;
	} Misc;

	struct Colors_t
	{
		struct Glow_t
		{
			Color Teammates = { 0.0f, 0.0f, 1.0f };
			Color Enemies = { 1.0f, 0.0f, 0.0f };
			Color EnemiesVisible = { 1.0f, 0.0f, 0.0f };
			Color Defusing = { 1.0f, 0.5f, 0.0f };
			Color Scoped = { 0.75f, 0.0f, 1.0f };
			Color Flashed = { 1.0f, 1.0f, 1.0f };
		} Glow;
		struct Chams_t
		{
			Color Teammates = { 0.0f, 0.0f, 1.0f };
			Color Enemies = { 1.0f, 0.0f, 0.0f };
		} Chams;
	} Colors;

	struct Developer_t
	{
		bool Enable = false;
		bool UnloadOnExit = true;
		float GlowAlpha = 0.85f;
		int GlowStyle = 0;
		float LocalPlayerFlashFlagAmount = 2.5f;
		float EntityFlashFlagAmount = 2.5f;
		int RcsShotsTrigger = 3;
	} Developer;

	struct Default_t
	{
		int oModelAmbient = 0;
		int oFov = 0;
	} Default;
};