#include <Windows.h>
#include <MemMan/MemMan.hpp>
#include "CClient.hpp"
#include "../helpers/offsets.hpp"
#include "../settings/globals.hpp"

bool CClient::IsMouseEnabled()
{
	int mouse = g_Mem->read<int>(this->addr + offsets::signatures::dwMouseEnable);
	mouse ^= offsets::signatures::dwMouseEnablePtr;
	return !(mouse & 1);
}

GlowStruct_t CClient::GetGlowStruct(const int glowIndex)
{
	return g_Mem->read<GlowStruct_t>(this->GetGlowObjectManager() + (glowIndex * 0x38));
}

uintptr_t CClient::Get()
{
	return this->addr;
}

uintptr_t CClient::GetLocalPlayer()
{
	return g_Mem->read<uintptr_t>(this->addr + offsets::signatures::dwLocalPlayer);
}

uintptr_t CClient::GetGlowObjectManager()
{
	return g_Mem->read<uintptr_t>(this->addr + offsets::signatures::dwGlowObjectManager);
}

uintptr_t CClient::GetEntityFromList(const int i)
{
	return g_Mem->read<uintptr_t>(this->addr + offsets::signatures::dwEntityList + (i * 0x10));
}

void CClient::Set(const uintptr_t addr)
{
	this->addr = addr;
}

void CClient::SetGlowStruct(const int glowIndex, const GlowStruct_t& glowStruct)
{
	g_Mem->write<GlowStruct_t>(this->GetGlowObjectManager() + (glowIndex * 0x38), glowStruct);
}

void CClient::DoForceJump()
{
	g_Mem->write<uintptr_t>(this->addr + offsets::signatures::dwForceJump, 6);
}

void CClient::DoForceAttack()
{
	g_Mem->write<uintptr_t>(this->addr + offsets::signatures::dwForceAttack, 6);
}

void CClient::DoForceAttack2()
{
	g_Mem->write<uintptr_t>(this->addr + offsets::signatures::dwForceAttack2, 6);
}