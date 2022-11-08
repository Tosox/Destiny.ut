#include "CClient.hpp"
#include "../helpers/offsets.hpp"
#include "../settings/globals.hpp"

bool CClient::isMouseEnabled()
{
	int mouse = g_Memory.read<int>(m_Address + offsets::signatures::dwMouseEnable);
	mouse ^= offsets::signatures::dwMouseEnablePtr;
	return !(mouse & 1);
}

GlowStruct_t CClient::getGlowStruct(int glowIndex)
{
	return g_Memory.read<GlowStruct_t>(getGlowObjectManager() + (glowIndex * 0x38));
}

std::uintptr_t CClient::getLocalPlayer()
{
	return g_Memory.read<std::uintptr_t>(m_Address + offsets::signatures::dwLocalPlayer);
}

std::uintptr_t CClient::getGlowObjectManager()
{
	return g_Memory.read<std::uintptr_t>(m_Address + offsets::signatures::dwGlowObjectManager);
}

std::uintptr_t CClient::getEntityFromList(int index)
{
	return g_Memory.read<std::uintptr_t>(m_Address + offsets::signatures::dwEntityList + (index * 0x10));
}

void CClient::setGlowStruct(int glowIndex, GlowStruct_t& glowStruct)
{
	g_Memory.write<GlowStruct_t>(getGlowObjectManager() + (glowIndex * 0x38), glowStruct);
}

void CClient::doForceJump()
{
	g_Memory.write<uintptr_t>(m_Address + offsets::signatures::dwForceJump, 6);
}

void CClient::doForceAttack()
{
	g_Memory.write<uintptr_t>(m_Address + offsets::signatures::dwForceAttack, 6);
}

void CClient::doForceAttack2()
{
	g_Memory.write<uintptr_t>(m_Address + offsets::signatures::dwForceAttack2, 6);
}