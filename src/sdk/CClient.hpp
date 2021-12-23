#pragma once

#include <Windows.h>
#include "Structs.hpp"

class CClient
{
public:
	bool IsMouseEnabled();
	GlowStruct_t GetGlowStruct(const int glowIndex);
	uintptr_t Get();
	uintptr_t GetLocalPlayer();
	uintptr_t GetGlowObjectManager();
	uintptr_t GetEntityFromList(const int i);

	void Set(const uintptr_t addr);
	void SetGlowStruct(const int glowIndex, const GlowStruct_t& glowStruct);
	void DoForceJump();
	void DoForceAttack();
	void DoForceAttack2();

private:
	uintptr_t addr;
};

