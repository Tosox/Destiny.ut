#pragma once

struct GlowStruct_t
{
	unsigned char __base[8];
	float red;
	float green;
	float blue;
	float alpha;
	unsigned char __buffer0[16];
	bool renderWhenOccluded;
	bool renderWhenUnOccluded;
	bool fullBloom;
	unsigned char __buffer1[5];
	int glowStyle;
};
