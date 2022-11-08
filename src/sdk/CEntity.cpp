#include <Windows.h>
#include "CEntity.hpp"
#include "CWeaponEntity.hpp"
#include "Structs.hpp"
#include "Vector.hpp"
#include "../helpers/offsets.hpp"
#include "../settings/globals.hpp"

CEntity::CEntity()
{
	m_Address = 0;
}

CEntity::CEntity(std::uintptr_t address)
{
	m_Address = address;
}

bool CEntity::isAlive()
{
	return getHealth() > 0;
}

bool CEntity::isDefusing()
{
	return g_Memory.read<bool>(m_Address + offsets::netvars::m_bIsDefusing);
}

bool CEntity::isDormant()
{
	return g_Memory.read<bool>(m_Address + offsets::signatures::m_bDormant);
}

bool CEntity::isScoped()
{
	return g_Memory.read<bool>(m_Address + offsets::netvars::m_bIsScoped);
}

bool CEntity::isSpotted()
{
	return g_Memory.read<bool>(m_Address + offsets::netvars::m_bSpotted);
}

bool CEntity::isSpottedBy(CEntity& entity)
{
	return g_Memory.read<int>(m_Address + offsets::netvars::m_bSpottedByMask) & (1 << entity.getId());
}

float CEntity::getFlashDuration()
{
	return g_Memory.read<float>(m_Address + offsets::netvars::m_flFlashDuration);
}

int CEntity::getClassId()
{
	return g_Memory.read<int>(g_Memory.read<std::uintptr_t>(g_Memory.read<std::uintptr_t>(g_Memory.read<std::uintptr_t>(m_Address + 0x8) + 0x8) + 0x1) + 0x14);
}

int CEntity::getGlowIndex()
{
	return g_Memory.read<int>(m_Address + offsets::netvars::m_iGlowIndex);
}

int CEntity::getHealth()
{
	return g_Memory.read<int>(m_Address + offsets::netvars::m_iHealth);
}

int CEntity::getId()
{
	return g_Memory.read<int>(m_Address + 0x64) - 1;
}

int CEntity::getTeamNum()
{
	return g_Memory.read<int>(m_Address + offsets::netvars::m_iTeamNum);
}

CWeaponEntity CEntity::getActiveWeapon()
{
	const int hWeapon = g_Memory.read<int>(m_Address + offsets::netvars::m_hActiveWeapon);
	return g_Memory.read<CWeaponEntity>(g_Client + offsets::signatures::dwEntityList + ((hWeapon & 0xFFF) - 0x1) * 0x10);
}

std::uintptr_t CEntity::getBoneMatrix()
{
	return g_Memory.read<std::uintptr_t>(m_Address + offsets::netvars::m_dwBoneMatrix);
}

Vector3 CEntity::getBoneById(int boneId)
{
	std::uintptr_t bonePtr = getBoneMatrix();
	Vector3 bonePosition{};
	bonePosition.x = g_Memory.read<float>(bonePtr + 0x30 * boneId + 0x0C);
	bonePosition.y = g_Memory.read<float>(bonePtr + 0x30 * boneId + 0x1C);
	bonePosition.z = g_Memory.read<float>(bonePtr + 0x30 * boneId + 0x2C);
	return bonePosition;
}

Vector3 CEntity::getOrigin()
{
	return g_Memory.read<Vector3>(m_Address + offsets::netvars::m_vecOrigin);
}

Vector3 CEntity::getVelocity()
{
	return g_Memory.read<Vector3>(m_Address + offsets::netvars::m_vecVelocity);
}

void CEntity::setFlashDuration(float value)
{
	g_Memory.write<float>(m_Address + offsets::netvars::m_flFlashDuration, value);
}

void CEntity::setSpotted(bool value)
{
	g_Memory.write<bool>(m_Address + offsets::netvars::m_bSpotted, value);
}

void CEntity::setClrRender(ClrRender_t& clrRender)
{
	g_Memory.write<ClrRender_t>(m_Address + offsets::netvars::m_clrRender, clrRender);
}