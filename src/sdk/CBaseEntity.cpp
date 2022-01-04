#include <Windows.h>
#include <MemMan/MemMan.hpp>
#include "CBaseEntity.hpp"
#include "../settings/globals.hpp"
#include "../helpers/offsets.hpp"

BYTE CBaseEntity::GetFlags()
{
	return g_Mem->read<BYTE>(this->addr + offsets::netvars::m_fFlags);
}

int CBaseEntity::GetCrosshairId()
{
	return g_Mem->read<int>(this->addr + offsets::netvars::m_iCrosshairId);
}

int CBaseEntity::GetFov()
{
	return g_Mem->read<int>(this->addr + offsets::netvars::m_iDefaultFOV);
}

int CBaseEntity::GetShotsFired()
{
	return g_Mem->read<int>(this->addr + offsets::netvars::m_iShotsFired);
}

Vector2 CBaseEntity::GetAimPunchAngle()
{
	return g_Mem->read<Vector2>(this->addr + offsets::netvars::m_aimPunchAngle);
}

Vector3 CBaseEntity::GetViewOffset()
{
	return g_Mem->read<Vector3>(this->addr + offsets::netvars::m_vecViewOffset);
}

void CBaseEntity::SetFov(int val)
{
	g_Mem->write<int>(this->addr + offsets::netvars::m_iDefaultFOV, val);
}