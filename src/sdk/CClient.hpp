#pragma once

#include <Windows.h>
#include "Structs.hpp"

class CClient
{
public:
	bool IsMouseEnabled();
	GlowStruct_t GetGlowStruct(int glowIndex);
	uintptr_t Get();
	uintptr_t GetLocalPlayer();
	uintptr_t GetGlowObjectManager();
	uintptr_t GetEntityFromList(int i);

	void Set(uintptr_t val);
	void SetGlowStruct(int glowIndex, GlowStruct_t& glowStruct);
	void DoForceJump();
	void DoForceAttack();
	void DoForceAttack2();

private:
	uintptr_t addr;
};

