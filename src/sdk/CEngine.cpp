#include <Windows.h>
#include <array>
#include <MemMan/MemMan.hpp>
#include "../helpers/offsets.hpp"
#include "../settings/globals.hpp"

bool CEngine::IsConnected()
{
	return this->GetClientState_State() == 6;
}

bool CEngine::GetSendPackets()
{
	return g_Mem->read<bool>(this->addr + offsets::signatures::dwbSendPackets);
}

char* CEngine::GetGameDirectory()
{
	return g_Mem->read<std::array<char, 0x120>>(this->addr + offsets::signatures::dwGameDir).data();
}

char* CEngine::GetMapDirectory()
{
	return g_Mem->read<std::array<char, 0x120>>(this->GetClientState() + offsets::signatures::dwClientState_MapDirectory).data();
}

int CEngine::GetModelAmbientMin()
{
	return g_Mem->read<int>(this->addr + offsets::signatures::model_ambient_min);
}

int CEngine::GetClientState_State()
{
	return g_Mem->read<int>(this->GetClientState() + offsets::signatures::dwClientState_State);
}

uintptr_t CEngine::Get()
{
	return this->addr;
}

uintptr_t CEngine::GetClientState()
{
	return g_Mem->read<uintptr_t>(this->addr + offsets::signatures::dwClientState);
}

Vector2 CEngine::GetClientState_ViewAngles()
{
	return g_Mem->read<Vector2>(this->GetClientState() + offsets::signatures::dwClientState_ViewAngles);
}

void CEngine::Set(uintptr_t val)
{
	this->addr = val;
}

void CEngine::SetModelAmbientMin(int val)
{
	g_Mem->write<int>(this->addr + offsets::signatures::model_ambient_min, val);
}

void CEngine::SetSendPackets(bool val)
{
	g_Mem->write<bool>(this->addr + offsets::signatures::dwbSendPackets, val);
}

void CEngine::SetClientState_ViewAngles(Vector2& val)
{
	g_Mem->write<Vector2>(this->GetClientState() + offsets::signatures::dwClientState_ViewAngles, val);
}