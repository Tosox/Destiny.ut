#pragma once

#include <cstdint>
#include "Structs.hpp"

class CClient
{
public:
	bool isMouseEnabled();
	GlowStruct_t getGlowStruct(int glowIndex);
	std::uintptr_t getLocalPlayer();
	std::uintptr_t getGlowObjectManager();
	std::uintptr_t getEntityFromList(int index);

	void setGlowStruct(int glowIndex, GlowStruct_t& glowStruct);
	void doForceJump();
	void doForceAttack();
	void doForceAttack2();

	inline CClient& operator= (const std::uintptr_t& address) { m_Address = address; return *this; }
	friend std::uintptr_t operator+ (const CClient& entity, const std::uintptr_t& offset) { return entity.m_Address + offset; }

private:
	std::uintptr_t m_Address{};
};

