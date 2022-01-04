#include <Windows.h>
#include <MemMan/MemMan.hpp>
#include "CEntity.hpp"
#include "CWeaponEntity.hpp"
#include "Structs.hpp"
#include "Vector.hpp"
#include "../helpers/offsets.hpp"
#include "../settings/globals.hpp"

bool CEntity::IsAlive()
{
	return this->GetHealth() > 0;
}

bool CEntity::IsExisting()
{
	return this->addr != NULL;
}

bool CEntity::IsDefusing()
{
	return g_Mem->read<bool>(this->addr + offsets::netvars::m_bIsDefusing);
}

bool CEntity::IsDormant()
{
	return g_Mem->read<bool>(this->addr + offsets::signatures::m_bDormant);
}

bool CEntity::IsScoped()
{
	return g_Mem->read<bool>(this->addr + offsets::netvars::m_bIsScoped);
}

bool CEntity::IsSpotted()
{
	return g_Mem->read<bool>(this->addr + offsets::netvars::m_bSpotted);
}

bool CEntity::IsSpottedBy(CEntity& entity)
{
	return (g_Mem->read<int>(this->addr + offsets::netvars::m_bSpottedByMask)) & (1 << entity.GetId());
}

bool CEntity::IsValid()
{
	if (!this->IsExisting())
		return false;
	if (this->GetHealth() <= 0)
		return false;
	if (this->IsDormant())
		return false;
	return true;
}

float CEntity::GetFlashDuration()
{
	return g_Mem->read<float>(this->addr + offsets::netvars::m_flFlashDuration);
}

int CEntity::GetClassId()
{
	return g_Mem->read<int>(g_Mem->read<uintptr_t>(g_Mem->read<uintptr_t>(g_Mem->read<uintptr_t>(this->addr + 0x8) + 0x8) + 0x1) + 0x14);
}

int CEntity::GetGlowIndex()
{
	return g_Mem->read<int>(this->addr + offsets::netvars::m_iGlowIndex);
}

int CEntity::GetHealth()
{
	return g_Mem->read<int>(this->addr + offsets::netvars::m_iHealth);
}

int CEntity::GetId()
{
	return g_Mem->read<int>(this->addr + 0x64) - 1;
}

int CEntity::GetTeamNum()
{
	return g_Mem->read<int>(this->addr + offsets::netvars::m_iTeamNum);
}

CWeaponEntity CEntity::GetActiveWeapon()
{
	int hWeapon = g_Mem->read<int>(this->addr + offsets::netvars::m_hActiveWeapon);
	return g_Mem->read<CWeaponEntity>(g_Client.Get() + offsets::signatures::dwEntityList + ((hWeapon & 0xFFF) - 0x1) * 0x10);
}

uintptr_t CEntity::Get()
{
	return this->addr;
}

uintptr_t CEntity::GetBoneMatrix()
{
	return g_Mem->read<uintptr_t>(this->addr + offsets::netvars::m_dwBoneMatrix);
}

Vector3 CEntity::GetBoneById(int bone)
{
	uintptr_t bonePtr = this->GetBoneMatrix();
	Vector3 bonePosition{};
	bonePosition.x = g_Mem->read<float>(bonePtr + 0x30 * bone + 0x0C);
	bonePosition.y = g_Mem->read<float>(bonePtr + 0x30 * bone + 0x1C);
	bonePosition.z = g_Mem->read<float>(bonePtr + 0x30 * bone + 0x2C);
	return bonePosition;
}

Vector3 CEntity::GetOrigin()
{
	return g_Mem->read<Vector3>(this->addr + offsets::netvars::m_vecOrigin);
}

Vector3 CEntity::GetVelocity()
{
	return g_Mem->read<Vector3>(this->addr + offsets::netvars::m_vecVelocity);
}

void CEntity::Set(uintptr_t val)
{
	this->addr = val;
}

void CEntity::SetFlashDuration(float val)
{
	g_Mem->write<float>(this->addr + offsets::netvars::m_flFlashDuration, val);
}

void CEntity::SetSpotted(bool val)
{
	g_Mem->write<bool>(this->addr + offsets::netvars::m_bSpotted, val);
}

void CEntity::SetClrRender(ClrRender_t& clrRender)
{
	g_Mem->write<ClrRender_t>(this->addr + offsets::netvars::m_clrRender, clrRender);
}