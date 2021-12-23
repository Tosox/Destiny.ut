#pragma once

#include <Windows.h>

struct GlowStruct_t
{
	BYTE base[8];
	float red;
	float green;
	float blue;
	float alpha;
	BYTE buffer0[16];
	bool renderWhenOccluded;
	bool renderWhenUnOccluded;
	bool fullBloom;
	BYTE buffer1[5];
	int glowStyle;
};

struct ClrRender_t
{
	BYTE red;
	BYTE green;
	BYTE blue;
};