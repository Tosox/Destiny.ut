#include "CBaseEntity.hpp"
#include "../settings/globals.hpp"
#include "../helpers/offsets.hpp"

unsigned char CBaseEntity::getFlags()
{
	return g_Memory.read<unsigned char>(m_Address + offsets::netvars::m_fFlags);
}

int CBaseEntity::getCrosshairId()
{
	return g_Memory.read<int>(m_Address + offsets::netvars::m_iCrosshairId);
}

int CBaseEntity::getFov()
{
	return g_Memory.read<int>(m_Address + offsets::netvars::m_iDefaultFOV);
}

int CBaseEntity::getShotsFired()
{
	return g_Memory.read<int>(m_Address + offsets::netvars::m_iShotsFired);
}

Vector2 CBaseEntity::getAimPunchAngle()
{
	return g_Memory.read<Vector2>(m_Address + offsets::netvars::m_aimPunchAngle);
}

Vector3 CBaseEntity::getViewOffset()
{
	return g_Memory.read<Vector3>(m_Address + offsets::netvars::m_vecViewOffset);
}

void CBaseEntity::setFov(int value)
{
	g_Memory.write<int>(m_Address + offsets::netvars::m_iDefaultFOV, value);
}