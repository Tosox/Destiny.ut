#include <Windows.h>
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

void CEngine::Set(const uintptr_t addr)
{
	this->addr = addr;
}

void CEngine::SetModelAmbientMin(const int val)
{
	g_Mem->write<int>(this->addr + offsets::signatures::model_ambient_min, val);
}

void CEngine::SetSendPackets(const bool val)
{
	g_Mem->write<bool>(this->addr + offsets::signatures::dwbSendPackets, val);
}

void CEngine::SetClientState_ViewAngles(const Vector2& val)
{
	g_Mem->write<Vector2>(this->GetClientState() + offsets::signatures::dwClientState_ViewAngles, val);
}