#pragma once
#include <Windows.h>
#include "CEntity.hpp"
#include "Vector.hpp"

class CBaseEntity : public CEntity
{
public:
	BYTE GetFlags();
	int GetCrosshairId();
	int GetFov();
	int GetShotsFired();
	Vector2 GetAimPunchAngle();
	Vector3 GetViewOffset();

	void SetFov(int val);
};