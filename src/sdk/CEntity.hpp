#pragma once

#include <Windows.h>
#include "CWeaponEntity.hpp"
#include "Structs.hpp"
#include "Vector.hpp"

class CEntity
{
public:
	CEntity();
	CEntity(std::uintptr_t address);

	bool isAlive();
	bool isDefusing();
	bool isDormant();
	bool isScoped();
	bool isSpotted();
	bool isSpottedBy(CEntity& entity);
	bool isValid();
	float getFlashDuration();
	int getClassId();
	int getGlowIndex();
	int getHealth();
	int getId();
	int getTeamNum();
	CWeaponEntity getActiveWeapon();
	uintptr_t getBoneMatrix();
	Vector3 getBoneById(int boneId);
	Vector3 getOrigin();
	Vector3 getVelocity();

	void setFlashDuration(float value);
	void setSpotted(bool value);
	void setClrRender(ClrRender_t& clrRender);

	inline CEntity& operator= (const std::uintptr_t& address) { m_Address = address; return *this; }
	friend std::uintptr_t operator+ (const CEntity& entity, const std::uintptr_t& offset) { return entity.m_Address + offset; }
	friend bool operator== (const CEntity& entity1, const CEntity& entity2) { return entity1.m_Address == entity2.m_Address; }
	friend bool operator! (const CEntity& entity) { return entity.m_Address == NULL; };

protected:
	std::uintptr_t m_Address{};
};