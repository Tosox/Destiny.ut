#pragma once

#include <Windows.h>
#include "CWeaponEntity.hpp"
#include "Structs.hpp"
#include "Vector.hpp"

class CEntity
{
public:
	bool IsAlive();
	bool IsExisting();
	bool IsDefusing();
	bool IsDormant();
	bool IsScoped();
	bool IsSpotted();
	bool IsSpottedBy(CEntity& entity);
	bool IsValid();
	float GetFlashDuration();
	int GetClassId();
	int GetGlowIndex();
	int GetHealth();
	int GetId();
	int GetTeamNum();
	CWeaponEntity GetActiveWeapon();
	uintptr_t Get();
	uintptr_t GetBoneMatrix();
	Vector3 GetBoneById(int bone);
	Vector3 GetOrigin();
	Vector3 GetVelocity();

	void Set(uintptr_t val);
	void SetFlashDuration(float val);
	void SetSpotted(bool val);
	void SetClrRender(ClrRender_t& clrRender);

protected:
	uintptr_t addr;
};