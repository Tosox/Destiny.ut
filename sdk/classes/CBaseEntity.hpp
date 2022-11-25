#pragma once

#include "CEntity.hpp"
#include "../structs/Vector2.hpp"
#include "../structs/Vector3.hpp"

class CBaseEntity : public CEntity
{
public:
	unsigned char getFlags();
	int getCrosshairId();
	int getFov();
	int getShotsFired();
	Vector2 getAimPunchAngle();
	Vector3 getViewOffset();
	Vector3 getEyeLocation();

	void setFov(int value);

	inline CBaseEntity& operator= (const std::uintptr_t& address) { m_Address = address; return *this; }
};